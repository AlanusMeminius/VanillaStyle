#pragma once
#include <QStyle>
#include "VanillaStyle/Helper/Common.h"

namespace VanillaStyle
{
enum class State
{
    Normal,
    Hover,
    Press,
    Disable

};

enum class Flags {
    Checked,
    Selected,
    Focus
};
State stateAdapter(const QStyleOption *option);
Flags flagsAdapter(const QStyleOption *option);
//Q_DECLARE_FLAGS(Flag, Flags)
}

