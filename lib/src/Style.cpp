#include <QApplication>
#include "VanillaStyle/Style.h"
#include "VanillaStyle/Style/CustomStyle.h"

void VanillaStyle::Style::setStyle()
{
    auto style = new CustomStyle();
    style->setConfigPath("config.json");
    qApp->setStyle(style);
}