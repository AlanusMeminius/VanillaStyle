#include <QApplication>
#include "Theme.h"
#include "Config/Color.h"
#include "Config/Config.h"
#include "Style/CustomStyle.h"

CustomTheme::CustomTheme() = default;
void CustomTheme::setStyle()
{
    qApp->setStyle(new Theme::CustomStyle);
    qApp->setPalette(Theme::Color::standardPalette());
}
void CustomTheme::setDarkMode(const bool darkMode)
{
    Theme::Color::isDarkMode = darkMode;
    qApp->setPalette(Theme::Color::standardPalette());
}
bool CustomTheme::isDarkMode()
{
    return Theme::Color::isDarkMode;
}
void CustomTheme::setWindowBackgroud(const Theme::ThemeType type, const QString& color)
{
    Theme::Config::Instance().setThemeConifg(type, QStringLiteral("WindowsBackground"), color);
    qApp->setPalette(Theme::Color::standardPalette());
}
