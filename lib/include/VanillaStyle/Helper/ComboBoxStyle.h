#pragma once
#include <QWidget>
#include <QStyleOption>
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle {
class VanillaStyle;
class ComboBoxStyle {

public:
    void draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme, const VanillaStyle* style) const;
};

} // VanillaStyle
