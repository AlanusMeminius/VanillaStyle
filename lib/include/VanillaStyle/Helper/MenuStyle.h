#pragma once
#include <QWidget>
#include <QStyleOption>
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle
{

class MenuStyle
{
public:
    void drawPrimitive(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget = nullptr) const;
    void drawMenuBarItem(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget = nullptr) const;
    void drawMenuItem(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget = nullptr) const;
    void drawMenuSeparator(QPainter* painter, const QRect& rect, QColor const& color, const int thickness) const;
    void eventFilter(QMenu* obj) const;
};

}  // namespace VanillaStyle
