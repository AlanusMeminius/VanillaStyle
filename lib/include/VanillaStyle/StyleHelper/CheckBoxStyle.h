#pragma once
#include <QWidget>
#include <QStyleOption>

namespace VanillaStyle
{
//class QStyleOption;
//class QStyleOptionButton;


class CheckBoxStyle
{
public:
    void draw(const QStyleOption* option, QPainter* painter, const QWidget* widget) const;
    void drawIndicator(const QStyleOption* option, QPainter* painter) const;
    [[nodiscard]] int indicatorSize() const;
};

}  // namespace VanillaStyle
