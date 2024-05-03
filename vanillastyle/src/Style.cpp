#include <QApplication>
#include "VanillaStyle/Style.h"
#include "VanillaStyle/Style/VanillaStyle.h"

#include <QFile>
#include <iostream>

void Vanilla::Style::setDefaultTheme(const Mode mode)
{
    const auto style = getStyle();
    style->setMode(mode);
    qApp->setStyle(style);
}

void Vanilla::Style::setStyleFromAppDir(const QString& styleName)
{
    const auto configPath = QApplication::applicationDirPath() + "/" + styleName + ".json";
    setStyleFromPath(configPath);
}

void Vanilla::Style::setStyleFromPath(const QString& configPath)
{
    const auto style = getStyle();
    if (QFile::exists(configPath))
    {
        style->setConfigPath(configPath);
        qApp->setStyle(style);
    }
    else
    {
        setDefaultTheme(Light);
        std::cout << "StyleConfigFile not found: " << configPath.toStdString() << std::endl;
    }
}

Vanilla::VanillaStyle* Vanilla::Style::getStyle()
{
    auto* previousStyle = qApp->style();
    auto* vanillaStyle = qobject_cast<VanillaStyle*>(previousStyle);
    if (vanillaStyle == nullptr)
    {
        vanillaStyle = new VanillaStyle();
    }
    return vanillaStyle;
}