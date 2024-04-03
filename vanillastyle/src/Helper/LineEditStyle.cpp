#include <QPainter>
#include <QPainterPath>

#include "VanillaStyle/Helper/LineEditStyle.h"
#include "VanillaStyle/Theme/Theme.h"


namespace Vanilla
{
bool LineEditStyle::draw(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionFrame*>(option);
    if (!opt)
    {
        return true;
    }

    painter->setRenderHints(QPainter::Antialiasing);
    if (opt->lineWidth > 0)
    {
        const auto radius = theme->getRadius(Theme::ButtonRadius);
        const auto fgColor = theme->getColor(option, Theme::ColorRole::LineEditOutline);
        painter->setPen(fgColor);
        painter->drawRoundedRect(QRectF(opt->rect).adjusted(1, 1, -1, -1), radius, radius);
    }
    return true;
}
QRect LineEditStyle::subElementRect(QStyle::SubElement element, const QStyleOption* option, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
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