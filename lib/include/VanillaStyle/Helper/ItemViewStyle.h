#pragma once
#include <QWidget>
#include <QStyleOption>
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle {
class ItemViewStyle {
public:
    void draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme) const;
    void drawPrimitive(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget = nullptr) const;

};

} // VanillaStyle
