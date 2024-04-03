#pragma once

#include <memory>

class QPainter;
class QStyleOption;
class QWidget;

namespace Vanilla
{
class Theme;

class ButtonStyle
{
public:
    bool drawPushButtonBevel(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget = nullptr) const;

    bool drawPushButtonLabel(const QStyleOption* option, QPainter* painter, const QWidget* widget, const std::shared_ptr<Theme>& theme) const;
};

}
