#include "ProgressbarStyle.h"
#include <QDebug>
#include <QPainter>
#include "Config/Color.h"

namespace Theme
{

void ProgressbarStyle::drawGroove(const QStyleOptionProgressBar* option, QPainter* painter, const QWidget* widget)
{
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Color::buttonOutlineColor());
    painter->setBrush(QBrush(Color::baseBackground()));
    const qreal radius = option->rect.height() / 2;
    painter->drawRoundedRect(QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);
}
void ProgressbarStyle::drawContents(const QStyleOptionProgressBar* option, QPainter* painter, const QWidget* widget)
{
    Q_UNUSED(widget);
    const auto value = option->progress - option->minimum;
    const auto range = option->maximum - option->minimum;
    if (value > 0)
    {
        painter->save();
        const QRect usableRect = option->rect.adjusted(3, 3, -3, -3);
        QRect progressRect = usableRect;
        progressRect.setWidth(double(value) / double(range) * usableRect.width());

        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(QPen(Color::progressBarOutlineBrush(option->rect), 1));
        painter->setBrush(Color::progressBarContentsBrush(option->rect));
        const qreal radius = option->rect.height() / 2 - 2.5;
        painter->drawRoundedRect(QRectF(progressRect).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);

        // Additional trick: the groove itself gets a gradient until the current X value
        QRect repaintedGrooveRect = option->rect;
        repaintedGrooveRect.setWidth(double(value) / double(range) * repaintedGrooveRect.width());
        painter->setClipRect(repaintedGrooveRect);
        painter->setPen(QPen(Color::progressBarOutlineFadingBrush(option->rect), 1));
        painter->setBrush(Qt::NoBrush);
        painter->setOpacity(0.43);
        painter->drawRoundedRect(QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);

        painter->restore();
    }
}
void ProgressbarStyle::drawText(const QStyleOptionProgressBar* option, QPainter* painter, const QWidget* widget)
{
    Q_UNUSED(widget)
    const QPen oldPen = painter->pen();
    painter->setPen(Color::progressBarTextColor(option->state & QStyle::State_Enabled));
    painter->drawText(option->rect, Qt::AlignRight | Qt::AlignVCenter | Qt::TextSingleLine, option->text);
    painter->setPen(oldPen);
}
QRect ProgressbarStyle::subElementRect(QStyle::SubElement subElement, const QStyleOptionProgressBar* option, const QWidget* widget)
{
    Q_UNUSED(widget)
    if (subElement == QStyle::SE_ProgressBarLabel)
        return option->rect.adjusted(0, 0, -6, 0);  // right-align before the round rect
    // The area for both groove and content is the whole rect. The drawing will take care of actual contents rect.
    return option->rect;
}

}  // namespace Theme
