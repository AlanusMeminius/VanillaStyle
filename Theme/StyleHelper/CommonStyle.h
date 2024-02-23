#pragma once
#include <QStyleOptionButton>

namespace Theme
{

class CommonStyle
{
public:
    void setupPainterForShape(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget);
};

}  // namespace Theme
