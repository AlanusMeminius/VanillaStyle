#pragma once
#include <QStyleOption>
#include <QPainter>

#include <memory>

namespace Vanilla
{
class Theme;

class Helper
{
public:
    bool emptyControl(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*) const;
    bool shapedFrame(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>& theme, const QWidget*) const;
    bool drawRadioCheckLabel(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*) const;

    static void renderRoundBorder(QPainter* painter, const QRectF& rect, const QColor& color, qreal border, qreal radius);
    static void renderRoundRect(QPainter* painter, const QRectF& rect, const QColor& color, qreal radius);
    static void renderEllipse(QPainter* painter, const QRectF& rect, const QColor& color);
    static void renderEllipseBorder(QPainter* painter, const QRectF& rect, const QColor& color, qreal border);
};

}  // namespace Vanilla
