#include "VanillaStyle/Helper/ComboBoxStyle.h"

namespace VanillaStyle {
void ComboBoxStyle::draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme) const
{
    if (const auto* opt = qstyleoption_cast<const QStyleOptionComboBox*>(option))
    {
        if (opt->editable)
        {

        }
    }
}
} // VanillaStyle