#include "VanillaStyle/Theme/Utils.h"
#include <QStyleOption>

namespace VanillaStyle
{
State stateAdapter(const QStyleOption* option)
{
    State state = State::Normal;
    if (!option->state.testFlag(QStyle::State_Enabled))
    {
        return State::Normal;
    }
    else if (option->state.testFlag(QStyle::State_Sunken))
    {
        state = State::Press;
    }
    else if (option->state.testFlag(QStyle::State_MouseOver))
    {
        state = State::Hover;
    }
    return state;
}
Flags flagsAdapter(const QStyleOption* option)
{
    Flags flags = Flags::Checked;

    if (option->state.testFlag(QStyle::State_On)) {
        flags = Flags::Checked;
    }
    if (option->state.testFlag(QStyle::State_Selected))
    {
        flags = Flags::Selected;
    }
    if (option->state.testFlag(QStyle::State_HasFocus))
    {
        flags = Flags::Focus;
    }
    return flags;
}
}  // namespace VanillaStyle