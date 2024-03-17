#include "VanillaStyle/Helper/ItemViewStyle.h"
#include <QPainter>
#include <QtWidgets/QListWidget>

namespace VanillaStyle
{
bool ItemViewStyle::draw(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionViewItem*>(option);
    if (!opt)
    {
        return true;
    }

    drawPrimitive(option, painter, theme, widget);

    const auto rect = opt->rect;
    if (!opt->text.isEmpty())
    {
        const auto& fm = opt->fontMetrics;
        const auto elidedText = fm.elidedText(opt->text, Qt::ElideRight, rect.width(), Qt::TextSingleLine);
        const auto textAlignment = opt->displayAlignment;
        const auto textFlags = Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | (textAlignment.testFlag(Qt::AlignRight) ? Qt::AlignRight : Qt::AlignLeft);
        painter->setFont(opt->font);
        painter->setBrush(Qt::NoBrush);
        const auto textColor = theme->getColor(option, Theme::Text);
        painter->setPen(textColor);
        painter->drawText(rect.adjusted(5, 0, 0, 0), static_cast<int>(textFlags), elidedText, nullptr);
    }
    return true;
}
void ItemViewStyle::drawPrimitive(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const
{
    if (const auto* opt = qstyleoption_cast<const QStyleOptionViewItem*>(option))
    {
        const auto& rect = opt->rect;
        const auto row = opt->index.row();
        QColor bgColor;
        if (row % 2 == 0)
        {
            bgColor = QColor(200, 200, 200);  // 偶数行的背景色为浅灰色
        }
        else
        {
            bgColor = QColor(220, 220, 220);  // 奇数行的背景色为淡灰色
        }
        if (opt->state.testFlag(QStyle::State_Active) && opt->state.testFlag(QStyle::State_Selected))
        {
            bgColor = theme->getColor(option, Theme::ButtonBackground);
        }

        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(bgColor);
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(rect.adjusted(1, 1, -1, -1), 5, 5);
    }
}
}  // namespace VanillaStyle