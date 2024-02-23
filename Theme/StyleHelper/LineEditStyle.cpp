#include "LineEditStyle.h"
#include "Config/Color.h"
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>

namespace Theme
{
LineEditStyle::LineEditStyle() = default;
void LineEditStyle::drawPanel(const QStyleOptionFrame* option, QPainter* painter, const QWidget* widget) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);

    // QPainterPath contentPath;
    // QRectF contentPathRoundedRect = QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5);
    // contentPath.addRoundedRect(contentPathRoundedRect, 5, 5);
    // painter->fillPath(contentPath, Qt::transparent);

    if (option->lineWidth > 0)
    {
        if (!(option->state & QStyle::State_Enabled))
        {
            painter->setPen(QColor(246, 245, 245));
            painter->setOpacity(0.5);
        }
        else if (option->state & QStyle::State_HasFocus)
        {
            painter->setPen(QColor(183, 132, 183));
        }
        else
        {
            painter->setPen(QColor(181, 192, 208));
        }
        painter->drawRoundedRect(QRectF(option->rect).adjusted(1, 1, -1, -1), 5, 5);
    }
    painter->restore();
}
// QSize LineEditStyle::sizeFromContents(const QStyleOptionFrame* option, const QSize& contentsSize, const QWidget* widget) const
// {
//     Q_UNUSED(option)
//     Q_UNUSED(widget)
//     return QSize(contentsSize.width() + 2 * option->lineWidth - 100, contentsSize.height() + 2 * option->lineWidth);
// }
QRect LineEditStyle::subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const
{
    Q_UNUSED(widget)
    if (subElement == QStyle::SE_LineEditContents)
    {
        return option->rect.adjusted( 5, 0, 0, 0);
    }
    return option->rect;
}
}  // namespace Theme