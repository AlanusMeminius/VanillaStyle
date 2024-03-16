#pragma once
#include "Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle {
class ItemViewStyle : public Helper{
public:
    bool draw(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const;
    void drawPrimitive(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget = nullptr) const;
};

} // VanillaStyle
