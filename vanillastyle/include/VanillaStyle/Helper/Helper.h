#pragma once
#include <memory>

#include <QStyleOption>
#include <QPainter>

#include "VanillaStyle/vglobal.h"

namespace Vanilla
{
class Theme;

class VANILLA_EXPORT Helper
{
public:
    bool emptyControl(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*) const;
    bool shapedFrame(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>& theme, const QWidget*) const;
    bool drawLabel(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*, int) const;

    bool drawAlignCenterLabel(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*) const;
    bool drawAlignLeftLabel(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*) const;

    static void renderRoundBorder(QPainter* painter, const QRectF& rect, const QColor& color, qreal border, qreal radius);
    static void renderRoundRect(QPainter* painter, const QRectF& rect, const QColor& color, qreal radius);
    static void renderEllipse(QPainter* painter, const QRectF& rect, const QColor& color);
    static void renderEllipseBorder(QPainter* painter, const QRectF& rect, const QColor& color, qreal border);

    static bool drawCheckBox(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget);
    static void drawCheckBoxHelper(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget);
    static void drawCheckBoxIndicator(const QStyleOption* option, const QRectF rect, QPainter* painter, const std::shared_ptr<Theme>& theme);
};

}  // namespace Vanilla
