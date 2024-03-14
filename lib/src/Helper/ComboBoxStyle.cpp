#include "VanillaStyle/Helper/ComboBoxStyle.h"
#include "VanillaStyle/Style/VanillaStyle.h"

namespace VanillaStyle {
void ComboBoxStyle::draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme, const VanillaStyle* style) const
{
    if (const auto* opt = qstyleoption_cast<const QStyleOptionComboBox*>(option))
    {
        if (opt->editable)
        {
            painter->setRenderHints(QPainter::Antialiasing);
            const auto rect = opt->rect;
            painter->fillRect(rect, theme->getColor(opt, Theme::ColorRole::LineEditOutline));
            // style->drawControl(QStyle::CE_PushButtonBevel, option, painter, widget);
        }
        else
        {
            painter->setRenderHints(QPainter::Antialiasing);
            const auto rect = opt->rect.adjusted(1,1,-1,-1);
            const auto fgColor = theme->getColor(opt, Theme::ColorRole::ButtonForeground);
            painter->setPen(fgColor);
            painter->drawRoundedRect(rect, 5, 5);

        }
    }
}
} // VanillaStyle