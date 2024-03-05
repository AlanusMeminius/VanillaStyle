#pragma once
#include <QWidget>
#include <QStyleOption>
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle
{
//class QStyleOption;
//class QStyleOptionButton;


class CheckBoxStyle
{
public:
    void draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme) const;
    void drawIndicator(const QStyleOption* option, const QRectF rect, QPainter* painter, const Theme* theme) const;
    [[nodiscard]] int indicatorSize() const;
};

}  // namespace VanillaStyle
