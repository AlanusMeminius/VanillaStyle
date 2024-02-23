#pragma once
#include "Config/Config.h"

#include <QObject>


class CustomTheme : public QObject
{
    Q_OBJECT
public:
    explicit CustomTheme();
    static void setStyle();
    static void setDarkMode(bool darkMode);

    [[nodiscard]] static bool isDarkMode() ;

    static void setWindowBackgroud(Theme::ThemeType type, const QString& color);
};
