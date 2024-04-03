#include <QPainter>

#include "VanillaStyle/Helper/RadioButtonStyle.h"
#include "VanillaStyle/Theme/Theme.h"

bool Vanilla::RadioButtonStyle::drawIndicator(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
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

QRect Vanilla::RadioButtonStyle::subElementRect(QStyle::SubElement element, const QStyleOption* option, const std::shared_ptr<Theme>& theme,
                                                const QWidget* widget) const
{
    Q_UNUSED(widget);
    if (element == QStyle::SE_RadioButtonIndicator)
    {
        const auto indicatorSize = theme->getSize(Theme::IconSize);
        const auto indicatorY = option->rect.y() + (option->rect.height() - indicatorSize) / 2;
        return QRect{option->rect.x(), indicatorY, indicatorSize, indicatorSize};
    }
    // SE_RadioButtonContents
    const auto indicatorSize = theme->getSize(Theme::IconSize);
    const auto border = theme->getSize(Theme::NormalBorder);
    return option->rect.marginsRemoved({indicatorSize + border, 0, 0, 0});
}
