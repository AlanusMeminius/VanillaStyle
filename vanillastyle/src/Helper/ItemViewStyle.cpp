#include <QPainter>
#include <QListWidget>

#include "VanillaStyle/Helper/ItemViewStyle.h"

#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace Vanilla
{
bool ItemViewStyle::draw(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionViewItem*>(option);
    if (!opt)
    {
        return true;
    }

    if (const bool isDrawItemBackground = widget->property("noBackground").toBool(); !isDrawItemBackground)
    {
        drawPrimitive(option, painter, theme, widget);
    }

    const auto rect = opt->rect;
    if (!opt->text.isEmpty())
    {
        const auto& fm = opt->fontMetrics;
        const auto elidedText = fm.elidedText(opt->text, Qt::ElideRight, rect.width(), Qt::TextSingleLine);
        const auto textAlignment = opt->displayAlignment;
        const auto textFlags =
            Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | (textAlignment.testFlag(Qt::AlignRight) ? Qt::AlignRight : Qt::AlignLeft);
        painter->setFont(opt->font);
        painter->setBrush(Qt::NoBrush);
        const auto textColor = theme->getColor(option, Theme::PrimaryText);
        painter->setPen(textColor);
        painter->drawText(rect.adjusted(5, 0, 0, 0), static_cast<int>(textFlags), elidedText, nullptr);
    }
    return true;
}

void ItemViewStyle::drawPrimitive(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    if (const auto* opt = qstyleoption_cast<const QStyleOptionViewItem*>(option))
    {
        const auto& rect = QRectF(opt->rect);
        const auto row = opt->index.row();
        QColor bgColor;
        if (row % 2 == 0)
        {
            bgColor = theme->getColor(opt, Theme::ItemViewEvenRowColor);
        }
        else
        {
            bgColor = theme->getColor(opt, Theme::ItemViewOddRowColor);
        }
        if (opt->state.testFlag(QStyle::State_Active) && opt->state.testFlag(QStyle::State_Selected))
        {
            bgColor = theme->getColor(option, Theme::ItemViewSelectedColor);
        }

        painter->setRenderHint(QPainter::Antialiasing);
        const auto radius = theme->getSize(Theme::ItemViewRadius);
        Helper::renderRoundRect(painter, rect.adjusted(1, 3, -1, -3), bgColor, radius);
    }
}
}  // namespace VanillaStyle