#pragma once
#include <QString>
#include <QSettings>

namespace Theme
{
enum ThemeType
{
    Light,
    Dark
};

struct ThemeConfig
{
    QString windowBackground;
    QString baseBackground;
    QString baseText;
    QString buttonPressedBackground;
};

class Config
{
public:
    static Config& Instance();
    void setLightThemeConfig(const ThemeConfig& config) const;
    void setDarkThemeConfig(const ThemeConfig& config) const;
    [[nodiscard]] ThemeConfig LightTheme() const;
    [[nodiscard]] ThemeConfig DarkTheme() const;

    void setThemeConifg(ThemeType type,const QString& key, const QString& value) const;

private:
    Config();
    void initThemeConfig(ThemeType type);

    std::shared_ptr<QSettings> mLightSettings;
    std::shared_ptr<QSettings> mDarkSettings;
};
}  // namespace Theme
