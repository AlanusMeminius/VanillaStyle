#include "VanillaStyle/Helper/RadioButtonStyle.h"
#include <QPainter>
#include <QPainterPath>

void VanillaStyle::RadioButtonStyle::draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const VanillaStyle::Theme* theme) const
{
    if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
    {
        const auto rect = QRectF(optionButton->rect);
        const auto border = theme->getBorder(Theme::ButtonBorder);
        const auto margins = QMarginsF(border / 2., border / 2., border / 2., border / 2.);
        const auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

        painter->setRenderHints(QPainter::Antialiasing);
        // theme->setupPainter(option, painter, Theme::RadioButton);
        const auto bgColor = theme->getColor(option, Theme::ButtonBackground);
        const auto gfColor = theme->getColor(option, Theme::ButtonForeground);
        painter->setPen(Qt::NoPen);
        painter->setBrush(bgColor);
        painter->drawEllipse(buttonRect);

        const auto halfBorder = border / 2.;
        const auto borderRect = rect.marginsRemoved({ halfBorder, halfBorder, halfBorder, halfBorder });
        painter->setPen(QPen(gfColor, border, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(borderRect);

        drawIndicator(option, buttonRect, painter, theme);
    }
}
void VanillaStyle::RadioButtonStyle::drawIndicator(const QStyleOption* option, const QRectF rect, QPainter* painter, const VanillaStyle::Theme* theme) const
{
    if (option->state & QStyle::State_On)
    {
        const QRect indicatorRect = option->rect;
        QPainterPath path;
        path.addEllipse(indicatorRect.adjusted(2, 2, -2, -2));
        const auto gfColor = theme->getColor(option, Theme::ButtonForeground);
        painter->fillPath(path, gfColor);
    }
}
