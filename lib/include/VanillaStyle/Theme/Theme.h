#pragma once
#include "Config.h"
#include "Utils.h"
#include <QPalette>
#include <QStyleOption>
namespace VanillaStyle
{
class Theme
{
public:
    enum State
    {
        NormalState = 0x00000000,
        HoverState = 0x00000001,
        PressState = 0x00000002,
        DisabledState = 0x00000003,
        StateCustomBase = 0x000000f0,

        Flag = 0x000000ff,
        CheckedFlag = 0x00000100,
        SelectedFlag = 0x00000200,
        FocusFlag = 0x00000300,
        FlagCustomBase = 0xf00000
    };
    Q_DECLARE_FLAGS(Flags, State)

    static State stateAdapter(const QStyleOption *option);
    static Flags flagsAdapter(const QStyleOption *option);

    enum RadiusRole {
        NormalRadius,
        ButtonRadius,
        MenuItemRadius
    };

    enum BorderRole {
        NormalBorder,
        ButtonBorder,
    };

    explicit Theme();
    void setConfig(const std::string& configPath);

    QPalette palette;
    void initPalette();
    QPalette standardPalette() const;
    [[nodiscard]] int getRadius(RadiusRole radiusRole) const;
    [[nodiscard]] int getBorder(BorderRole borderRole) const;
    QBrush getBrush(const QStyleOption* option, const QBrush& brush, QPalette::ColorGroup group, QPalette::ColorRole role) const;
    QBrush getBrush(State state, const QStyleOption* option, const QBrush& brush, QPalette::ColorGroup group, QPalette::ColorRole role) const;
    [[nodiscard]] QBrush getBrush(Flags flags, const QBrush& brush, QPalette::ColorGroup group, QPalette::ColorRole role) const;
    QColor getColor(const QStyleOption *option, QPalette::ColorRole role) const;

    QColor checkBtnBgColor(const QStyleOption* option) const;
    QColor checkBtnFgColor(const QStyleOption* option) const;
private:
    std::shared_ptr<ConfigManager> configManager;
    std::shared_ptr<StyleConfig> styleConfig;
};
}  // namespace VanillaStyle