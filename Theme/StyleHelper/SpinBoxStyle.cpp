#include "SpinBoxStyle.h"
#include <QPainter>
#include <QStyleOption>

SpinBoxStyle::SpinBoxStyle()
    : commonStyle(std::make_shared<Theme::CommonStyle>()){};
void SpinBoxStyle::draw(const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const
{
    commonStyle->drawFrame(opt, painter);
}

void SpinBoxStyle::drawIndicator(QStyle::PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    if (option->state & QStyle::State_Enabled)
    {
        painter->setPen(QPen(Qt::darkGray, 2));
        painter->setBrush(QBrush(Qt::darkGray));
    }
    else
    {
        painter->setPen(QPen(Qt::gray, 2));
        painter->setBrush(QBrush(Qt::gray));
    }
    const QRect rect = option->rect;
    const QRectF copy = rect.adjusted(2, 0, -2, 0);
    if (element == QStyle::PE_IndicatorSpinDown)
    {
        commonStyle->drawDownArrow(copy, painter);
    }
    else
    {
        commonStyle->drawUpArrow(copy, painter);
    }
}
