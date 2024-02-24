#pragma once
#include <QStyleOptionButton>

namespace Theme
{

class CommonStyle
{
public:
    void setupPainterForShape(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget);
    void drawFrame(const QStyleOption* option, QPainter* painter) const;
    void drawDownArrow(const QRectF& rect, QPainter* painter) const;
    void drawUpArrow(const QRectF& rect, QPainter* painter) const;
};

}  // namespace Theme
