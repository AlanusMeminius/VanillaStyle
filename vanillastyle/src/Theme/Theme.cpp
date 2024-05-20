#include <iostream>

#include <QFileInfo>
#include <QToolTip>
#include <QPainter>
#include <QScreen>
#include <QFontDatabase>

#include "VanillaStyle/Helper/Common.h"
#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle/Theme/Config.h"
#include "VanillaStyle/Theme/ConfigManager.h"
#include "VanillaStyle/Theme/PatchHelper.h"
#include "VanillaStyle/Theme/Utils.h"

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
    styleConfig = configManager->defaultConfig();
    updatePalette();
    initFont();
}

void Theme::setConfig(const QString& configPath)
{
    styleConfig = configManager->getConfig(configPath);
    update();
    auto callback = [this](const ConfigErrorHanler::ErrorCode& error) {
        if (error != ConfigErrorHanler::ErrorCode::NoError)
        {
            std::cout << "Config Error: " << error << std::endl;
        }
    };
    configManager->setErrorHandler(callback);
}

void Theme::setMode(const Mode mode)
{
    styleConfig = configManager->defaultConfig(mode);
    update();
}

void Theme::update()
{
    PatchHelper::global().init(styleConfig.patch);
    updatePalette();
}

bool Theme::isEnableHotReload() const
{
    return styleConfig.isEnableHotReload;
}

void Theme::updatePalette()
{
    palette.setColor(QPalette::Window, styleConfig.color.backgroundColor);
    palette.setColor(QPalette::Base, styleConfig.color.backgroundColor);

    palette.setColor(QPalette::WindowText, styleConfig.color.primaryTextColor);
    palette.setColor(QPalette::Text, styleConfig.color.primaryTextColor);
    palette.setColor(QPalette::Highlight, styleConfig.color.highlightTextColor);
    palette.setColor(QPalette::ButtonText, styleConfig.color.primaryTextColor);
    palette.setColor(QPalette::ToolTipText, styleConfig.color.primaryTextColor);
    palette.setColor(QPalette::ColorRole::PlaceholderText, styleConfig.color.primaryTextColor);

    QToolTip::setPalette(palette);
}

void Theme::initFont()
{
    // install font
    const std::array<std::string, 4> fontFiles = {"Roboto-Regular.ttf", "Roboto-Medium.ttf", "Roboto-Bold.ttf", "Roboto-Black.ttf"};
    for (const auto& file : fontFiles)
    {
        const auto RobotoFontPath = ":/VanillaStyle/fonts/Roboto/";
        const auto path = RobotoFontPath + file;
        QFontDatabase::addApplicationFont(path.c_str());
    }
#if __WIN32__
    const auto DefaultFont = ":/VanillaStyle/fonts/Inter/";
    const std::array<std::string, 4> DefaultFontFiles = {"Inter-Regular.ttf", "Inter-Medium.ttf", "Inter-Bold.ttf", "Inter-Black.ttf"};
    for (const auto& file : DefaultFontFiles)
    {
        const auto path = DefaultFont + file;
        QFontDatabase::addApplicationFont(path.c_str());
    }
#endif

    const auto regularFont = QFont();
#if __WIN32__
    regularFont = QFont(QStringLiteral("Inter"));
#endif

    const auto fixedFont = QFont(QStringLiteral("Roboto"));

    fontRegular = regularFont;
    fontRegular.setPixelSize(16);
    fontBold = regularFont;
    fontBold.setWeight(QFont::Weight::Bold);
    fontBold.setPixelSize(16);

    fontH1 = regularFont;
    fontH1.setPixelSize(24);
    fontH2 = regularFont;
    fontH2.setPixelSize(20);
    fontH3 = regularFont;
    fontH3.setPixelSize(16);
    fontH4 = regularFont;
    fontH4.setPixelSize(14);
    fontH5 = regularFont;
    fontH5.setPixelSize(12);
    fontH6 = regularFont;
    fontH6.setPixelSize(10);

    fontFixed = fixedFont;
    fontFixed.setPixelSize(16);
}

QPalette Theme::standardPalette() const
{
    return palette;
}

int Theme::getSize(const SizeRole sizeRole) const
{
    switch (sizeRole)
    {
    case SizeRole::NormalRadius:
        return 5;
    case SizeRole::SmallRadius:
        return 3;
    case SizeRole::NormalBorder:
        return 1;
    case SizeRole::NormalPadding:
        return 5;
    case SizeRole::ButtonBorder:
        return 1;
    case SizeRole::CheckBoxBorder:
        return 2;
    case SizeRole::ButtonRadius:
        return 4;
    case SizeRole::ItemViewRadius:
        return styleConfig.size.itemViewRadius;
    case SizeRole::IconSize:
        return styleConfig.size.iconSize;
    case SizeRole::MenuItemPadding:
        return 5;
    case SizeRole::CheckBoxIndicatorMargin:
        return 4;
    case SizeRole::CheckBoxSpacing:
        return 5;
    case SizeRole::ProgressBarHeight:
        return 6;
    case SizeRole::ProgressBarTextMargin:
        return 35;
    case SizeRole::ScrollBarWidth:
        return 5;
    default:
        return 3;
    }
}

QFont Theme::getFont(const TextSizeRole sizeRole)
{
    switch (sizeRole)
    {
    case TextSizeRole::H6:
        fontH6.setPixelSize(styleConfig.size.fontH6);
        return fontH6;
    case TextSizeRole::H5:
        fontH5.setPixelSize(styleConfig.size.fontH5);
        return fontH5;
    case TextSizeRole::H4:
        fontH4.setPixelSize(styleConfig.size.fontH4);
        return fontH4;
    case TextSizeRole::H3:
        fontH3.setPixelSize(styleConfig.size.fontH3);
        return fontH3;
    case TextSizeRole::H2:
        fontH2.setPixelSize(styleConfig.size.fontH2);
        return fontH2;
    case TextSizeRole::H1:
        fontH1.setPixelSize(styleConfig.size.fontH1);
        return fontH1;
    default:
        fontRegular.setPixelSize(styleConfig.size.fontSize);
        return fontRegular;
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
    case ColorRole::PrimaryText:
    {
        color = styleConfig.color.primaryTextColor;
        break;
    }
    case ColorRole::LabelText:
    {
        if ((flags & Flag) == Disabled)
        {
            color = QColor(Qt::gray);
        }
        else if ((flags & Flag) == Hover)
        {
            color = styleConfig.color.hoverTextColor;
        }
        else if ((flags & Flag) == Press)
        {
            color = styleConfig.color.pressedTextColor;
        }
        else
        {
            color = styleConfig.color.textColor;
        }
        break;
    }
    case ColorRole::LabelBackground:
    {
        color = styleConfig.color.labelBackground;
        break;
    }
    case ColorRole::LabelBorderColor:
    {
        color = styleConfig.color.labelBorderColor;
        break;
    }
    case ColorRole::IconColor:
    {
        color = styleConfig.color.iconColor;
        break;
    }
    case ColorRole::IndicatorColor:
    {
        color = styleConfig.color.indicatorColor;
        break;
    }
    case ColorRole::ButtonForeground:
    {
        if ((flags & Flag) == Hover)
        {
            color = styleConfig.color.buttonHoveredForeground;
        }
        else if ((flags & Flag) == Press)
        {
            color = styleConfig.color.buttonPressedForeground;
        }
        else
        {
            color = styleConfig.color.buttonForeground;
        }
        break;
    }
    case ColorRole::ButtonBackground:
    {
        if ((flags & Flag) == Hover)
        {
            color = styleConfig.color.buttonHoveredBackground;
        }
        else if ((flags & Flag) == Press)
        {
            color = styleConfig.color.buttonPressedBackground;
        }
        else
        {
            color = styleConfig.color.buttonBackground;
        }
        break;
    }
    case ColorRole::ButtonBorderColor:
    {
        color = styleConfig.color.buttonBorderColor;
        break;
    }
    case ColorRole::RadioButtonForeground:
    {
        color = styleConfig.color.checkBoxForeground;
        break;
    }
    case ColorRole::CheckBoxForeground:
    {
        color = styleConfig.color.checkBoxCheckedForeground;
        break;
    }
    case ColorRole::RadioButtonBackground:
    {
        if ((flags & Checked) != Checked && (flags & Flag) == Hover)
        {
            color = styleConfig.color.checkBoxHoveredBackground;
        }
        else
        {
            color = styleConfig.color.checkBoxBackground;
        }
        break;
    }
    case ColorRole::CheckBoxBackground:
    {
        if ((flags & Checked) == Checked)
        {
            color = styleConfig.color.checkBoxCheckedBackground;
        }
        else if ((flags & Checked) != Checked && (flags & Flag) == Hover)
        {
            color = styleConfig.color.checkBoxHoveredBackground;
        }
        else
        {
            color = styleConfig.color.checkBoxBackground;
        }
        break;
    }
    case ColorRole::CheckBoxBorderColor:
    {
        if ((flags & Checked) != Checked && (flags & Flag) == Hover)
        {
            color = styleConfig.color.checkBoxHoveredBorderColor;
        }
        else
        {
            color = styleConfig.color.checkBoxBorderColor;
        }
        break;
    }
    case ColorRole::ProgressBarForeground:
    {
        color = styleConfig.color.progressBarForeground;
        break;
    }
    case ColorRole::ProgressBarBackground:
    {
        color = styleConfig.color.progressBarBackground;
        break;
    }
    case ColorRole::ProgressBarText:
    {
        color = styleConfig.color.progressBarText;
        break;
    }
    case ColorRole::LineEditOutline:
    {
        if ((flags & Flag) == Focus)
        {
            color = styleConfig.color.lineEditFocusOutline;
        }
        else
        {
            color = styleConfig.color.lineEditOutline;
        }
        break;
    }
    case ColorRole::ItemViewSelectedColor:
    {
        color = styleConfig.color.itemViewSelectedColor;
        break;
    }
    case ColorRole::ItemViewEvenRowColor:
    {
        color = styleConfig.color.itemViewEvenRowColor;
        break;
    }
    case ColorRole::ItemViewOddRowColor:
    {
        color = styleConfig.color.itemViewOddRowColor;
        break;
    }
    case ColorRole::ScrollBarSliderColor:
    {
        color = styleConfig.color.scrollBarSliderColor;
        break;
    }
    case ColorRole::MenuBackground:
    {
        color = styleConfig.color.menuBackground;
        break;
    }
    case ColorRole::MenuSeparatorColor:
    {
        color = styleConfig.color.menuSeparatorColor;
        break;
    }
    case ColorRole::ComboBoxDropDownBackground:
    {
        color = styleConfig.color.comboBoxDropDownBackground;
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
    case ColorRole::PrimaryText:
        return styleConfig.color.textColor;
    case ColorRole::ButtonForeground:
        return styleConfig.color.buttonForeground;
    case ColorRole::ButtonBackground:
        return styleConfig.color.buttonBackground;
    case ColorRole::LabelText:
        return styleConfig.color.iconLabelText;
    case ColorRole::ToggleButtonBackground:
        return styleConfig.color.toggleButtonBackground;
    case ColorRole::ToggleButtonForeground:
        return styleConfig.color.toggleButtonForeground;
    case ColorRole::ToggleButtonIndicatorColor:
        return styleConfig.color.toggleButtonIndicatorColor;
    case ColorRole::IconColor:
        return styleConfig.color.iconColor;
    case ColorRole::ToggleButtonIconColor:
        return styleConfig.color.toggleButtonIconColor;
    default:
        return Qt::white;
    }
}

QString Theme::checkIconFile(const std::string& path)
{
    QString filePath = QString::fromStdString(path);
    return QFileInfo::exists(filePath) ? filePath : QString();
}

QString Theme::getIconPath(const IconRole role) const
{
    switch (role)
    {
    case IconRole::UpArrow:
    {
        return checkIconFile(styleConfig.icons.upArrow);
    }
    case IconRole::DownArrow:
    {
        return checkIconFile(styleConfig.icons.downArrow);
    }
    case IconRole::ProgressIndicator:
    {
        return checkIconFile(styleConfig.icons.progressIndicator);
    }
    default:
        return {};
    }
}

ProgressMode Theme::getProgressMode() const
{
    return styleConfig.progressBarMode == "mode1" ? ProgressMode::ModeOne : ProgressMode::ModeTwo;
}

void Theme::setPatchConfig(const std::string& propertyValue)
{
    for (const auto& item : styleConfig.patch)
    {
        if (item.enable && item.propertyValue == propertyValue)
        {
            auto original = configManager->getJson();
            original.merge_patch(item.configPatch);
            styleConfig = original.get<StyleConfig>();
        }
    }
}

QString Theme::getCachedIcon(const QString& path, QColor color)
{
    if (iconData.contains(path))
    {
        return iconData.at(path);
    }
    const auto svg = switchSvgColor(path, color);
    iconData.emplace(path, svg);
    return svg;
}

}  // namespace Vanilla