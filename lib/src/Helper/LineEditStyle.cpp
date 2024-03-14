#include "VanillaStyle/Helper/LineEditStyle.h"
#include <QPainter>
#include <QPainterPath>

namespace VanillaStyle
{
void LineEditStyle::draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme) const
{
    if (const auto* optionLineEdit = qstyleoption_cast<const QStyleOptionFrame*>(option))
    {
        painter->setRenderHints(QPainter::Antialiasing);
        if (optionLineEdit->lineWidth > 0)
        {
            const auto radius = theme->getRadius(Theme::ButtonRadius);
            const auto fgColor = theme->getColor(option, Theme::ColorRole::LineEditOutline);
            painter->setPen(fgColor);
            painter->drawRoundedRect(QRectF(optionLineEdit->rect).adjusted(1, 1, -1, -1), radius, radius);
        }
    }
}
QRect LineEditStyle::subElementRect(QStyle::SubElement element, const QStyleOption* option, const QWidget* widget) const
{
    if (element == QStyle::SE_LineEditContents)
    {
        if (const auto* opt = qstyleoption_cast<const QStyleOptionFrame*>(option))
        {
            return opt->rect.adjusted(5, 0, 0, 0);
        }
        return option->rect;
    }
    return option->rect;
}
}  // namespace VanillaStyle