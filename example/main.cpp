#include <QApplication>
#include "MainWindow.h"
#include "VanillaStyle/Style/VanillaStyle.h"
//#include "CustomStyle.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    auto style = new VanillaStyle::VanillaStyle();
    qApp->setStyle(style);
    QApplication::setPalette(style->getStandardPalette());
    w.show();
    w.setTheme(true);
    return QApplication::exec();
}
