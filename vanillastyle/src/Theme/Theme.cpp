#include <QFileInfo>
#include <QToolTip>
#include <QPainter>

#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle/Theme/Config.h"

namespace Vanilla
{
Theme::State Theme::state(const QStyleOption* option)
{
    State state = Normal;
    if (!option->state.testFlag(QStyle::State_Enabled))
    {
        return Disabled;
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
    auto defalutConfig = configManager->defaultConfig();
    styleConfig = std::make_shared<StyleConfig>(defalutConfig);
    initPalette();
}

void Theme::setConfig(const std::string& configPath)
{
    auto config = configManager->getConfig(configPath);
    styleConfig = std::make_shared<StyleConfig>(config);
    auto callback = [this](const ConfigErrorHanler::ErrorCode& error) {
        if (error != ConfigErrorHanler::ErrorCode::NoError)
        {
        }
    };
    configManager->errorHandler.setErrorCallback(callback);
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

int Theme::getSize(const SizeRole sizeRole) const
{
    switch (sizeRole)
    {
    case ButtonBorder:
        return styleConfig->size.borderWidth;
    case MenuItemPadding:
        return 5;
    case IconSize:
        return styleConfig->size.iconSize;
    default:
        return 3;
    }
}

QFont Theme::getFont(const TextSizeRole sizeRole)
{
    QFont font;
    font.setWeight(QFont::Weight::Normal);
    font.setPointSize(12);
    switch (sizeRole)
    {
    case H5:
        font.setPointSize(10);
        break;
    default:
        break;
    }
    return font;
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
            color = styleConfig->color.hoverTextColor;
        }
        else if ((flags & Flag) == Press)
        {
            color = styleConfig->color.pressedTextColor;
        }
        else
        {
            color = styleConfig->color.textColor;
        }
        break;
    }
    case LabelText:
    {
        if ((flags & Flag) == Disabled)
        {
            color = QColor(Qt::gray);
        }
        else
        {
            color = QColor(Qt::black);
        }
        break;
    }
    case ButtonForeground:
    {
        if ((flags & Flag) == Hover)
        {
            color = styleConfig->color.buttonHoveredForeground;
        }
        else if ((flags & Flag) == Press)
        {
            color = styleConfig->color.buttonPressedForeground;
        }
        else
        {
            color = styleConfig->color.buttonForeground;
        }
        break;
    }
    case ButtonBackground:
    {
        if ((flags & Flag) == Hover)
        {
            color = styleConfig->color.buttonHoveredBackground;
        }
        else if ((flags & Flag) == Press)
        {
            color = styleConfig->color.buttonPressedBackground;
        }
        else
        {
            color = styleConfig->color.buttonBackground;
        }
        break;
    }
    case ProgressBarForeground:
    {
        color = styleConfig->color.progressBarForeground;
        break;
    }
    case ProgressBarBackground:
    {
        color = styleConfig->color.progressBarBackground;
        break;
    }
    case ProgressBarText:
    {
        color = styleConfig->color.progressBarText;
        break;
    }
    case LineEditOutline:
    {
        if ((flags & Flag) == Focus)
        {
            color = styleConfig->color.lineEditFocusOutline;
        }
        else
        {
            color = styleConfig->color.lineEditOutline;
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
        return styleConfig->color.textColor;
    }
    case ButtonForeground:
        return styleConfig->color.buttonForeground;
    case ButtonBackground:
        return styleConfig->color.buttonBackground;
    case LabelText:
        return styleConfig->color.iconLabelText;
    default:
        return Qt::white;
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
}  // namespace Vanilla