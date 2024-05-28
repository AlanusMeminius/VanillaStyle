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

void Theme::setPatchHelper(const std::shared_ptr<PatchHelper>& helper)
{
    patchHelper = helper;
}

void Theme::setMode(const Mode mode)
{
    styleConfig = configManager->defaultConfig(mode);
    update();
}

void Theme::update()
{
    patchHelper->init(styleConfig.patch);
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
    const auto& config = styleConfig.size;
    switch (sizeRole)
    {
    case SizeRole::NormalRadius:
        return config.normalRadius;
    case SizeRole::SmallRadius:
        return config.smallRadius;
    case SizeRole::NormalBorder:
        return config.normalBorder;
    case SizeRole::NormalPadding:
        return config.normalPadding;
    case SizeRole::ButtonBorder:
        return config.buttonBorder;
    case SizeRole::CheckBoxBorder:
        return config.checkBoxBorder;
    case SizeRole::ButtonRadius:
        return config.buttonRadius;
    case SizeRole::ItemViewRadius:
        return config.itemViewRadius;
    case SizeRole::IconSize:
        return config.iconSize;
    case SizeRole::MenuItemPadding:
        return config.menuItemPadding;
    case SizeRole::CheckBoxIndicatorMargin:
        return config.checkBoxIndicatorMargin;
    case SizeRole::CheckBoxPadding:
        return config.checkBoxPadding;
    case SizeRole::ProgressBarHeight:
        return config.progressBarHeight;
    case SizeRole::ProgressBarTextMargin:
        return config.progressBarTextMargin;
    case SizeRole::ScrollBarWidth:
        return config.scrollBarWidth;
    default:
        return 3;
    }
}

QFont Theme::getFont(const TextSizeRole sizeRole)
{
    const auto& config = styleConfig.size;
    switch (sizeRole)
    {
    case TextSizeRole::H6:
        fontH6.setPixelSize(config.fontH6);
        return fontH6;
    case TextSizeRole::H5:
        fontH5.setPixelSize(config.fontH5);
        return fontH5;
    case TextSizeRole::H4:
        fontH4.setPixelSize(config.fontH4);
        return fontH4;
    case TextSizeRole::H3:
        fontH3.setPixelSize(config.fontH3);
        return fontH3;
    case TextSizeRole::H2:
        fontH2.setPixelSize(config.fontH2);
        return fontH2;
    case TextSizeRole::H1:
        fontH1.setPixelSize(config.fontH1);
        return fontH1;
    default:
        fontRegular.setPixelSize(config.fontSize);
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
    const auto& config = styleConfig.color;
    switch (role)
    {
    case ColorRole::PrimaryText:
    {
        color = config.primaryTextColor;
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
            color = config.hoverTextColor;
        }
        else if ((flags & Flag) == Press)
        {
            color = config.pressedTextColor;
        }
        else
        {
            color = config.textColor;
        }
        break;
    }
    case ColorRole::LabelBackground:
    {
        color = config.labelBackground;
        break;
    }
    case ColorRole::LabelBorderColor:
    {
        color = config.labelBorderColor;
        break;
    }
    case ColorRole::IconColor:
    {
        color = config.iconColor;
        break;
    }
    case ColorRole::IndicatorColor:
    {
        color = config.indicatorColor;
        break;
    }
    case ColorRole::ButtonForeground:
    {
        if ((flags & Flag) == Hover)
        {
            color = config.buttonHoveredForeground;
        }
        else if ((flags & Flag) == Press)
        {
            color = config.buttonPressedForeground;
        }
        else
        {
            color = config.buttonForeground;
        }
        break;
    }
    case ColorRole::ButtonBackground:
    {
        if ((flags & Flag) == Hover)
        {
            color = config.buttonHoveredBackground;
        }
        else if ((flags & Flag) == Press)
        {
            color = config.buttonPressedBackground;
        }
        else
        {
            color = config.buttonBackground;
        }
        break;
    }
    case ColorRole::ButtonBorderColor:
    {
        color = config.buttonBorderColor;
        break;
    }
    case ColorRole::RadioButtonForeground:
    {
        color = config.checkBoxForeground;
        break;
    }
    case ColorRole::CheckBoxForeground:
    {
        color = config.checkBoxCheckedForeground;
        break;
    }
    case ColorRole::RadioButtonBackground:
    {
        if ((flags & Checked) != Checked && (flags & Flag) == Hover)
        {
            color = config.checkBoxHoveredBackground;
        }
        else
        {
            color = config.checkBoxBackground;
        }
        break;
    }
    case ColorRole::CheckBoxBackground:
    {
        if ((flags & Checked) == Checked)
        {
            color = config.checkBoxCheckedBackground;
        }
        else if ((flags & Checked) != Checked && (flags & Flag) == Hover)
        {
            color = config.checkBoxHoveredBackground;
        }
        else
        {
            color = config.checkBoxBackground;
        }
        break;
    }
    case ColorRole::CheckBoxBorderColor:
    {
        if ((flags & Checked) != Checked && (flags & Flag) == Hover)
        {
            color = config.checkBoxHoveredBorderColor;
        }
        else
        {
            color = config.checkBoxBorderColor;
        }
        break;
    }
    case ColorRole::ProgressBarForeground:
    {
        color = config.progressBarForeground;
        break;
    }
    case ColorRole::ProgressBarBackground:
    {
        color = config.progressBarBackground;
        break;
    }
    case ColorRole::ProgressBarText:
    {
        color = config.progressBarText;
        break;
    }
    case ColorRole::LineEditOutline:
    {
        if ((flags & Focus) != Focus)
        {
            color = config.lineEditFocusOutline;
        }
        else
        {
            color = config.lineEditOutline;
        }
        break;
    }
    case ColorRole::LineEditBackground:
    {
        if ((flags & Focus) != Focus)
        {
            color = config.lineEditFocusBackground;
        }
        else
        {
            color = config.lineEditBackground;
        }
        break;
    }
    case ColorRole::ItemViewSelectedColor:
    {
        color = config.itemViewSelectedColor;
        break;
    }
    case ColorRole::ItemViewEvenRowColor:
    {
        color = config.itemViewEvenRowColor;
        break;
    }
    case ColorRole::ItemViewOddRowColor:
    {
        color = config.itemViewOddRowColor;
        break;
    }
    case ColorRole::ScrollBarSliderColor:
    {
        color = config.scrollBarSliderColor;
        break;
    }
    case ColorRole::MenuBackground:
    {
        color = config.menuBackground;
        break;
    }
    case ColorRole::MenuSeparatorColor:
    {
        color = config.menuSeparatorColor;
        break;
    }
    case ColorRole::MenuShortCutsBackground:
    {
        color = config.menuShortCutsBackground;
        break;
    }
    case ColorRole::ComboBoxDropDownBackground:
    {
        color = config.comboBoxDropDownBackground;
        break;
    }
    default:
        break;
    }
    return color;
}

QColor Theme::customColor(const ColorRole role) const
{
    const auto& config = styleConfig.color;
    switch (role)
    {
    case ColorRole::PrimaryText:
        return config.textColor;
    case ColorRole::ButtonForeground:
        return config.buttonForeground;
    case ColorRole::ButtonBackground:
        return config.buttonBackground;
    case ColorRole::LabelText:
        return config.iconLabelText;
    case ColorRole::ToggleButtonBackground:
        return config.toggleButtonBackground;
    case ColorRole::ToggleButtonForeground:
        return config.toggleButtonForeground;
    case ColorRole::ToggleButtonIndicatorColor:
        return config.toggleButtonIndicatorColor;
    case ColorRole::IconColor:
        return config.iconColor;
    case ColorRole::ToggleButtonIconColor:
        return config.toggleButtonIconColor;
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
    case IconRole::LeftArrow:
    {
        return checkIconFile(styleConfig.icons.leftArrow);
    }
    case IconRole::RightArrow:
    {
        return checkIconFile(styleConfig.icons.rightArrow);
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