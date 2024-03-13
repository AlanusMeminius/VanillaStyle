#include "VanillaStyle/Helper/Common.h"
#include "fast_gaussian_blur_template.h"
#include <QSvgRenderer>
#include <QPainter>

namespace VanillaStyle
{

QImage switchImageColor(const QPixmap& original, const QColor& color)
{
    if (original.isNull())
    {
        return {};
    }
    const QImage inputImage = original.toImage().convertToFormat(QImage::Format_ARGB32);
    QImage outputImage(inputImage.size(), inputImage.format());
    outputImage.setDevicePixelRatio(inputImage.devicePixelRatioF());

    const auto outputAf = color.alphaF();

    for (int x = 0; x < inputImage.width(); ++x)
    {
        for (int y = 0; y < inputImage.height(); ++y)
        {
            const auto inputPixel = inputImage.pixel(x, y);
            const auto outputA = static_cast<int>(qAlpha(inputPixel) * outputAf);
            const auto outputPixel = qRgba(color.red(), color.green(), color.blue(), outputA);
            outputImage.setPixel(x, y, outputPixel);
        }
    }
    return outputImage;
}
QPixmap switchPixColor(const QPixmap& original, const QColor& color)
{
    return QPixmap::fromImage(switchImageColor(original, color));
}
QPixmap renderSvgToPixmap(const QString& path, const int size, const int ratio)
{
    QSvgRenderer renderer(path);
    QPixmap pixmap(size * ratio, size * ratio);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    renderer.render(&painter, pixmap.rect());
    pixmap.setDevicePixelRatio(ratio);
    return pixmap;
}
QIcon createIcon(const QString& path, int size)
{
    if (path.isEmpty())
        return {};

    QIcon icon;
    constexpr std::array<int, 2> ratios{1, 2};
    for (const auto& ratio : ratios)
    {
        icon.addPixmap(renderSvgToPixmap(path, size, ratio));
    }
    return icon;
}
void renderSvgFromString(const std::string& svg, QPainter* painter, const QRect& rect)
{
    QSvgRenderer render;
    render.load(QString::fromStdString(svg).toUtf8());
    render.render(painter, rect);
}
QPixmap roundedPixmap(const QPixmap& input, const double radius)
{
    if (input.isNull())
        return {};

    QPixmap result(input.size());
    result.fill(Qt::transparent);
    QPainter p(&result);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setBrush(Qt::white);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(result.rect(), radius, radius);
    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    p.drawPixmap(result.rect(), input);

    result.setDevicePixelRatio(input.devicePixelRatio());
    return result;
}
QImage blurImage(const QImage& original, const double sigma)
{
    if (original.isNull())
        return {};
    auto input = original.copy();
    auto output = original.copy();
    auto* inputData = input.bits();
    auto* outputData = output.bits();
    fast_gaussian_blur<uchar, kExtend>(inputData, outputData, input.width(), input.height(), 4, static_cast<float>(sigma));
    return input;
}
QPixmap blurPixmap(const QPixmap& original, double blurRadius, const bool extend)
{
    if (original.isNull())
    {
        return {};
    }
    blurRadius /= 2.329; // std::sqrt(2 * std::log(255)) - 1;

    if (blurRadius < 1) {
        return original;
    }

    const auto padding = static_cast<int>(std::ceil(blurRadius * 4));
    const auto input = extend? extendedImage(original, padding) : original.toImage();
    const auto output = blurImage(input, blurRadius);
    return QPixmap::fromImage(output);
}
QPixmap shadowPixmap(const QPixmap& original, const double blurRadius, const QColor& color)
{
    if (original.isNull())
    {
        return {};
    }

    if (blurRadius <= 0) {
        QPixmap result(original.size());
        result.fill(Qt::transparent);
        return result;
    }

    const auto padding = static_cast<int>(std::ceil(blurRadius * 4));
    const auto switchColor = switchImageColor(original, color);
    const auto input = extendedImage(switchColor, padding);
    const auto output = blurImage(input, blurRadius);
    return QPixmap::fromImage(output);
}
QPixmap shadowPixmap(const QSize& size, const double borderRadius, const double blurRadius, const QColor& color)
{
    if (size.isEmpty())
    {
        return {};
    }
    QPixmap input(size);
    {
        QPainter painter(&input);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setBrush(color);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(input.rect(), borderRadius, borderRadius);
    }
    return shadowPixmap(input, blurRadius, color);
}
void drawUpArrow(QPainter* painter, const QRect& rect, const QColor& color)
{
    const auto svg = std::string(R"(
<svg viewBox="0 0 1024 1024" width="64" height="64">
<path d="M560.256 314.453333c2.474667 2.389333 13.056 11.52 21.76 19.968 54.741333 49.706667
144.341333 179.370667 171.690667 247.253334 4.394667 10.325333 13.696 36.394667 14.293333
50.304 0 13.354667-3.072 26.026667-9.301333 38.186666a79.957333 79.957333 0 0 1-38.570667
33.92c-11.221333 4.266667-44.8 10.922667-45.397333 10.922667-36.736 6.656-96.426667
10.325333-162.389334 10.325333-62.848 0-120.106667-3.669333-157.397333-9.088-0.597333-0.64-42.325333-7.253333-56.618667-14.549333A76.16
76.16 0 0 1 256 634.368v-2.389333c0.64-18.176 16.853333-56.362667 17.450667-56.362667 27.392-64.213333 112.597333-190.890667 169.216-241.834667
 0 0 14.549333-14.336 23.637333-20.565333A76.074667 76.074667 0 0 1 511.701333 298.666667c18.048 0 34.858667 5.461333 48.554667 15.786666z"
fill="#130F26"></path></svg>
                )");
    renderSvgFromString(svg, painter, rect);
}
void drawDownArrow(QPainter* painter, const QRect& rect, const QColor& color)
{
    const auto svg = std::string(R"(
<svgviewBox="0 0 1024 1024" width="64" height="64">
<path d="M463.744 709.546667c-2.474667-2.389333-13.056-11.52-21.76-19.968-54.741333-49.706667-144.341333-179.370667-
171.690667-247.253334-4.394667-10.325333-13.696-36.394667-14.293333-50.304
 0-13.354667 3.072-26.026667 9.301333-38.186666 8.704-15.146667 22.4-27.306667
38.570667-33.92 11.221333-4.266667 44.8-10.922667 45.397333-10.922667 36.736-6.656
96.426667-10.325333 162.389334-10.325333 62.848 0 120.106667 3.669333 157.397333
9.088 0.597333 0.64 42.325333 7.253333 56.618667 14.549333 26.112 13.354667 42.325333
39.424 42.325333 67.328v2.389333c-0.64 18.176-16.853333 56.362667-17.450667 56.362667-27.392
64.213333-112.597333 190.890667-169.216 241.834667 0 0-14.549333 14.336-23.637333
20.565333a76.074667 76.074667 0 0 1-45.397333 14.549333c-18.048
0-34.858667-5.461333-48.554667-15.786666z"
fill="#200E32"></path></svg>
                )");
    renderSvgFromString(svg, painter, rect);
}
template <typename T>
QImage extendedImage(const T& input, int padding)
{
    if (input.isNull())
    {
        return {};
    }
    const auto extendedSize = QSize(input.width() + padding, input.height() + padding);
    QImage inputImage(extendedSize, QImage::Format_ARGB32_Premultiplied);
    inputImage.fill(Qt::transparent);
    {
        QPainter p(&inputImage);
        p.setRenderHint(QPainter::Antialiasing, true);
        const auto x = (extendedSize.width() - input.width()) / 2;
        const auto y = (extendedSize.height() - input.height()) / 2;
        if constexpr (std::is_same_v<T, QPixmap>) {
            p.drawPixmap(x, y, input);
        } else if constexpr (std::is_same_v<T, QImage>) {
            p.drawImage(x, y, input);
        }
    }
    return inputImage;
}

}  // namespace VanillaStyle