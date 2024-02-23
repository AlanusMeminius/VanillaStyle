#include "Config.h"

#include <QApplication>
#include <QFile>

Theme::Config& Theme::Config::Instance()
{
    static Config instance;
    return instance;
}

void Theme::Config::setLightThemeConfig(const ThemeConfig& config) const
{
    mLightSettings->setValue(QStringLiteral("WindowsBackground"), config.windowBackground);
    mLightSettings->setValue(QStringLiteral("BaseBackground"), config.baseBackground);
    mLightSettings->setValue(QStringLiteral("BaseText"), config.baseText);
    mLightSettings->setValue(QStringLiteral("ButtonPressedBackground"), config.buttonPressedBackground);
}
void Theme::Config::setDarkThemeConfig(const ThemeConfig& config) const
{
    mDarkSettings->setValue(QStringLiteral("WindowsBackground"), config.windowBackground);
    mDarkSettings->setValue(QStringLiteral("BaseBackground"), config.baseBackground);
    mDarkSettings->setValue(QStringLiteral("BaseText"), config.baseText);
    mDarkSettings->setValue(QStringLiteral("ButtonPressedBackground"), config.buttonPressedBackground);
}
Theme::ThemeConfig Theme::Config::LightTheme() const
{
    return ThemeConfig{mLightSettings->value(QStringLiteral("WindowsBackground")).toString(),
                       mLightSettings->value(QStringLiteral("BaseBackground")).toString(), mLightSettings->value(QStringLiteral("BaseText")).toString(),
                       mLightSettings->value(QStringLiteral("ButtonPressedBackground")).toString()};
}
Theme::ThemeConfig Theme::Config::DarkTheme() const
{
    return ThemeConfig{mDarkSettings->value(QStringLiteral("WindowsBackground")).toString(), mDarkSettings->value(QStringLiteral("BaseBackground")).toString(),
                       mDarkSettings->value(QStringLiteral("BaseText")).toString(), mDarkSettings->value(QStringLiteral("ButtonPressedBackground")).toString()};
}
void Theme::Config::setThemeConifg(ThemeType type, const QString& key, const QString& value) const
{
    if (type == Light)
    {
        mLightSettings->setValue(key, value);
        mLightSettings->sync();
    } else
    {
        mDarkSettings->setValue(key, value);
        mDarkSettings->sync();
    }

}

Theme::Config::Config()
{
    initThemeConfig(Light);
    initThemeConfig(Dark);
}
void Theme::Config::initThemeConfig(const ThemeType type)
{
    const auto appConfigPath = QApplication::applicationDirPath() + "/config/";
    QString configPath = type == Light ? appConfigPath + "LightTheme.ini" : appConfigPath + "DarkTheme.ini";
    if (type == Light)
    {
        mLightSettings = std::make_shared<QSettings>(configPath, QSettings::IniFormat);
    }
    else
    {
        mDarkSettings = std::make_shared<QSettings>(configPath, QSettings::IniFormat);
    }

    // Default theme config
    if (!QFile::exists(configPath))
    {
        if (type == Light)
        {
            const ThemeConfig LightConfig{
                QStringLiteral("#EFF0F1"),
                QStringLiteral("#fbfbfb"),
                QStringLiteral("#252525"),
                QStringLiteral("#F8F7F8"),
            };
            setLightThemeConfig(LightConfig);
        }

        if (type == Dark)
        {
            const ThemeConfig DarkConfig{
                QStringLiteral("#182129"),
                QStringLiteral("#0f0f0f"),
                QStringLiteral("#A5A5A5"),
                QStringLiteral("#171717"),
            };
            setDarkThemeConfig(DarkConfig);
        }
    }
}
