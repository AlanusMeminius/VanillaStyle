#include "SwitchButtonStyle.h"
#include <QPainter>

namespace Theme
{
void SwitchButtonStyle::drawGroove(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget)
{
    Q_UNUSED(widget)
    painter->setPen(Qt::NoPen);
    if (option->state & QStyle::State_On)
        painter->setBrush(QColor("#77d472"));

    if (option->state & QStyle::State_Off)
    {
        painter->setPen(QPen(QColor("#e5e5e5"), 2));
        painter->setBrush(QColor("#fdfefd"));
    }

    painter->drawRoundedRect(option->rect.adjusted(1, 1, -1, -1), option->rect.height() / 2.0, option->rect.height() / 2.0);
}
void SwitchButtonStyle::drawHandle(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget)
{
    Q_UNUSED(widget)
    painter->setPen(Qt::NoPen);
    if (option->state & QStyle::State_On)
        painter->setBrush(QColor("#fefffe"));

    if (option->state & QStyle::State_Off)
        painter->setPen(QPen(QColor("#e5e5e5"), 2));

    QRect rectHandle = option->rect.adjusted(1, 1, -1, -1);
    int r = qMin(rectHandle.width() / 2.0, rectHandle.height() / 2.0);
    painter->drawEllipse(rectHandle.center(), r, r);
}
QRect SwitchButtonStyle::subElementRect(QStyle::SubElement subElement, const QStyleOptionButton* option, const QWidget* widget)
{
    Q_UNUSED(widget)
    if (subElement == SE_SwitchButtonHandle)
    {
        int handleWidth = indicatorSize(PM_SwitchButtonHandleWidth);
        QRect rectHandle(0, 0, 0, 0);
        rectHandle.setHeight(option->rect.height());

        if (option->rect.width() / 2.0 <= handleWidth)
            rectHandle.setWidth(option->rect.width() / 2.0);
        else
            rectHandle.setWidth(handleWidth);

        if (option->state & QStyle::State_Off)
            rectHandle.moveLeft(option->rect.left() + 5);
        if (option->state & QStyle::State_On)
            rectHandle.moveRight(option->rect.right() - 5);

        return rectHandle;
    }
    return option->rect;
}

int SwitchButtonStyle::indicatorSize(QStyle::PixelMetric pm) const
{
    if (pm == PM_SwitchButtonHandleWidth)
    {
        return 36;
    }
    return 12;
}
void SwitchButtonStyle::drawControl(QStyleOptionButton* option, QPainter* painter, const QWidget* widget)
{
    option->rect = subElementRect(SwitchButtonStyle::SE_SwitchButtonGroove, option, widget);
    drawGroove(option, painter, widget);
    option->rect = subElementRect(SwitchButtonStyle::SE_SwitchButtonHandle, option, widget);
    drawHandle(option, painter, widget);
}

QRect SwitchButtonStyle::subElementRect(SubElement subElement, const QStyleOptionButton* option, const QWidget* widget)
{
    return subElementRect(static_cast<QStyle::SubElement>(subElement), option, widget);
}

int SwitchButtonStyle::indicatorSize(PixelMetric pm) const
{
    return indicatorSize(static_cast<QStyle::PixelMetric>(pm));
}
}  // namespace Theme