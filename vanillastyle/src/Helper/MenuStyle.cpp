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
    const auto bgColor = theme->getColor(option, ColorRole::MenuBackground); //QColor(245, 245, 245, 210)
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

        const auto elements = opt->text.split('\t', Qt::KeepEmptyParts);
        const auto& label = !elements.empty() ? elements.first() : QString("");
        const auto& shortcut = elements.size() > 1 ? elements.at(1) : QString("");

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
        if (!label.isEmpty())
        {
            const auto labelWidth = fm.boundingRect(opt->rect, Qt::AlignLeft, label).width();
            const auto labelRect = QRect{fgRect.x(), fgRect.y(), std::min(labelWidth, availableWidth), fgRect.height()};
            painter->setPen(fgColor);
            painter->drawText(labelRect, textFlags, label);
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