#pragma once
#include "Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle
{
class ButtonStyle : public Helper
{
public:
    bool drawPushButtonBevel(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget = nullptr) const;

    bool drawPushButtonLabel(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme) const;
};

}
