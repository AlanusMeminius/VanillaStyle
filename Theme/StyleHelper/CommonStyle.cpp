#include "CommonStyle.h"
#include "Config/Color.h"
#include <QPainter>

namespace Theme
{
void CommonStyle::setupPainterForShape(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget)
{
    Q_UNUSED(widget)
    if (!(option->state & QStyle::State_Enabled))
    {
        painter->setPen(Color::buttonOutlineColor());
        painter->setBrush(Color::buttonBackground());
        painter->setOpacity(0.5);
    }
    else if (option->state & QStyle::State_Sunken)
    {
        painter->setPen(Color::pressedOutlineColor());
        painter->setBrush(Color::buttonPressedBackground());
    }
    else if ((option->state & QStyle::State_MouseOver) || (option->state & QStyle::State_HasFocus))
    {
        painter->setPen(QPen(Color::hoverOutlineBrush(option->rect), 1));
        painter->setBrush(Color::buttonHoveredBackground());
    }
    else
    {
        painter->setPen(Color::buttonOutlineColor());
        painter->setBrush(Color::buttonBackground());
    }
}
}  // namespace Theme
