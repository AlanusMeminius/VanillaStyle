#include <QApplication>
#include "MainWindow.h"
#include "VanillaStyle/Style.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    VanillaStyle::Style::setStyle();
    MainWindow w;
    w.show();
    return QApplication::exec();
}
