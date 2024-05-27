#include <QPainter>
#include <QMenu>

#include "VanillaStyle/Helper/EventFilters.h"
#include "VanillaStyle/Helper/MenuStyle.h"

#include "VanillaStyle/Helper/Common.h"
#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace Vanilla
{
bool MenuStyle::drawPrimitive(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    const auto radius = theme->getSize(SizeRole::NormalRadius);
    const auto bgColor = theme->getColor(option, ColorRole::MenuBackground);  // QColor(245, 245, 245, 210)
    const auto border = theme->getSize(SizeRole::ButtonBorder);
    const auto totalRect = option->rect;
    const auto frameRect = totalRect.marginsRemoved({border, border, border, border});
    painter->setPen(bgColor);
    painter->setBrush(bgColor);
    painter->drawRoundedRect(frameRect, radius, radius);

    return true;
}

void MenuStyle::eventFilter(QMenu* menu) const
{
    menu->setBackgroundRole(QPalette::NoRole);
    menu->setAutoFillBackground(false);
    menu->setAttribute(Qt::WA_TranslucentBackground, true);
    menu->setAttribute(Qt::WA_OpaquePaintEvent, false);
    menu->setAttribute(Qt::WA_NoSystemBackground, true);
    menu->setWindowFlag(Qt::FramelessWindowHint, true);
    menu->setWindowFlag(Qt::NoDropShadowWindowHint, true);
    menu->setProperty("_q_windowsDropShadow", false);
}

bool MenuStyle::drawMenuItem(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionMenuItem*>(option);
    if (!opt)
    {
        return true;
    }
    const auto padding = theme->getSize(SizeRole::MenuItemPadding);

    if (opt->menuItemType == QStyleOptionMenuItem::Separator)
    {
        const auto& sColor = theme->getColor(option, ColorRole::MenuSeparatorColor);
        const auto rect = opt->rect;
        constexpr auto sPadding = 5;
        Helper::renderRoundRect(painter, rect.adjusted(sPadding, 0, -sPadding, 0), sColor, 1);
    }
    else if (opt->menuItemType == QStyleOptionMenuItem::Normal || opt->menuItemType == QStyleOptionMenuItem::SubMenu)
    {
        // Background.
        const auto& bgRect = opt->rect.adjusted(4, 0, 4, 0);

        // Foreground.
        const auto fgRect = bgRect.marginsRemoved(QMargins{padding, 0, padding, 0});
        const auto arrowWidth = theme->getSize(SizeRole::IconSize);
        const auto& fgColor = theme->getColor(opt, ColorRole::PrimaryText);
        constexpr int textFlags = Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | Qt::TextHideMnemonic | Qt::AlignLeft;
        const auto& fm = opt->fontMetrics;

        const auto hasSubMenu = opt->menuItemType == QStyleOptionMenuItem::SubMenu;

        auto availableWidth = fgRect.width() - (hasSubMenu ? arrowWidth + padding : 0);

        const auto menuHasCheckable = opt->menuHasCheckableItems;
        const auto checkable = opt->checkType != QStyleOptionMenuItem::NotCheckable;
        const auto elements = opt->text.split('\t', Qt::KeepEmptyParts);
        const auto& label = !elements.empty() ? elements.first() : QString("");
        const auto& shortcut = elements.size() > 1 ? elements.at(1) : QString("");
        const auto iconSize = theme->getSize(SizeRole::IconSize);
        auto availableX = fgRect.x();

        if (menuHasCheckable || checkable)
        {
            const auto checkBoxX = availableX;

            const auto checkBoxY = fgRect.y() + (fgRect.height() - iconSize) / 2;
            const auto checkboxRect = QRect{
                QPoint{checkBoxX, checkBoxY},
                QSize(iconSize, iconSize)
            };

            auto checkBoxOpt = *option;
            checkBoxOpt.rect = checkboxRect;
            Helper::drawCheckBox(&checkBoxOpt, painter, theme, widget);
            const auto checkBoxWidth = iconSize + padding;
            availableWidth -= checkBoxWidth;
            availableX += checkBoxWidth;
        }

        const auto pixmap = getIconPixmap(opt->icon, QSize(iconSize, iconSize), widget);
        if (!pixmap.isNull())
        {
            const auto colorizedPixmap = getColorizedPixmap(pixmap, widget, fgColor);
            const auto pixmapPixelRatio = colorizedPixmap.devicePixelRatio();
            const auto pixmapWidth = pixmapPixelRatio != 0 ? static_cast<int>(static_cast<qreal>(colorizedPixmap.width()) / pixmapPixelRatio) : 0;
            const auto pixmapHeight = pixmapPixelRatio != 0 ? static_cast<int>(static_cast<qreal>(colorizedPixmap.height()) / pixmapPixelRatio) : 0;

            const auto iconX = availableX;
            const auto iconY = fgRect.y() + (fgRect.height() - pixmapHeight) / 2;
            const auto iconRect = QRect{
                QPoint{iconX, iconY},
                QSize(pixmapWidth, pixmapHeight)
            };
            painter->drawPixmap(iconRect, colorizedPixmap);
            availableX += (pixmapWidth + padding);
        }
        if (!label.isEmpty())
        {
            const auto labelWidth = fm.boundingRect(opt->rect, Qt::AlignLeft, label).width();
            const auto labelRect = QRect{availableX, fgRect.y(), std::min(labelWidth, availableWidth), fgRect.height()};
            painter->setPen(fgColor);
            if (!option->state.testFlag(QStyle::State_Enabled))
            {
                painter->setPen(Qt::gray);
            }
            painter->drawText(labelRect, textFlags, label);
        }

        if (!shortcut.isEmpty())
        {
            const auto shortcutWidth = fm.boundingRect(opt->rect, Qt::AlignRight, shortcut).width();
            const auto shortcutX = fgRect.x() + fgRect.width() - shortcutWidth;
            const auto shortcutRect = QRect{shortcutX, fgRect.y(), shortcutWidth, fgRect.height()};
            constexpr auto shortcutFlags = Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | Qt::AlignRight | Qt::TextHideMnemonic;
            painter->setPen(fgColor);
            painter->drawText(shortcutRect, shortcutFlags, shortcut);
            availableWidth -= shortcutWidth;
        }
    }
    return true;
}

void MenuStyle::drawMenuSeparator(QPainter* painter, const QRect& rect, const QColor& color, const int padding) const
{
    painter->setPen(color);
    painter->setBrush(color);
    painter->drawRoundedRect(rect, 1, 1);
}
}  // namespace Vanilla