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
        Normal = 0x00000000,
        Hover = 0x00000001,
        Press=0x00000002,
        StateBase = 0x000000f0,

        Flag = 0x000000ff,
        Selected = 0x00000100,
        Focus =0x00000200,
        Checked = 0x00000300,
        FlagBase = 0xf00000,
    };
    Q_DECLARE_FLAGS(StateFlags, State)

    static State state(const QStyleOption *option);
    static StateFlags flags(const QStyleOption* option);
    enum ColorRole
    {
        Text,
        ButtonForeground,
        ButtonBackground,
    };

    enum PainterRole
    {
        Button,
        RadioButton,
        CheckBox,
    };

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
    [[nodiscard]] QPalette standardPalette() const;
    [[nodiscard]] int getRadius(RadiusRole radiusRole) const;
    [[nodiscard]] int getBorder(BorderRole borderRole) const;

    QColor getColor(const QStyleOption* option, ColorRole role) const;
    QColor createColor(State state, const QStyleOption* option, ColorRole role) const;
    QColor createColor(StateFlags flags, const QStyleOption* option, ColorRole role) const;

    void setupPainter(const QStyleOption* option, QPainter* painter, PainterRole role) const;
    void setupButtonPainter(const QStyleOption* option, QPainter* painter) const;
    void setupRaioPainter(const QStyleOption* option, QPainter* painter) const;

    void adjustTextPalette(QStyleOptionButton* option) const;
private:
    std::shared_ptr<ConfigManager> configManager;
    std::shared_ptr<StyleConfig> styleConfig;
    std::shared_ptr<Color> colorConfig = nullptr;
};
}  // namespace VanillaStyle