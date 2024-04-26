#pragma once

#include "Config.h"

#include <QPalette>
#include <QStyleOption>

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
        Checked = 0x00000300,
        FlagBase = 0xf00000,
    };
    Q_DECLARE_FLAGS(StateFlags, State)

    static State state(const QStyleOption* option);
    static StateFlags flags(const QStyleOption* option);
    enum ColorRole
    {
        Text,
        LabelText,
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

    enum RadiusRole
    {
        NormalRadius,
        ButtonRadius,
        MenuItemRadius,
        ProgressRadius
    };

    enum SizeRole
    {
        NormalBorder,
        ButtonBorder,
        CheckBoxBorder,
        MenuItemPadding,
        IconSize,
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
    void setConfig(const std::string& configPath);

    QPalette palette;
    void initPalette();
    [[nodiscard]] QPalette standardPalette() const;
    [[nodiscard]] int getRadius(RadiusRole radiusRole) const;
    [[nodiscard]] int getSize(SizeRole sizeRole) const;

    QFont getFont(TextSizeRole sizeRole);

    QColor getColor(const QStyleOption* option, ColorRole role) const;
    QColor createColor(State state, const QStyleOption* option, ColorRole role) const;
    QColor createColor(StateFlags flags, const QStyleOption* option, ColorRole role) const;

    [[nodiscard]] QColor customColor(ColorRole role) const;

    [[nodiscard]] QString checkIconFile(const std::string& path) const;
    [[nodiscard]] QString getIconPath(IconRole role) const;

    [[nodiscard]] ProgressMode getProgressMode() const;

private:
    std::shared_ptr<ConfigManager> configManager;
    StyleConfig styleConfig;
};
}  // namespace Vanilla