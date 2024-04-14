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
        CheckBoxBorder,
        RadioButtonForeground,
        RadioButtonBackground,
        RadioButtonBorder,
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
        MenuItemRadius
    };

    enum SizeRole
    {
        NormalBorder,
        ButtonBorder,
        MenuItemPadding,
        IconSize,
        CheckBoxIndicatorMargin,
        CheckBoxSpacing,
    };

    enum IconRole
    {
        UpArrow,
        DownArrow,
        ProgressIndicator,
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

    QString checkIconFile(const std::string& path) const;
    QString getIconPath(IconRole role) const;

    void adjustTextPalette(QStyleOptionButton* option) const;

private:
    std::shared_ptr<ConfigManager> configManager;
    StyleConfig styleConfig;
};
}  // namespace Vanilla