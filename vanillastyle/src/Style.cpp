#include <QApplication>
#include "VanillaStyle/Style.h"
#include "VanillaStyle/Style/VanillaStyle.h"

void Vanilla::Style::setStyle()
{
    set({});
}
void Vanilla::Style::setStyleFromName(const QString& styleName)
{
    const auto configPath = QApplication::applicationDirPath() + "/" + styleName + ".json";
    set(configPath);
}
void Vanilla::Style::setStyleFromPath(const QString& configPath)
{
    set(configPath);
}
void Vanilla::Style::set(const QString& configPath)
{
    const auto style = new VanillaStyle();
    if (!configPath.isEmpty())
    {
        style->setConfigPath(configPath.toStdString());
    }
    qApp->setStyle(style);
}