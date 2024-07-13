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
    bool draw(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
};

}  // namespace Vanilla
