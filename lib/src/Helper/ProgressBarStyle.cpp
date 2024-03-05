#include "VanillaStyle/Helper/ProgressBarStyle.h"
#include <QPainter>

namespace VanillaStyle
{
void ProgressBarStyle::drawGroove(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme)
{
    if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
    {
        auto radius = theme->getRadius(Theme::ButtonRadius);
        painter->setRenderHint(QPainter::Antialiasing);
        // buttonOutlineColor
        painter->setPen(QColor(198, 220, 186));
        // baseBackground
        painter->setBrush(QBrush(QColor(198, 220, 186)));
        painter->drawRoundedRect(QRectF(progressBarOption->rect), radius, radius);
    }
}
void ProgressBarStyle::drawContents(const QStyleOption* option, QPainter* painter, const QWidget* widget)
{
    Q_UNUSED(widget);
    if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
    {

    const auto value = progressBarOption->progress - progressBarOption->minimum;
    const auto range = progressBarOption->maximum - progressBarOption->minimum;
    if (value > 0)
    {
        painter->save();
        const QRect usableRect = progressBarOption->rect.adjusted(3, 3, -3, -3);
        QRect progressRect = usableRect;
        progressRect.setWidth(double(value) / double(range) * usableRect.width());

        painter->setRenderHint(QPainter::Antialiasing);
        // progressBarOutlineBrush
        painter->setPen(QPen(QColor(198, 210, 186)));
        // progressBarContentsBrush
        painter->setBrush(QColor(198, 200, 186));
        const qreal radius = progressBarOption->rect.height() / 2 - 2.5;
        painter->drawRoundedRect(QRectF(progressRect).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);

        // Additional trick: the groove itself gets a gradient until the current X value
        QRect repaintedGrooveRect = option->rect;
        repaintedGrooveRect.setWidth(double(value) / double(range) * repaintedGrooveRect.width());
        painter->setClipRect(repaintedGrooveRect);
        // progressBarOutlineFadingBrush
        painter->setPen(QPen(QColor(198, 210, 156)));
        painter->setBrush(Qt::NoBrush);
        painter->setOpacity(0.43);
        painter->drawRoundedRect(QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);

        painter->restore();
    }

    }
}
void ProgressBarStyle::drawText(const QStyleOption* option, QPainter* painter, const QWidget* widget)
{
    Q_UNUSED(widget)
    if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
    {
        const QPen oldPen = painter->pen();
        // progressBarTextColor
        painter->setPen(QColor(198, 210, 126));
        painter->drawText(progressBarOption->rect, Qt::AlignRight | Qt::AlignVCenter | Qt::TextSingleLine, progressBarOption->text);
        painter->setPen(oldPen);
    }

}
QRect ProgressBarStyle::subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget)
{
    Q_UNUSED(widget)
    if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
    {
        if (subElement == QStyle::SE_ProgressBarLabel) {
            return progressBarOption->rect.adjusted(0, 0, -6, 0);  // right-align before the round rect
        }
        // The area for both groove and content is the whole rect. The drawing will take care of actual contents rect.
        return progressBarOption->rect;
    }
    return option->rect;
}
}  // namespace VanillaStyle