#pragma once
#include "Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle
{

class MenuStyle : public Helper
{
public:
    bool drawPrimitive(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget = nullptr) const;
    bool drawMenuBarItem(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget = nullptr) const;
    bool drawMenuItem(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget = nullptr) const;
    void drawMenuSeparator(QPainter* painter, const QRect& rect, QColor const& color, int thickness) const;
    void eventFilter(QMenu* obj) const;
};

}  // namespace VanillaStyle
