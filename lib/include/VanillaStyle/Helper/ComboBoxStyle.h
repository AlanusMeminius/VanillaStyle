#pragma once
#include "Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle
{
class ComboBoxStyle : public Helper
{
public:
    bool draw(const QStyleOptionComplex* option, QPainter* painter, const Theme* theme, const QWidget* widget) const;
};

}  // namespace VanillaStyle
