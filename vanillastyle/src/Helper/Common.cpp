#include "VanillaStyle/Helper/Common.h"
#include "fast_gaussian_blur_template.h"

#include <QWidget>
#include <QFile>
#include <QSvgRenderer>
#include <QPainter>
#include <QTextStream>
#include <QPixmapCache>
#include <array>
#include <regex>
#include <QtWidgets/QApplication>

namespace Vanilla
{

static void grayscale(const QImage& image, QImage& dest, const QRect& rect = QRect())
{
    QRect destRect = rect;
    QRect srcRect = rect;

    if (rect.isNull())
    {
        srcRect = dest.rect();
        destRect = dest.rect();
    }
    if (&image != &dest)
    {
        destRect.moveTo(QPoint(0, 0));
    }

    const auto* data = reinterpret_cast<const unsigned int*>(image.bits());
    auto* outData = reinterpret_cast<unsigned int*>(dest.bits());

    if (dest.size() == image.size() && image.rect() == srcRect)
    {
        // A bit faster loop for grayscaling everything.
        int pixels = dest.width() * dest.height();
        for (int i = 0; i < pixels; ++i)
        {
            int val = qGray(data[i]);
            outData[i] = qRgba(val, val, val, qAlpha(data[i]));
        }
    }
    else
    {
        int yd = destRect.top();
        for (int y = srcRect.top(); y <= srcRect.bottom() && y < image.height(); y++)
        {
            data = reinterpret_cast<const unsigned int*>(image.scanLine(y));
            outData = reinterpret_cast<unsigned int*>(dest.scanLine(yd++));
            int xd = destRect.left();
            for (int x = srcRect.left(); x <= srcRect.right() && x < image.width(); x++)
            {
                int val = qGray(data[x]);
                outData[xd++] = qRgba(val, val, val, qAlpha(data[x]));
            }
        }
    }
}

QImage switchImageColor(const QPixmap& original, const QColor& color)
{
    if (original.isNull())
    {
        return {};
    }
    auto inputImage = original.toImage();
    const auto format = inputImage.hasAlphaChannel() ? QImage::Format_ARGB32_Premultiplied : QImage::Format_RGB32;
    inputImage = std::move(inputImage).convertToFormat(format);

    auto outputImage = QImage(inputImage.size(), inputImage.format());
    outputImage.setDevicePixelRatio(inputImage.devicePixelRatioF());

    QPainter outputPainter(&outputImage);
    grayscale(inputImage, outputImage, inputImage.rect());
    outputPainter.setCompositionMode(QPainter::CompositionMode_Screen);
    outputPainter.fillRect(inputImage.rect(), color);
    outputPainter.end();

    if (inputImage.hasAlphaChannel())
    {
        Q_ASSERT(outputImage.format() == QImage::Format_ARGB32_Premultiplied);
        QPainter maskPainter(&outputImage);
        maskPainter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        maskPainter.drawImage(0, 0, inputImage);
    }

    return outputImage;
}

QPixmap switchPixColor(const QPixmap& original, const QColor& color)
{
    return QPixmap::fromImage(switchImageColor(original, color));
}

static QString getPixmapKey(const QPixmap& pixmap, const QColor color)
{
    return QString("%1_%2").arg(pixmap.cacheKey(), color.name().toInt());
}

QPixmap getCachedPixmap(QPixmap const& input, QColor const& color)
{
    if (input.isNull())
    {
        return {};
    }
    const auto& pixmapKey = getPixmapKey(input, color);
    QPixmap pixmapInCache;
    if (const auto found = QPixmapCache::find(pixmapKey, &pixmapInCache); !found)
    {
        const auto& newPixmap = switchPixColor(input, color);
        if (const auto flag = QPixmapCache::insert(pixmapKey, newPixmap))
        {
            QPixmapCache::find(pixmapKey, &pixmapInCache);
        }
    }
    if (pixmapInCache.isNull())
    {
        return input;
    }
    return pixmapInCache;
}

QPixmap getColorizedPixmap(QPixmap const& input, const QWidget* widget, const QColor color)
{
    if (input.isNull())
    {
        return {};
    }
    if (const auto customColor = getQColorProperty(widget, "CustomIconColor"); customColor.isValid())
    {
        return getCachedPixmap(input, customColor);
    }
    return getCachedPixmap(input, color);
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

void renderSvgFromPath(const QString& path, QPainter* painter, const QRectF& rect)
{
    QSvgRenderer render(path);
    render.render(painter, rect);
}

void renderSvgFromString(const QString& svg, QPainter* painter, const QRectF& rect)
{
    QSvgRenderer render;
    render.load(svg.toUtf8());
    render.render(painter, rect);
}

QString switchSvgColor(const QString& path, const QColor& color)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return {};
    }
    QTextStream in(&file);
    const QString svg = in.readAll();
    file.close();
    auto svgString = svg.toStdString();
    const std::regex rx(R"(fill\s*=\s*\"#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})\")");
    svgString = std::regex_replace(svgString, rx, std::string("fill=\"") + color.name(QColor::HexRgb).toStdString() + "\"");
    return QString::fromStdString(svgString);
}

QPixmap getIconPixmap(const QIcon& icon, const QSize& iconSize, const QWidget* widget)
{
    if (icon.isNull())
    {
        return {};
    }
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return icon.pixmap(iconSize);
#else
    return icon.pixmap(iconSize, widget->devicePixelRatio());
#endif
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
    blurRadius /= 2.329;  // std::sqrt(2 * std::log(255)) - 1;

    if (blurRadius < 1)
    {
        return original;
    }

    const auto padding = static_cast<int>(std::ceil(blurRadius * 4));
    const auto input = extend ? extendedImage(original, padding) : original.toImage();
    const auto output = blurImage(input, blurRadius);
    return QPixmap::fromImage(output);
}

QPixmap shadowPixmap(const QPixmap& original, const double blurRadius, const QColor& color)
{
    if (original.isNull())
    {
        return {};
    }

    if (blurRadius <= 0)
    {
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

void drawUpArrow(const QString& iconPath, QPainter* painter, const QRect& rect)
{
    renderSvgFromPath(iconPath, painter, rect);
}

void drawDownArrow(const QString& iconPath, QPainter* painter, const QRect& rect)
{
    renderSvgFromPath(iconPath, painter, rect);
}

QRect insideMargin(const QRect& rect, int margin)
{
    return insideMargin(rect, margin, margin);
}

QRectF insideMargin(const QRectF& rect, int margin)
{
    return insideMargin(rect, margin, margin);
}

QRect insideMargin(const QRect& rect, int marginWidth, int marginHeight)
{
    return rect.adjusted(marginWidth, marginHeight, -marginWidth, -marginHeight);
}

QRectF insideMargin(const QRectF& rect, int marginWidth, int marginHeight)
{
    return rect.adjusted(marginWidth, marginHeight, -marginWidth, -marginHeight);
}

QRect centerRect(const QRect& rect, const QSize& size)
{
    return centerRect(rect, size.width(), size.height());
}

QRect centerRect(const QRect& rect, int width, int height)
{
    return {rect.left() + (rect.width() - width) / 2, rect.top() + (rect.height() - height) / 2, width, height};
}

QRectF centerRectF(const QRectF& rect, double width, double height)
{
    return {rect.left() + (rect.width() - width) / 2, rect.top() + (rect.height() - height) / 2, width, height};
}

bool checkBoolProperty(const QWidget* widget, const std::string& propertyName)
{
    if (const auto p = widget->property(propertyName.c_str()); p.isValid())
    {
        return p.toBool();
    }
    return false;
}

QColor getQColorProperty(const QWidget* widget, const std::string& propertyName)
{
    if (const auto property = widget->property(propertyName.c_str()); property.isValid())
    {
        return  property.value<QColor>();
    }
    return {};
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
        if constexpr (std::is_same_v<T, QPixmap>)
        {
            p.drawPixmap(x, y, input);
        }
        else if constexpr (std::is_same_v<T, QImage>)
        {
            p.drawImage(x, y, input);
        }
    }
    return inputImage;
}

}  // namespace Vanilla