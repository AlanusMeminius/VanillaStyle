#include "VanillaStyle/Helper/CheckBoxStyle.h"
#include <QPainter>
namespace VanillaStyle
{
void CheckBoxStyle::draw(const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
    {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing);
        //    commonStyle->setupPainterForShape(option, painter, widget);

        painter->drawRoundedRect(QRectF(optionButton->rect).adjusted(0.5, 0.5, -0.5, -0.5), 5, 5);
        drawIndicator(optionButton, painter);
        painter->restore();
    }

}
void CheckBoxStyle::drawIndicator(const QStyleOption* option, QPainter* painter) const
{
}
int CheckBoxStyle::indicatorSize() const
{
    return 0;
}
}  // namespace VanillaStyle