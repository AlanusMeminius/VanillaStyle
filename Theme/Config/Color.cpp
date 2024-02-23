#include "Config/Color.h"
#include "Config.h"
#include <QToolTip>

namespace Theme
{
bool Color::isDarkMode = false;

QPalette Color::standardPalette()
{
    QPalette pal;
    pal.setColor(QPalette::Window, windowBackground());
    pal.setColor(QPalette::Base, baseBackground());
    pal.setColor(QPalette::WindowText, baseText());
    pal.setColor(QPalette::Text, baseText());
    pal.setColor(QPalette::Highlight, QColor(0x53, 0x94, 0x9f));

    // Text color on buttons
    pal.setColor(QPalette::ButtonText, baseText());

    // pal.setColor(QPalette::ToolTipBase, baseBackground());
    pal.setColor(QPalette::ToolTipText, baseText());

    QToolTip::setPalette(pal);

    return pal;
}
QColor Color::windowBackground()
{
    return isDarkMode ? QColor::fromString(Config::Instance().DarkTheme().windowBackground) :
                        QColor::fromString(Config::Instance().LightTheme().windowBackground);
}
QColor Color::baseBackground()
{
    return isDarkMode ? QColor::fromString(Config::Instance().DarkTheme().baseBackground) : QColor::fromString(Config::Instance().LightTheme().baseBackground);
}
QColor Color::baseText()
{
    return isDarkMode ? QColor::fromString(Config::Instance().DarkTheme().baseText) : QColor::fromString(Config::Instance().LightTheme().baseText);
}
QColor Color::pressedTextColor()
{
    return QColor(0x65, 0x65, 0x65);  // medium gray
}
QColor Color::hoverTextColor()
{
    return QColor(0xdd, 0xdd, 0xdd);  // light gray
}
QColor Color::pressedOutlineColor()
{
    return QColor(0x32, 0x2d, 0x35);
}
QBrush Color::hoverOutlineBrush(const QRect& rect)
{  // Instructions from the designer:
    // "Draw line passing by center of rectangle (+4% to the right)
    // and that is perpendicular to the topleft-bottomright diagonal.
    // This line intersects the top and bottom in two points, which are the gradient stops"

    const qreal w = rect.width();
    const qreal h = rect.height();
    const qreal xmid = w * 0.54;
    const qreal xoffset = (h * h) / (2 * w);  // Proportionality: xoffset / (h/2) = h / w
    const qreal x0 = xmid - xoffset;
    const qreal x1 = xmid + xoffset;

    QLinearGradient gradient(x0, h, x1, 0);
    gradient.setColorAt(0.0, QColor(0x53, 0x94, 0x9f));
    gradient.setColorAt(1.0, QColor(0x75, 0x55, 0x79));
    return QBrush(gradient);
}
QColor Color::buttonPressedBackground()
{
    return isDarkMode ? QColor::fromString(Config::Instance().DarkTheme().buttonPressedBackground) :
                        QColor::fromString(Config::Instance().LightTheme().buttonPressedBackground);
}
QColor Color::buttonOutlineColor()
{
    return isDarkMode ? QColor(0x59, 0x51, 0x5f) : QColor(0x9f, 0x95, 0xa3);
}
QColor Color::buttonHoveredBackground()
{
    QColor color = buttonPressedBackground();
    color.setAlphaF(0.2);
    return color;
}
QColor Color::buttonBackground()
{
    return isDarkMode ? QColor(0x21, 0x1f, 0x22, 0xa7) : QColor(0xf5, 0xf4, 0xf5);
}
QColor Color::swichButtonHandleColor()
{
    return isDarkMode ? QColor(0x53, 0x94, 0x9f) : QColor(0x75, 0x55, 0x79);
}
QColor Color::swichButtonCheckedBackground()
{
    return isDarkMode ? QColor(38, 80, 115) : QColor(198, 220, 186);
}
QColor Color::toogleButtonBackground()
{
    return isDarkMode ? QColor(0x21, 0x1f, 0x22, 0xa7) : QColor(229, 230, 235);
}
QColor Color::toogleButtonHandleColor()
{
    return isDarkMode ? QColor(0x53, 0x94, 0x9f) : QColor(247, 222, 208);
}
QColor Color::progressBarTextColor(bool enabled)
{
    QColor textColor = baseText();
    if (!enabled)
        textColor.setAlphaF(textColor.alphaF() / 2.0);
    return textColor;
}
QBrush Color::progressBarOutlineBrush(const QRect& rect)
{
    QLinearGradient gradient(0, rect.height(), rect.width(), 0);
    gradient.setColorAt(0.0, QColor(0x11, 0xc2, 0xe1));
    gradient.setColorAt(1.0, QColor(0x89, 0x3a, 0x94));
    return {gradient};
}
QBrush Color::progressBarOutlineFadingBrush(const QRect& rect)
{
    QLinearGradient gradient(0, rect.height(), rect.width(), 0);
    gradient.setColorAt(0.0, QColor(0x11, 0xc2, 0xe1));
    gradient.setColorAt(1.0, QColor(0x89, 0x3a, 0x94));
    return {gradient};
}
QBrush Color::progressBarContentsBrush(const QRect& rect)
{
    QLinearGradient gradient(0, rect.height(), rect.width(), 0);
    gradient.setColorAt(0.0, QColor(0x11, 0xc2, 0xe1, 0x60));
    gradient.setColorAt(1.0, QColor(0x89, 0x3a, 0x94, 0x60));
    return {gradient};
}
}  // namespace Theme
