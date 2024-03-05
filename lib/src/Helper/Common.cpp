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
    QImage inputImage = original.toImage().convertToFormat(QImage::Format_ARGB32);
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
QPixmap renderSvgToPixmap(const QString& path, int size, int ratio)
{
    QSvgRenderer renderer(path);
    QPixmap pixmap(size * ratio, size * ratio);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    renderer.render(&painter, pixmap.rect());
    pixmap.setDevicePixelRatio(static_cast<double>(ratio));
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
QPixmap roundedPixmap(const QPixmap& input, double radius)
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
QImage blurImage(const QImage& original, double sigma)
{
    if (original.isNull())
        return {};
    auto input = original.copy();
    auto output = original.copy();
    auto* inputData = input.bits();
    auto* outputData = output.bits();
    fast_gaussian_blur<uchar, Border::kExtend>(inputData, outputData, input.width(), input.height(), 4, sigma);
    return input;
}
QPixmap blurPixmap(const QPixmap& original, double blurRadius, bool extend)
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
    auto input = extend? extendedImage(original, padding) : original.toImage();
    const auto output = blurImage(input, blurRadius);
    return QPixmap::fromImage(output);
}
QPixmap shadowPixmap(const QPixmap& original, double blurRadius, const QColor& color)
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
QPixmap shadowPixmap(const QSize& size, double borderRadius, double blurRadius, const QColor& color)
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