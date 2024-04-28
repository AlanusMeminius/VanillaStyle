#include <QApplication>
#include "VanillaStyle/Style.h"
#include "VanillaStyle/Style/VanillaStyle.h"

void Vanilla::Style::setStyle(const Mode mode)
{
    set(nullptr,mode);
}

void Vanilla::Style::setStyleFromName(const QString& styleName, const Mode mode)
{
    const auto configPath = QApplication::applicationDirPath() + "/" + styleName + ".json";
    set(configPath, mode);
}

void Vanilla::Style::setStyleFromPath(const QString& configPath, const Mode mode)
{
    set(configPath, mode);
}

void Vanilla::Style::set(const QString& configPath, const Mode mode)
{
    const auto style = new VanillaStyle(mode);
    if (!configPath.isEmpty())
    {
        style->setConfigPath(configPath.toStdString());
    }
    qApp->setStyle(style);
}