#include "VanillaStyle/Theme/Theme.h"
#include <QFileInfo>
#include <QToolTip>
#include <QPainter>

namespace VanillaStyle
{
Theme::State Theme::state(const QStyleOption* option)
{
    State state = Normal;
    if (!option->state.testFlag(QStyle::State_Enabled))
    {
        return Normal;
    }
    if (option->state.testFlag(QStyle::State_MouseOver))
    {
        state = Hover;
    }
    if (option->state.testFlag(QStyle::State_Sunken))
    {
        state = Press;
    }
    return state;
}
Theme::StateFlags Theme::flags(const QStyleOption* option)
{
    StateFlags flags{0};

    if (option->state.testFlag(QStyle::State_On))
    {
        flags |= Checked;
    }

    if (option->state.testFlag(QStyle::State_Selected))
    {
        flags |= Selected;
    }

    if (option->state.testFlag(QStyle::State_HasFocus))
    {
        flags |= Focus;
    }
    return flags;
}
Theme::Theme()
    : configManager(std::make_shared<ConfigManager>())
{
    styleConfig = std::make_shared<StyleConfig>(configManager->defaultConfig());
    colorConfig = std::make_shared<Color>(styleConfig->color);
    initPalette();
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
void Theme::initPalette()
{
    palette.setColor(QPalette::Window, Qt::transparent);
    palette.setColor(QPalette::Base, styleConfig->color.backgroundColor);
    palette.setColor(QPalette::WindowText, styleConfig->color.textColor);
    palette.setColor(QPalette::Text, styleConfig->color.textColor);
    palette.setColor(QPalette::Highlight, QColor(0x53, 0x94, 0x9f));

    // Text color on buttons
    palette.setColor(QPalette::ButtonText, styleConfig->color.textColor);

    // pal.setColor(QPalette::ToolTipBase, baseBackground());
    palette.setColor(QPalette::ToolTipText, styleConfig->color.textColor);

    QToolTip::setPalette(palette);
}

void Theme::adjustTextPalette(QStyleOptionButton* option) const
{
    QColor textColor;
    if (state(option) == Press)
    {
        textColor = styleConfig->color.pressedTextColor;
    }
    else if (state(option) == Hover)
    {
        textColor = styleConfig->color.hoverTextColor;
    }
    else
    {
        textColor = styleConfig->color.buttonForeground;
    }
    option->palette.setColor(QPalette::ButtonText, textColor);
}

QPalette Theme::standardPalette() const
{
    return palette;
}
int Theme::getRadius(const RadiusRole radiusRole) const
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
int Theme::getBorder(const BorderRole borderRole) const
{
    switch (borderRole)
    {
    case ButtonBorder:
    {
        return styleConfig->size.borderWidth;
    }
    default:
        return 1;
    }
}
QColor Theme::getColor(const QStyleOption* option, const ColorRole role) const
{
    return createColor(state(option), option, role);
}
QColor Theme::createColor(const State state, const QStyleOption* option, const ColorRole role) const
{
    return createColor(flags(option) | state, option, role);
}
QColor Theme::createColor(StateFlags flags, const QStyleOption* option, ColorRole role) const
{
    QColor color = option->palette.color(QPalette::Base);
    switch (role)
    {
    case Text:
    {
        if ((flags & Flag) == Hover)
        {
            color = colorConfig->hoverTextColor;
        }
        else if ((flags & Flag) == Press)
        {
            color = colorConfig->pressedTextColor;
        }
        else
        {
            color = colorConfig->buttonForeground;
        }
        break;
    }
    case ButtonForeground:
    {
        if ((flags & Flag) == Hover)
        {
            color = colorConfig->buttonHoveredForeground;
        }
        else if ((flags & Flag) == Press)
        {
            color = colorConfig->buttonPressedForeground;
        }
        else
        {
            color = colorConfig->buttonForeground;
        }
        break;
    }
    case ButtonBackground:
    {
        if ((flags & Flag) == Hover)
        {
            color = colorConfig->buttonHoveredBackground;
        }
        else if ((flags & Flag) == Press)
        {
            color = colorConfig->buttonPressedBackground;
        }
        else
        {
            color = colorConfig->buttonBackground;
        }
        break;
    }
    case ProgressBarForeground:
    {
        color = colorConfig->progressBarForeground;
        break;
    }
    case ProgressBarBackground:
    {
        color = colorConfig->progressBarBackground;
        break;
    }
    case ProgressBarText:
    {
        color = colorConfig->progressBarText;
        break;
    }
    case LineEditOutline:
    {
        if ((flags & Flag) == Focus)
        {
            color = colorConfig->lineEditFocusOutline;
        }
        else
        {
            color = colorConfig->lineEditOutline;
        }
        break;
    }
    default:
        break;
    }
    return color;
}
QColor Theme::customColor(const ColorRole role) const
{
    switch (role)
    {
    case Text:
    {
        return colorConfig->textColor;
    }
    case ButtonForeground:
        return colorConfig->buttonForeground;
    case ButtonBackground:
        return colorConfig->buttonBackground;
    default:
        return {};
    }
}
QString Theme::checkIconFile(const std::string& path) const
{
    if (const QFileInfo file(QString::fromStdString(path)); file.exists())
    {
        return QString::fromStdString(path);
    }
    return {};
}
QString Theme::getIconPath(const IconRole role) const
{
    switch (role)
    {
    case UpArrow:
    {
        return checkIconFile(styleConfig->icons.upArrow);
    }
    case DownArrow:
    {
        return checkIconFile(styleConfig->icons.downArrow);
    }
    case ProgressIndicator:
    {
        return checkIconFile(styleConfig->icons.progressIndicator);
    }
    default:
        return {};
    }
}
}  // namespace VanillaStyle