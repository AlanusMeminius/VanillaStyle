#include "CommonStyle.h"
#include "Config/Color.h"
#include <QPainter>

namespace Theme
{
void CommonStyle::setupPainterForShape(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget)
{
    Q_UNUSED(widget)
    if (!(option->state & QStyle::State_Enabled))
    {
        painter->setPen(Color::buttonOutlineColor());
        painter->setBrush(Color::buttonBackground());
        painter->setOpacity(0.5);
    }
    else if (option->state & QStyle::State_Sunken)
    {
        painter->setPen(Color::pressedOutlineColor());
        painter->setBrush(Color::buttonPressedBackground());
    }
    else if ((option->state & QStyle::State_MouseOver) || (option->state & QStyle::State_HasFocus))
    {
        painter->setPen(QPen(Color::hoverOutlineBrush(option->rect), 1));
        painter->setBrush(Color::buttonHoveredBackground());
    }
    else
    {
        painter->setPen(Color::buttonOutlineColor());
        painter->setBrush(Color::buttonBackground());
    }
}
void CommonStyle::drawFrame(const QStyleOption* option, QPainter* painter) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    // painter->setPen(QColor(172, 195, 166));
    if (!(option->state & QStyle::State_Enabled))
    {
        painter->setPen(QColor(246, 245, 245));
        painter->setOpacity(0.5);
    }
    else if (option->state & QStyle::State_HasFocus)
    {
        painter->setPen(QColor(183, 132, 183));
    }
    else
    {
        painter->setPen(QColor(181, 192, 208));
    }
    painter->drawRoundedRect(QRectF(option->rect).adjusted(1, 1, -1, -1), 5, 5);
    painter->restore();
}
void CommonStyle::drawDownArrow(const QRectF& rect, QPainter* painter) const
{
    QVector<QPointF> points = {QPointF(4.5, 8.25), QPointF(12, 15.75), QPointF(19.5, 8.25)};
    for (QPointF& point : points)
    {
        point.rx() = rect.x() + point.x() * (rect.width() / 24.0);
        point.ry() = rect.y() + point.y() * (rect.height() / 24.0);
    }
    painter->drawPolyline(points);
}
void CommonStyle::drawUpArrow(const QRectF& rect, QPainter* painter) const
{
    QVector<QPointF> points = {QPointF(4.5, 15.75), QPointF(12.0, 8.25), QPointF(19.5, 15.75)};
    for (QPointF& point : points)
    {
        point.rx() = rect.x() + point.x() * (rect.width() / 24.0);
        point.ry() = rect.y() + point.y() * (rect.height() / 24.0);
    }
    painter->drawPolyline(points);
}
}  // namespace Theme
