#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>

#include "VanillaStyle/Helper/ButtonStyle.h"

#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace Vanilla
{
bool ButtonStyle::drawPushButtonBevel(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    Q_UNUSED(widget);
    const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option);
    if (!optionButton)
    {
        return true;
    }
    const auto rect = QRectF(optionButton->rect);
    const auto border = theme->getSize(Theme::ButtonBorder);
    const auto radius = theme->getRadius(Theme::ButtonRadius);

    const auto margins = QMarginsF(border / 2., border / 2., border / 2., border / 2.);
    const auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

    painter->setRenderHints(QPainter::Antialiasing);
    const auto bgColor = theme->getColor(option, Theme::ButtonBackground);
    Helper::renderRoundRect(painter, buttonRect, bgColor, radius);
    if (border > 0.1)
    {
        const auto borderColor = theme->getColor(option, Theme::ButtonForeground);
        Helper::renderRoundBorder(painter, buttonRect, borderColor, border, radius);
    }
    return true;
}

bool ButtonStyle::drawPushButtonLabel(const QStyleOption* option, QPainter* painter, const QWidget* widget, const std::shared_ptr<Theme>& theme) const
{
    Q_UNUSED(widget);
    Q_UNUSED(painter);
    Q_UNUSED(theme);
    if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
    {
        QStyleOptionButton copy = *optionButton;
        theme->adjustTextPalette(&copy);
        // QCommonStyle::drawControl(QStyle::CE_PushButtonLabel, &copy, painter, widget);
    }
    return true;
}

}  // namespace Vanilla
