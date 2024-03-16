#include <QApplication>
#include "VanillaStyle/Style.h"
#include "VanillaStyle/Style/VanillaStyle.h"

void VanillaStyle::Style::setStyle()
{
    set({});
}
void VanillaStyle::Style::setStyleFromName(const QString& styleName)
{
    const auto configPath = QApplication::applicationDirPath() + "/" + styleName + ".json";
    set(configPath);
}
void VanillaStyle::Style::setStyleFromPath(const QString& configPath)
{
    set(configPath);
}
void VanillaStyle::Style::set(const QString& configPath)
{
    const auto style = new VanillaStyle();
    if (!configPath.isEmpty())
    {
        style->setConfigPath(configPath.toStdString());
    }
    qApp->setStyle(style);
    QApplication::setPalette(style->getStandardPalette());
}