#include <QApplication>
#include "MainWindow.h"
#include "VanillaStyle/Style/VanillaStyle.h"
//#include "CustomStyle.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
//    VanillaStyle::Style::setStyle();
    auto style = new VanillaStyle::VanillaStyle();
//    auto style = new CustomStyle();
    qApp->setStyle(style);
//    app.setStyle(style);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
