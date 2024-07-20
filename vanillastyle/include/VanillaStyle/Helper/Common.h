#pragma once
#include <QPixmap>
#include <QIcon>
#include "VanillaStyle/vglobal.h"

namespace Vanilla
{

VANILLA_EXPORT QImage switchColorWithTint(const QPixmap& original, const QColor& color);
VANILLA_EXPORT QImage switchImageColor(const QPixmap& original, const QColor& color);
VANILLA_EXPORT QPixmap switchPixColor(const QPixmap& original, const QColor& color, bool mode);

VANILLA_EXPORT QPixmap getCachedPixmap(QPixmap const& input, QColor const& color, bool mode);
VANILLA_EXPORT QPixmap getColorizedPixmap(QPixmap const& input, const QWidget* widget, QColor color, bool mode = true);

VANILLA_EXPORT QPixmap renderSvgToPixmap(const QString& path, int size, qreal ratio);

VANILLA_EXPORT void renderSvgFromPath(const QString& path, QPainter* painter, const QRectF& rect);
VANILLA_EXPORT void renderSvgFromString(const QString& svg, QPainter* painter, const QRectF& rect);

VANILLA_EXPORT QString switchSvgColor(const QString& path, const QColor& color);

VANILLA_EXPORT QPixmap getIconPixmap(const QIcon& icon, const QSize& iconSize, const QWidget* widget, QIcon::Mode mode, QIcon::State state);

VANILLA_EXPORT QImage blurImage(const QImage& original, double sigma);
VANILLA_EXPORT QPixmap blurPixmap(QPixmap const& original, double blurRadius, bool extend);

template <typename T>
VANILLA_EXPORT QImage extendedImage(const T& input, int padding);

VANILLA_EXPORT QPixmap shadowPixmap(QPixmap const& original, double blurRadius, QColor const& color);
VANILLA_EXPORT QPixmap shadowPixmap(QSize const& size, double borderRadius, double blurRadius, QColor const& color);

VANILLA_EXPORT void drawUpArrow(const QString& iconPath, QPainter* painter, const QRect& rect);
VANILLA_EXPORT void drawDownArrow(const QString& iconPath, QPainter* painter, const QRect& rect);

VANILLA_EXPORT std::tuple<QString, QString> splitMenuShortcut(QString const& text);

VANILLA_EXPORT QRect insideMargin(const QRect& rect, int margin);
VANILLA_EXPORT QRectF insideMargin(const QRectF& rect, int margin);
VANILLA_EXPORT QRect insideMargin(const QRect& rect, int marginWidth, int marginHeight);
VANILLA_EXPORT QRectF insideMargin(const QRectF& rect, int marginWidth, int marginHeight);

VANILLA_EXPORT QRect centerRect(const QRect& rect, const QSize& size);

VANILLA_EXPORT QRect centerRect(const QRect& rect, int width, int height);

VANILLA_EXPORT QRectF centerRectF(const QRectF& rect, double width, double height);

VANILLA_EXPORT bool checkBoolProperty(const QWidget* widget, const std::string& propertyName);
VANILLA_EXPORT QColor getQColorProperty(const QWidget* widget, const std::string& propertyName);
}  // namespace Vanilla
