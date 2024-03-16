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
        // const auto textX = availableX;
        // const auto textRect = QRect{ textX, contentRect.y(), availableW, contentRect.height() };
        const auto textAlignment = opt->displayAlignment;
        auto textFlags = Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | (textAlignment.testFlag(Qt::AlignRight) ? Qt::AlignRight : Qt::AlignLeft);
        painter->setFont(opt->font);
        painter->setBrush(Qt::NoBrush);
        const auto textColor = theme->getColor(option, Theme::Text);
        painter->setPen(textColor);
        painter->drawText(rect.adjusted(2,0,0,0), int(textFlags), elidedText, nullptr);
    }
    return true;
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

        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(bgColor);
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(rect.adjusted(1,1,-1,-1), 5,5);
        // painter->fillRect(rect, bgColor);
    }
}

}  // namespace VanillaStyle