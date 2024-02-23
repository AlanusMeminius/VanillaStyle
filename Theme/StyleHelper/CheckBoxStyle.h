#pragma once

#include "CommonStyle.h"

class QStyleOption;
class QPainter;
class QStyleOptionButton;

namespace Theme
{

class CustomStyle;

class CheckBoxStyle
{
public:
    explicit CheckBoxStyle();
    void draw(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget) const;
    void drawIndicator(const QStyleOption* option, QPainter* painter) const;
    [[nodiscard]] int indicatorSize() const;

private:
    std::shared_ptr<CommonStyle> commonStyle;
};

}  // namespace Theme
