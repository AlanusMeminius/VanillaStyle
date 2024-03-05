#pragma once
#include <QPixmap>
#include <QImage>
#include <QtGui/qicon.h>

namespace VanillaStyle
{

QImage switchImageColor(const QPixmap& original, const QColor& color);
QPixmap switchPixColor(const QPixmap& original, const QColor& color);

QPixmap renderSvgToPixmap(const QString& path, int size, int ratio);
QIcon createIcon(const QString& path, int size);

QPixmap roundedPixmap(QPixmap const& input, double radius);

QImage blurImage(const QImage& original, double sigma);
QPixmap blurPixmap(QPixmap const& original, double blurRadius, bool extend);

template <typename T>
QImage extendedImage(const T& input, int padding);

QPixmap shadowPixmap(QPixmap const& original, double blurRadius, QColor const& color);
QPixmap shadowPixmap(QSize const& size, double borderRadius, double blurRadius, QColor const& color);
}  // namespace VanillaStyle
