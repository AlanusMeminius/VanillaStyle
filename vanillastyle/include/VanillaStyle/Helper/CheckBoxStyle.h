#pragma once
#include "VanillaStyle/Theme/Theme.h"
#include "Helper.h"

namespace Vanilla
{

class CheckBoxStyle : public Helper
{
public:
    bool draw(const QStyleOption* option, QPainter* painter,const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    void drawIndicator(const QStyleOption* option, QRectF rect, QPainter* painter, const std::shared_ptr<Theme>& theme) const;
    [[nodiscard]] int indicatorSize() const;
};

}  // namespace VanillaStyle
