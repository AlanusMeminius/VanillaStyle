#pragma once
#include <QStyle>
#include <QStyleOptionProgressBar>

namespace Theme
{

class ProgressbarStyle
{
public:
    void drawGroove(const QStyleOptionProgressBar* option, QPainter* painter, const QWidget* widget);
    void drawContents(const QStyleOptionProgressBar* option, QPainter* painter, const QWidget* widget);
    void drawText(const QStyleOptionProgressBar* option, QPainter* painter, const QWidget* widget);
    QRect subElementRect(QStyle::SubElement subElement, const QStyleOptionProgressBar* option, const QWidget* widget);
};

}  // namespace Theme
