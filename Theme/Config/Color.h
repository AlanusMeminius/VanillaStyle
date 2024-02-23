#pragma once
#include <QColor>
#include <QBrush>

namespace Theme
{

class Color
{
public:
    static bool isDarkMode;
    static QPalette standardPalette();
    static QColor windowBackground();
    static QColor baseBackground();
    static QColor baseText();
    static QColor pressedTextColor();
    static QColor hoverTextColor();
    static QColor pressedOutlineColor();
    static QBrush hoverOutlineBrush(const QRect& rect);
    static QColor buttonPressedBackground();
    static QColor buttonOutlineColor();
    static QColor buttonHoveredBackground();
    static QColor buttonBackground();
    static QColor swichButtonHandleColor();
    static QColor swichButtonCheckedBackground();
    static QColor toogleButtonBackground();
    static QColor toogleButtonHandleColor();
    static QColor progressBarTextColor(bool enabled);
    static QBrush progressBarOutlineBrush(const QRect& rect);
    static QBrush progressBarOutlineFadingBrush(const QRect& rect);
    static QBrush progressBarContentsBrush(const QRect& rect);
};

}  // namespace Theme
