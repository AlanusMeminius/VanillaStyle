#pragma once

#include "Config.h"

#include <QStyleOption>
#include <QPalette>
#include <QFont>

namespace Vanilla
{
class ConfigManager;

class Theme
{
public:
    enum State
    {
        Normal = 0x00000000,
        Hover = 0x00000001,
        Press = 0x00000002,
        Disabled = 0x00000003,
        StateBase = 0x000000f0,

        Flag = 0x000000ff,
        Selected = 0x00000100,
        Focus = 0x00000200,
        Checked = 0x00000400,
        FlagBase = 0xf00000,
    };
    Q_DECLARE_FLAGS(StateFlags, State)

    static State state(const QStyleOption* option);
    static StateFlags flags(const QStyleOption* option);

    enum ColorRole
    {
        PrimaryText,
        LabelText,

        IndicatorColor,
        ButtonForeground,
        ButtonBackground,
        ButtonBorderColor,

        CheckBoxForeground,
        CheckBoxBackground,
        CheckBoxBorderColor,

        RadioButtonForeground,
        RadioButtonBackground,
        RadioButtonBorderColor,

        ProgressBarForeground,
        ProgressBarBackground,
        ProgressBarText,

        LineEditOutline,

        ToggleButtonBackground,
        ToggleButtonForeground,
        ToggleButtonBorderColor,
        ToggleButtonIndicatorColor,

        ItemViewEvenRowColor,
        ItemViewOddRowColor,
        ItemViewSelectedColor,

        ComboBoxDropDownBackground
    };

    enum TextSizeRole
    {
        Default,
        H1,
        H2,
        H3,
        H4,
        H5,
        H6
    };

    enum SizeRole
    {
        NormalRadius,
        NormalBorder,
        NormalPadding,
        IconSize,

        ButtonTextMargin,
        ButtonBorder,
        CheckBoxBorder,

        ButtonRadius,
        ItemViewRadius,

        MenuItemPadding,
        CheckBoxIndicatorMargin,
        CheckBoxSpacing,
        ProgressBarHeight,
        ProgressBarTextMargin
    };

    enum IconRole
    {
        UpArrow,
        DownArrow,
        ProgressIndicator,
    };

    enum ProgressMode
    {
        ModeOne,
        ModeTwo
    };

    explicit Theme();
    void setConfig(const QString& configPath);
    void setMode(Mode mode);
    [[nodiscard]] bool isEnableHotReload() const;

    void initPalette();
    void initFont();
    [[nodiscard]] QPalette standardPalette() const;

    QFont getFont(TextSizeRole sizeRole);

    [[nodiscard]] int getSize(SizeRole sizeRole) const;

    QColor getColor(const QStyleOption* option, ColorRole role) const;
    QColor createColor(State state, const QStyleOption* option, ColorRole role) const;
    QColor createColor(StateFlags flags, const QStyleOption* option, ColorRole role) const;
    [[nodiscard]] QColor customColor(ColorRole role) const;

    [[nodiscard]] QString checkIconFile(const std::string& path) const;
    [[nodiscard]] QString getIconPath(IconRole role) const;
    QString getCachedIcon(const QString&, QColor color);

    [[nodiscard]] ProgressMode getProgressMode() const;

private:
    QPalette palette;

    QFont fontRegular;
    QFont fontFixed;
    QFont fontBold;

    QFont fontH1;
    QFont fontH2;
    QFont fontH3;
    QFont fontH4;
    QFont fontH5;
    QFont fontH6;

    std::shared_ptr<ConfigManager> configManager;
    StyleConfig styleConfig;

    std::unordered_map<QString, QString> iconData;
};
}  // namespace Vanilla