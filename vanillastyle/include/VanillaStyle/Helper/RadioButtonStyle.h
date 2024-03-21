#pragma once
#include "Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle
{
class RadioButtonStyle : public Helper
{
public:
    bool drawIndicator(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget = nullptr) const;
    // void draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme) const;
    // void drawIndicator(const QStyleOption* option, const QRectF rect, QPainter* painter, const Theme* theme) const;
};
}  // namespace VanillaStyle