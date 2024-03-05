#include "VanillaStyle/Helper/RadioButtonStyle.h"
#include <QPainter>

void VanillaStyle::RadioButtonStyle::draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const VanillaStyle::Theme* theme)
{
    if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
    {
        auto rect = QRectF(optionButton->rect);
        // 获取颜色
        //        auto bgColor = theme->checkBtnBgColor(option);
        auto bgColor = QColor(10, 255, 255);
        auto border = theme->getBorder(Theme::ButtonBorder);
        auto margins = QMarginsF(border / 2., border / 2., border / 2., border / 2.);
        auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

        painter->setRenderHints(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(bgColor);
        painter->drawEllipse(buttonRect);
        drawIndicator(option, buttonRect, painter, theme);
    }
}
void VanillaStyle::RadioButtonStyle::drawIndicator(const QStyleOption* option, const QRectF rect, QPainter* painter, const VanillaStyle::Theme* theme) const
{
    if (option->state & QStyle::State_On)
    {
//        auto fgColor = theme->checkBtnFgColor(option);
        auto fgColor = QColor(10, 10, 255);
        painter->setRenderHints(QPainter::Antialiasing);
        painter->setBrush(fgColor);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(rect.adjusted(2, 2, -2, -2));
    }
}
