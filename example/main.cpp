#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"
#include "Theme.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    CustomTheme::setStyle();
    // qApp->setStyle(new Theme::CustomStyle());
    // qApp->setPalette(Theme::Color::standardPalette());
    MainWindow w;
    w.show();
    return QApplication::exec();
}
