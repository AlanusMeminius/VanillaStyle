#pragma once

#include "VanillaStyle/vglobal.h"

class QPainter;
class QStyleOption;
class QWidget;

namespace Vanilla
{
class Theme;
class VANILLA_EXPORT CheckBoxStyle
{
public:
    bool draw(const QStyleOption* option, QPainter* painter,const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    void drawIndicator(const QStyleOption* option, QRectF rect, QPainter* painter, const std::shared_ptr<Theme>& theme) const;
    [[nodiscard]] int indicatorSize() const;
};

}  // namespace VanillaStyle
