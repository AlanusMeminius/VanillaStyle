#include "CheckBoxStyle.h"
#include <QPainter>
#include <QStyleOption>
#include "Theme.h"

namespace Theme
{
CheckBoxStyle::CheckBoxStyle()
    : commonStyle(std::make_shared<CommonStyle>())
{
}
void CheckBoxStyle::draw(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    commonStyle->setupPainterForShape(option, painter, widget);
    painter->drawRoundedRect(QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5), 5, 5);
    drawIndicator(option, painter);  // with the same pen color
    painter->restore();
}
void CheckBoxStyle::drawIndicator(const QStyleOption* option, QPainter* painter) const
{
    if (option->state & QStyle::State_On)
    {
        const QRect rect = option->rect;
        const QVector<QPointF> points{QPointF(rect.x() + 4, rect.y() + 9), QPointF(rect.x() + 8, rect.y() + 12), QPointF(rect.x() + 14, rect.y() + 5)};
        painter->drawPolyline(points);
    }
}
int CheckBoxStyle::indicatorSize() const
{
    return 18;
}
}  // namespace Theme
