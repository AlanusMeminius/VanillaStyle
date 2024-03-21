#pragma once
#include "VanillaStyle/Theme/Theme.h"

#include <QComboBox>
namespace VanillaStyle
{

class Helper
{
public:
    virtual ~Helper() = default;
    bool emptyControl(const QStyleOption*, QPainter*, const Theme* theme, const QWidget*) const
    {
        return true;
    };
    bool shapedFrame(const QStyleOption*, QPainter*, const Theme* theme, const QWidget*) const;
};


}  // namespace VanillaStyle
