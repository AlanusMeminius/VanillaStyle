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

    drawPrimitive(option, painter, theme, widget);

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
        const auto textColor = theme->getColor(option, ColorRole::PrimaryText);
        painter->setPen(textColor);
        painter->drawText(rect.adjusted(5, 0, 0, 0), static_cast<int>(textFlags), elidedText, nullptr);
    }
    return true;
}

void ItemViewStyle::drawPrimitive(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionViewItem*>(option);
    if (!opt)
    {
        return;
    }

    const auto& rect = QRectF(opt->rect);
    const auto row = opt->index.row();
    QColor bgColor;
    if (row % 2 == 0)
    {
        bgColor = theme->getColor(opt, ColorRole::ItemViewEvenRowColor);
    }
    else
    {
        bgColor = theme->getColor(opt, ColorRole::ItemViewOddRowColor);
    }
    if (opt->state.testFlag(QStyle::State_Active) && opt->state.testFlag(QStyle::State_Selected))
    {
        bgColor = theme->getColor(option, ColorRole::ItemViewSelectedColor);
    }

    painter->setRenderHint(QPainter::Antialiasing);
    const auto radius = theme->getSize(SizeRole::ItemViewRadius);
    Helper::renderRoundRect(painter, rect.adjusted(1, 3, -1, -3), bgColor, radius);
}

QSize ItemViewStyle::sizeFromContentsForItemView(QStyle::ContentsType type, const QStyleOption* option, const QSize& contentsSize,
                                                 const std::shared_ptr<Theme>& theme, const QWidget* widget)
{
    if (type == QStyle::CT_ItemViewItem)
    {
        if (const auto* opt = qstyleoption_cast<const QStyleOptionViewItem*>(option))
        {
            const auto& features = opt->features;
            const auto padding = theme->getSize(SizeRole::MenuItemPadding);

            const auto hasIcon = features.testFlag(QStyleOptionViewItem::HasDecoration) && !opt->icon.isNull();
            const auto& iconSize = hasIcon ? opt->decorationSize : QSize{0, 0};

            const auto hasText = features.testFlag(QStyleOptionViewItem::HasDisplay) && !opt->text.isEmpty();
            const auto textH = hasText ? opt->fontMetrics.height() : 0;

            const auto hasCheck = features.testFlag(QStyleOptionViewItem::HasCheckIndicator);
            const auto& checkSize = hasCheck ? iconSize : QSize{0, 0};

            auto font = QFont(widget->font());
            const auto fm = QFontMetrics(font);
            const auto textWidth = fm.boundingRect(opt->rect, Qt::AlignLeft, opt->text).width();
            const auto itemWidth =
                textWidth + 2 * padding + (iconSize.width() > 0 ? iconSize.width() + padding : 0) + (checkSize.width() > 0 ? checkSize.width() + padding : 0);
            return {itemWidth, textH + 16};
        }
        return {};
    }
    return {};
}
}  // namespace Vanilla