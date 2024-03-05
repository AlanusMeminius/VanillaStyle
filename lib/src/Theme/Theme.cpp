#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle
{
Theme::Theme()
    : configManager(std::make_shared<ConfigManager>())
{
    styleConfig = std::make_shared<VanillaStyle::StyleConfig>(configManager->defaultConfig());
}
void Theme::setConfig(const std::string& configPath)
{
    configManager->setConfigPath(configPath);
    auto error = configManager->readConfig(*styleConfig);
    if (error != ConfigManager::ErrorCode::NoError)
    {
        //        styleConfig = configManager->defaultConfig();
    }
}
Theme::State Theme::stateAdapter(const QStyleOption* option)
{
    State state = NormalState;
    if (!option->state.testFlag(QStyle::State_Enabled))
    {
        state = NormalState;
    }
    if (option->state.testFlag(QStyle::State_MouseOver))
    {
        state = HoverState;
    }
    if (option->state.testFlag(QStyle::State_Sunken))
    {
        state = PressState;
    }
    return state;
}
Theme::Flags Theme::flagsAdapter(const QStyleOption* option)
{
    Flags flags;
    if (option->state.testFlag(QStyle::State_On))
    {
        flags |= State::CheckedFlag;
    }
    if (option->state.testFlag(QStyle::State_Selected))
    {
        flags |= State::SelectedFlag;
    }
    if (option->state.testFlag(QStyle::State_HasFocus))
    {
        flags |= State::FocusFlag;
    }
    return flags;
}
QBrush Theme::getBrush(const QStyleOption* option, const QBrush& brush, QPalette::ColorGroup group, QPalette::ColorRole role) const
{
    return getBrush(stateAdapter(option), option, brush, group, role);
}

QBrush Theme::getBrush(State state, const QStyleOption* option, const QBrush& brush, QPalette::ColorGroup group, QPalette::ColorRole role) const
{
    return getBrush(flagsAdapter(option) | state, brush, group, role);
}
QBrush Theme::getBrush(Flags flags, const QBrush& brush, QPalette::ColorGroup group, QPalette::ColorRole role) const
{
    QColor color = brush.color();
    if (!color.isValid())
    {
        return brush;
    }
    if ((flags & Flag) == HoverState)
    {
        switch (role)
        {
        case QPalette::Button:
            color = styleConfig->color.buttonHoveredColor;
            break;
        default:
            break;
        }

        return color;
    }
    else if ((flags & Flag) == PressState)
    {
    }
    else if ((flags & Flag) == FocusFlag)
    {
    }
    return brush;
}
QColor Theme::getColor(const QStyleOption* option, QPalette::ColorRole role) const
{
    return getBrush(option, option->palette.brush(role), option->palette.currentColorGroup(), role).color();
}

int Theme::getRadius(RadiusRole radiusRole) const
{
    switch (radiusRole)
    {
    case ButtonRadius:
    {
        return styleConfig->size.buttonRadius;
    }
    default:
        return 5;
    }
}
int Theme::getBorder(Theme::BorderRole borderRole) const
{
    switch (borderRole)
    {
    case ButtonBorder:{
        return styleConfig->size.borderWidth;
    }
    default:
        return 0;
    }
}
QColor Theme::checkBtnBgColor(const QStyleOption* option) const
{
    return getColor(option, QPalette::Button);
}

QColor Theme::checkBtnFgColor(const QStyleOption* option) const
{
    return getColor(option, QPalette::ButtonText);
}

}  // namespace VanillaStyle