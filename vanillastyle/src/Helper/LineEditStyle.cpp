#include <QPainter>
#include <QPainterPath>

#include "VanillaStyle/Helper/LineEditStyle.h"

#include "VanillaStyle/Helper/Helper.h"
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
    const auto radius = theme->getSize(SizeRole::ButtonRadius);
    const auto fgColor = theme->getColor(option, ColorRole::LineEditOutline);
    const auto bgColor = theme->getColor(option, ColorRole::LineEditBackground);
    const auto border = theme->getSize(SizeRole::NormalBorder);
    const auto rect = QRectF(opt->rect).adjusted(1, 1, -1, -1);
    Helper::renderRoundRect(painter, rect.adjusted(0.5, 0.5, -0.5, -0.5), bgColor, radius);
    if (opt->lineWidth > 0)
    {
        Helper::renderRoundBorder(painter, rect, fgColor, border + 0.5, radius);
    }
    return true;
}

QRect LineEditStyle::subElementRect(QStyle::SubElement element, const QStyleOption* option, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    if (element == QStyle::SE_LineEditContents)
    {
        if (const auto* opt = qstyleoption_cast<const QStyleOptionFrame*>(option))
        {
            return opt->rect.adjusted(3, 0, 0, 0);
        }
        return option->rect;
    }
    return option->rect;
}
}  // namespace Vanilla