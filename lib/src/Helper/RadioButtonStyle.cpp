#include "VanillaStyle/Helper/RadioButtonStyle.h"
#include <QPainter>
#include <QPainterPath>

bool VanillaStyle::RadioButtonStyle::drawIndicator(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionButton*>(option);
    if (!opt)
    {
        return true;
    }
    const auto rect = QRectF(opt->rect);
    const auto border = theme->getSize(Theme::ButtonBorder);
    const auto margins = QMarginsF(border / 2., border / 2., border / 2., border / 2.);
    const auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

    painter->setRenderHints(QPainter::Antialiasing);
    // theme->setupPainter(option, painter, Theme::RadioButton);
    const auto bgColor = theme->getColor(option, Theme::ButtonBackground);
    const auto fgColor = theme->getColor(option, Theme::ButtonForeground);
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(buttonRect);

    // const auto halfBorder = border / 2.;
    // const auto borderRect = rect.marginsRemoved({halfBorder, halfBorder, halfBorder, halfBorder});
    // painter->setPen(QPen(fgColor, border, Qt::SolidLine));
    // painter->setBrush(Qt::NoBrush);
    // painter->drawEllipse(borderRect);

    // drawIndicator(option, buttonRect, painter, theme);

    if (option->state & QStyle::State_On)
    {
        // const QRect indicatorRect = option->rect;
        // QPainterPath path;
        // path.addEllipse(buttonRect.adjusted(2, 2, -2, -2));
        painter->setBrush(fgColor);
        painter->drawEllipse(buttonRect.adjusted(2, 2, -2, -2));
        // painter->fillPath(path, fgColor);
    }
    return true;
}

// void VanillaStyle::RadioButtonStyle::drawIndicator(const QStyleOption* option, const QRectF rect, QPainter* painter, const VanillaStyle::Theme* theme) const
// {
//     if (option->state & QStyle::State_On)
//     {
//         const QRect indicatorRect = option->rect;
//         QPainterPath path;
//         path.addEllipse(indicatorRect.adjusted(2, 2, -2, -2));
//         const auto gfColor = theme->getColor(option, Theme::ButtonForeground);
//         painter->fillPath(path, gfColor);
//     }
// }
