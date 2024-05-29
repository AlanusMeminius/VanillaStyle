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
        const auto [label, shortcut] = splitMenuShortcut(opt->text);
        const auto iconSize = theme->getSize(SizeRole::IconSize);
        auto availableX = fgRect.x();

        if (checkable)
        {
            const auto checkBoxX = availableX;

            const auto checkBoxY = fgRect.y() + (fgRect.height() - iconSize) / 2;
            const auto checkboxRect = QRect{
                QPoint{checkBoxX, checkBoxY},
                QSize(iconSize, iconSize)
            };

            auto copy = *opt;
            copy.rect = checkboxRect.adjusted(1,1,-1,-1);
            Helper::drawCheckBoxHelper(&copy, painter, theme, widget);

            if (copy.checked)
            {
                Helper::drawCheckBoxIndicator(&copy, checkboxRect, painter, theme);
            }
        }
        if (menuHasCheckable || checkable)
        {
            const auto checkBoxWidth = iconSize + padding;
            availableWidth -= checkBoxWidth;
            availableX += checkBoxWidth;
            availableX += 2 * padding;
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
            availableX += pixmapWidth;
            availableX += 2 * padding;
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
            auto endX = fgRect.x() + fgRect.width();
            const auto radius = theme->getSize(SizeRole::NormalRadius);
            const auto shortCutBgColor = theme->getColor(opt, ColorRole::MenuShortCutsBackground);
            constexpr auto shortcutFlags = Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | Qt::AlignRight | Qt::TextHideMnemonic;
            const auto keyList = shortcut.split(' ');
            for (int i = static_cast<int>(keyList.size()) - 1; i >= 0; --i)
            {
                constexpr int keyPadding = 2;
                const auto wordWidth = fm.boundingRect(opt->rect, Qt::AlignRight, keyList.at(i)).width();
                const auto keyWitdh = wordWidth + 4 * keyPadding;
                const auto keyRect = QRect{endX - keyWitdh, fgRect.y(), keyWitdh, fgRect.height()};
                const auto keyBgRect = insideMargin(keyRect, keyPadding, 2 * keyPadding);
                Helper::renderRoundRect(painter, keyBgRect, shortCutBgColor, radius);
                painter->setPen(Qt::gray);
                const auto keyTextRect = insideMargin(keyBgRect, keyPadding);
                painter->drawText(keyTextRect, shortcutFlags, keyList.at(i));
                endX -= keyWitdh;
            }
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