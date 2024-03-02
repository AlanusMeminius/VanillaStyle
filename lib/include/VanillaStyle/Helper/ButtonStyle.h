#pragma once

class ButtonStyle
{
    class QPainter;
    class QStyleOption;
    class QWidget;
public:
    void drawButtonShape(const QStyleOption* option, QPainter* painter, const QWidget* widget);
};
