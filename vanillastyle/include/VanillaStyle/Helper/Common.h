#pragma once
#include <QPixmap>
#include <QIcon>

namespace Vanilla
{

QImage switchImageColor(const QPixmap& original, const QColor& color);
QPixmap switchPixColor(const QPixmap& original, const QColor& color);

QPixmap getCachedPixmap(QPixmap const& input, QColor const& color);
QPixmap getColorizedPixmap(QPixmap const& input, const QWidget* widget, QColor color);

QPixmap renderSvgToPixmap(const QString& path, int size, int ratio);

void renderSvgFromPath(const QString& path, QPainter* painter, const QRectF& rect);
void renderSvgFromString(const QString& svg, QPainter* painter, const QRectF& rect);

QString switchSvgColor(const QString& path, const QColor& color);

QPixmap getIconPixmap(const QIcon& icon, const QSize& iconSize, const QWidget* widget);

QImage blurImage(const QImage& original, double sigma);
QPixmap blurPixmap(QPixmap const& original, double blurRadius, bool extend);

template <typename T>
QImage extendedImage(const T& input, int padding);

QPixmap shadowPixmap(QPixmap const& original, double blurRadius, QColor const& color);
QPixmap shadowPixmap(QSize const& size, double borderRadius, double blurRadius, QColor const& color);

void drawUpArrow(const QString& iconPath, QPainter* painter, const QRect& rect);
void drawDownArrow(const QString& iconPath, QPainter* painter, const QRect& rect);


QRect insideMargin(const QRect& rect, int margin);
QRectF insideMargin(const QRectF& rect, int margin);
QRect insideMargin(const QRect& rect, int marginWidth, int marginHeight);
QRectF insideMargin(const QRectF& rect, int marginWidth, int marginHeight);

QRect centerRect(const QRect& rect, const QSize& size) ;

QRect centerRect(const QRect& rect, int width, int height);

QRectF centerRectF(const QRectF& rect, double width, double height);

bool checkBoolProperty(const QWidget* widget, const std::string& propertyName);
QColor getQColorProperty(const QWidget* widget, const std::string& propertyName);
}  // namespace VanillaStyle
