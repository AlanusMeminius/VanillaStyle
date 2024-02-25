#include <QApplication>
#include "MainWindow.h"
#include "VanillaStyle/Style.h"
#include "VanillaStyle/Config/Config.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    VanillaStyle::Style::setStyle();


//    auto config = nlohmann::json::parse(j2);
//    auto c = VanillaStyle::StyleConfig(j2);
//    qDebug() << c.author;
    MainWindow w;
    w.show();
    return QApplication::exec();
}
