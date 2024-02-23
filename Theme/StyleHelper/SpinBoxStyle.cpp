#include "SpinBoxStyle.h"
#include <QPainter>
#include <QStyleOption>

SpinBoxStyle::SpinBoxStyle() = default;
void SpinBoxStyle::draw(const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const
{

}

void SpinBoxStyle::drawIndicator(QStyle::PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    QPolygon points(3);
    int x = option->rect.x();
    int y = option->rect.y();
    int w = option->rect.width() / 2;
    int h = option->rect.height() / 2;
    x += (option->rect.width() - w) / 2;
    y += (option->rect.height() - h) / 2;

    if (element == QStyle::PE_IndicatorSpinUp)
    {
        points[0] = QPoint(x, y + h);
        points[1] = QPoint(x + w, y + h);
        points[2] = QPoint(x + w / 2, y);
    }
    else
    {  // PE_SpinBoxDown
        points[0] = QPoint(x, y);
        points[1] = QPoint(x + w, y);
        points[2] = QPoint(x + w / 2, y + h);
    }

    if (option->state & QStyle::State_Enabled)
    {
        painter->setPen(option->palette.mid().color());
        painter->setBrush(option->palette.buttonText());
    }
    else
    {
        painter->setPen(option->palette.buttonText().color());
        painter->setBrush(option->palette.mid());
    }
    painter->drawPolygon(points);
}