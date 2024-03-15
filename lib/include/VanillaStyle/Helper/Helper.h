#pragma once
#include "VanillaStyle/Theme/Theme.h"
namespace VanillaStyle
{

class Helper
{
public:
    virtual ~Helper() = default;
    bool emptyControl(const QStyleOption*, QPainter*, const Theme* theme, const QWidget*) const
    {
        return true;
    }
};

}  // namespace VanillaStyle
