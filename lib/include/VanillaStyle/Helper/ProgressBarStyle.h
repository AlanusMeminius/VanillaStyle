#pragma once
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle
{

class ProgressBarStyle
{
public:
    void drawGroove(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme);
    void drawContents(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme);
    void drawText(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme);
    QRect subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget);
};

}  // namespace VanillaStyle
