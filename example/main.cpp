#include <QApplication>
#include "MainWindow.h"
#include "VanillaStyle/Style/VanillaStyle.h"
//#include "CustomStyle.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    w.setAutoTheme();
    return QApplication::exec();
}
