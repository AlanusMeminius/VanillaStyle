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
    painter->setRenderHints(QPainter::Antialiasing);

    const auto rect = QRectF(optionButton->rect);
    const auto border = theme->getSize(Theme::ButtonBorder);
    const auto radius = theme->getSize(Theme::ButtonRadius);

    const auto halfBorder = border / 2.;
    const auto margins = QMarginsF(halfBorder, halfBorder, halfBorder, halfBorder);
    const auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

    const auto bgColor = theme->getColor(option, Theme::ButtonBackground);
    Helper::renderRoundRect(painter, buttonRect, bgColor, radius);
    if (border > 0.1)
    {
        const auto borderColor = theme->getColor(option, Theme::ButtonBorderColor);
        Helper::renderRoundBorder(painter, buttonRect, borderColor, border, radius);
    }
    return true;
}

}  // namespace Vanilla
