#pragma once

#include <memory>

class QPainter;
class QStyleOption;
class QWidget;

namespace Vanilla
{
class Theme;

class Helper
{
public:
    bool emptyControl(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*) const;
    bool shapedFrame(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>& theme, const QWidget*) const;
    bool drawRadioCheckLabel(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*) const;
};

}  // namespace Vanilla
