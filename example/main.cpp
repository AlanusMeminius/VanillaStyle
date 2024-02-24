#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"
#include "Theme.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    CustomTheme::setStyle();
    MainWindow w;
    w.show();
    return QApplication::exec();
}
