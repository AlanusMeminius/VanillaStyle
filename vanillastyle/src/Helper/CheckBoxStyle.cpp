#include <QPainter>
#include <QPainterPath>

#include "VanillaStyle/Helper/CheckBoxStyle.h"

#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace Vanilla
{
bool CheckBoxStyle::draw(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    return Helper::drawCheckBox(option, painter, theme, widget);
}

}  // namespace Vanilla