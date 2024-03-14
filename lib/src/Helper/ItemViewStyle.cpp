#include "VanillaStyle/Helper/ItemViewStyle.h"
#include <QPainter>

namespace VanillaStyle
{
void ItemViewStyle::draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme) const
{
    if (const auto* opt = qstyleoption_cast<const QStyleOptionViewItem*>(option))
    {
        drawPrimitive(option, painter, theme, widget);

        const auto rect = opt->rect;
        if (!opt->text.isEmpty())
        {
            const auto& fm = opt->fontMetrics;
            const auto elidedText = fm.elidedText(opt->text, Qt::ElideRight, rect.width(), Qt::TextSingleLine);
            // const auto textX = availableX;
            // const auto textRect = QRect{ textX, contentRect.y(), availableW, contentRect.height() };
            const auto textAlignment = opt->displayAlignment;
            auto textFlags =
                Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | (textAlignment.testFlag(Qt::AlignRight) ? Qt::AlignRight : Qt::AlignLeft);
            painter->setFont(opt->font);
            painter->setBrush(Qt::NoBrush);
            const auto textColor = theme->getColor(option, Theme::Text);
            painter->setPen(textColor);
            painter->drawText(rect, int(textFlags), elidedText, nullptr);
        }
    }
}
void ItemViewStyle::drawPrimitive(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const
{
    if (const auto* opt = qstyleoption_cast<const QStyleOptionViewItem*>(option))
    {
        const auto& rect = opt->rect;
        const auto row = opt->index.row();
        const auto column = opt->index.column();
        const auto widgetHasFocus = (widget && widget->hasFocus());
        const auto focus = widgetHasFocus && VanillaStyle::Theme::state(option) == Theme::Selected;
        const auto bgColor = theme->getColor(option, Theme::ButtonBackground);

        // painter->setBrush(bgColor);
        // painter->drawRoundedRect(rect, 5,5);
        painter->fillRect(rect, bgColor);
    }
}
}  // namespace VanillaStyle