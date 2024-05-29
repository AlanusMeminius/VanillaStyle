#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>

#include "VanillaStyle/Helper/ButtonStyle.h"
#include "VanillaStyle/Helper/Common.h"
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
    const auto border = theme->getSize(SizeRole::ButtonBorder);
    const auto radius = theme->getSize(SizeRole::ButtonRadius);

    const auto halfBorder = border / 2.;
    const auto margins = QMarginsF(halfBorder, halfBorder, halfBorder, halfBorder);
    const auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

    // draw background
    const auto bgColor = theme->getColor(option, ColorRole::ButtonBackground);
    Helper::renderRoundRect(painter, buttonRect, bgColor, radius);

    // draw border
    if (border > 0.1)
    {
        const auto borderColor = theme->getColor(option, ColorRole::ButtonBorderColor);
        Helper::renderRoundBorder(painter, buttonRect, borderColor, border + 0.5, radius);
    }
    return true;
}

bool ButtonStyle::drawPushButtonLabel(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionButton*>(option);
    if (opt == nullptr)
    {
        return true;
    }

    const auto fgColor = theme->getColor(option, ColorRole::ButtonForeground);
    const auto pixmap = getIconPixmap(opt->icon, opt->iconSize, widget);
    const auto colorizedPixmap = getColorizedPixmap(pixmap, widget, fgColor, theme->getIconsColorizeMode());
    const auto pixmapPixelRatio = colorizedPixmap.devicePixelRatio();
    const auto iconWidth = colorizedPixmap.isNull() ? 0 : static_cast<int>(colorizedPixmap.width() / pixmapPixelRatio);
    const auto textWidth = opt->fontMetrics.boundingRect(opt->rect, Qt::AlignCenter, opt->text).width();
    const auto isTextEmpty = opt->text.isEmpty();
    const auto isIconWithText = iconWidth > 0 && !isTextEmpty && textWidth > 0;
    const auto isIconFirst = widget->layoutDirection() == Qt::RightToLeft;
    const auto padding = theme->getSize(SizeRole::NormalPadding);
    const auto iconPadding = textWidth > 0 ? padding : 0;
    auto rect = QRect(0, 0, iconWidth + textWidth + iconPadding, opt->rect.height());
    rect.moveCenter(opt->rect.center());

    painter->setRenderHints(QPainter::Antialiasing);

    int pixmapWidth = 0;
    int pixmapHeight = 0;
    QRect iconOuterRect = rect.adjusted(padding, padding, -padding, -padding);
    QRect textOuterRect = rect.adjusted(padding, padding, -padding, -padding);

    // calculate icon rectangle
    if (iconWidth > 0)
    {
        pixmapWidth = pixmapPixelRatio != 0 ? static_cast<int>(static_cast<qreal>(colorizedPixmap.width()) / pixmapPixelRatio) : 0;
        pixmapHeight = pixmapPixelRatio != 0 ? static_cast<int>(static_cast<qreal>(colorizedPixmap.height()) / pixmapPixelRatio) : 0;
    }
    // calculate text rectangle
    if (isIconWithText)
    {
        const auto iconLeft = isIconFirst ? rect.x() : rect.x() + textWidth + padding;
        iconOuterRect = QRect(iconLeft, rect.y(), pixmapWidth + padding, rect.height());
        const auto textLeft = isIconFirst ? rect.x() + pixmapWidth + padding : rect.x();
        textOuterRect = QRect(textLeft, rect.y(), textWidth + padding, rect.height());
    }

    if (textWidth > 0)
    {
        constexpr auto textFlags = Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | Qt::TextHideMnemonic;
        const auto elidedText = opt->fontMetrics.elidedText(opt->text, Qt::ElideRight, rect.width(), Qt::TextSingleLine);
        painter->setBrush(Qt::NoBrush);
        const auto fgcolor = theme->getColor(option, ColorRole::LabelText);
        painter->setPen(fgcolor);
        const auto textTect = centerRect(textOuterRect, textWidth, rect.height());
        painter->drawText(textTect, textFlags, elidedText);
    }

    if (iconWidth > 0)
    {
        const auto iconRect = centerRect(iconOuterRect, pixmapWidth, pixmapHeight);
        painter->drawPixmap(iconRect, colorizedPixmap);
    }
    return true;
}

}  // namespace Vanilla
