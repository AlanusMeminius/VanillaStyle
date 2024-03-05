#include <QApplication>
#include "VanillaStyle/Style.h"
#include "VanillaStyle/Style/VanillaStyle.h"

void VanillaStyle::Style::setStyle()
{
    auto style = new VanillaStyle();
//    style->setConfigPath("config.json");
//    qApp->setPalette(style->palette())
    qApp->setStyle(style);
}