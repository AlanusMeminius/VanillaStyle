#include "ComboBoxStyle.h"
#include <QPainter>
#include <QStyleOption>

ComboBoxStyle::ComboBoxStyle()
    : commonStyle(std::make_shared<Theme::CommonStyle>())
{
}
void ComboBoxStyle::draw(const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const
{
    commonStyle->drawFrame(opt, painter);
}
void ComboBoxStyle::drawIndicator(const QStyleOption* option, QPainter* painter) const
{
    const QRectF copy = option->rect.adjusted(2, 0, -2, 0);
    commonStyle->drawDownArrow(copy, painter);
};