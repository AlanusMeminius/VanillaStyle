#include "VanillaStyle/Config/ThemeRepository.h"

ThemeRepository::ThemeRepository()
{
    init();
}
void ThemeRepository::init()
{
    palette.setColor(QPalette::Window, windowBackground());
    palette.setColor(QPalette::Base, baseBackground());
}
QColor ThemeRepository::windowBackground()
{
    return QColor::fromString("#EFF0F1");
}
QColor ThemeRepository::baseBackground()
{
    return QColor::fromString("#fbfbfb");
}