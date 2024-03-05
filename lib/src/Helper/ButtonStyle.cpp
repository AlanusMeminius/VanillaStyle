#include "VanillaStyle/Helper/ButtonStyle.h"
#include <QPainter>

namespace VanillaStyle
{
void ButtonStyle::draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme)
{
    if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
    {
        auto rect = QRectF(optionButton->rect);
        // 获取颜色
        //        auto bgColor = theme->checkBtnBgColor(option);
        auto bgColor = QColor(10, 255, 255);
        auto border = theme->getBorder(Theme::ButtonBorder);
        auto radius = theme->getRadius(Theme::ButtonRadius);

        auto margins = QMarginsF(border / 2., border / 2., border / 2., border / 2.);
        auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

        painter->setRenderHints(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(bgColor);
        painter->drawRoundedRect(buttonRect, radius, radius);
    }
}

}  // namespace VanillaStyle
