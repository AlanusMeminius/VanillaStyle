#include "VanillaStyle/Helper/ButtonStyle.h"
#include <QPainter>
#include <QPainterPath>

namespace VanillaStyle
{
void ButtonStyle::draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme)
{
    if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
    {
        const auto rect = QRectF(optionButton->rect);
        const auto border = theme->getBorder(Theme::ButtonBorder);
        const auto radius = theme->getRadius(Theme::ButtonRadius);

        const auto margins = QMarginsF(border / 2., border / 2., border / 2., border / 2.);
        const auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

        painter->setRenderHints(QPainter::Antialiasing);
        // theme->setupButtonPainter(option, painter);
        const auto bgColor = theme->getColor(option, Theme::ButtonBackground);
        painter->setBrush(QBrush(bgColor));
        QPainterPath path;
        path.addRoundedRect(buttonRect,radius,radius);
        painter->fillPath(path, QBrush(bgColor));
        // painter->drawRoundedRect(buttonRect, radius, radius);
    }
}

}  // namespace VanillaStyle
