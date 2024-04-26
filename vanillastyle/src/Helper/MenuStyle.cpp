#include <QPainter>
#include <QMenu>

#include "VanillaStyle/Helper/EventFilters.h"
#include "VanillaStyle/Helper/MenuStyle.h"

#include "VanillaStyle/Helper/Common.h"
#include "VanillaStyle/Theme/Theme.h"


namespace Vanilla
{
bool MenuStyle::drawPrimitive(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    //        const auto radius = d->m_theme->getRadius(Theme::ButtonRadius);
    const auto radius = 5;
    const auto bgColor = QColor(245, 245, 245);
    const auto border = theme->getSize(Theme::ButtonBorder);
    painter->setRenderHint(QPainter::Antialiasing);
    const auto totalRect = option->rect;
    const auto shadowPadding = 2;
    const auto frameRect = totalRect.marginsRemoved({shadowPadding, shadowPadding, shadowPadding, shadowPadding});
    const auto dropShadowRadius = shadowPadding / 3.;
    const auto dropShadowOffsetY = shadowPadding / 4;
    const auto dropShadowPixmap = shadowPixmap(frameRect.size(), radius, dropShadowRadius, QColor(245, 245, 245, 100));
    const auto dropShadowX = frameRect.x() + (frameRect.width() - dropShadowPixmap.width()) / 2;
    const auto dropShadowY = frameRect.y() + (frameRect.height() - dropShadowPixmap.height()) / 2 + dropShadowOffsetY;

    const auto compMode = painter->compositionMode();
    painter->setCompositionMode(QPainter::CompositionMode_Multiply);
    painter->drawPixmap(dropShadowX, dropShadowY, dropShadowPixmap);
    painter->setCompositionMode(compMode);
    const auto halfBorderW = 2 / 2.;

    const auto bgFrameRect = QRectF(frameRect).marginsRemoved(QMarginsF(halfBorderW, halfBorderW, halfBorderW, halfBorderW));

    painter->setPen(bgColor);
    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgFrameRect, radius, radius);

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

    // Place the QMenu correctly by making up for the drop shadow margins.
    menu->installEventFilter(new MenuEventFilter(menu));
}
bool MenuStyle::drawMenuBarItem(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionMenuItem*>(option);
    if (!opt)
    {
        return true;
    }
    // MenuBar background.
    const auto& barBgColor = QColor(55, 55, 55);
    painter->fillRect(opt->rect, barBgColor);
    const auto& bgColor = QColor(255, 255, 255);
    const auto& fgColor = QColor(12, 12, 12);
    int textFlags = Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | Qt::AlignHCenter;
    const auto radius = theme->getRadius(Theme::ButtonRadius);
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawRoundedRect(option->rect, radius, radius);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(fgColor);
    painter->drawText(opt->rect, textFlags, opt->text);
    return true;
}
bool MenuStyle::drawMenuItem(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionMenuItem*>(option);
    if (!opt)
    {
        return true;
    }
    const auto padding = theme->getSize(Theme::MenuItemPadding);

    if (opt->menuItemType == QStyleOptionMenuItem::Separator)
    {
        const auto& color = QColor(100, 100, 100);
        const auto rect = opt->rect;
        drawMenuSeparator(painter, rect, color, padding);
    }
    else if (opt->menuItemType == QStyleOptionMenuItem::Normal || opt->menuItemType == QStyleOptionMenuItem::SubMenu)
    {
        // Background.
        const auto& bgRect = opt->rect.adjusted(4, 0, 4, 0);

        // Foreground.
        const auto fgRect = bgRect.marginsRemoved(QMargins{ padding, 0, padding, 0 });
        const auto arrowWidth = theme->getSize(Theme::IconSize);
        const auto& fgColor = theme->getColor(opt, Theme::ColorRole::PrimaryText);
        constexpr int textFlags = Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | Qt::TextShowMnemonic | Qt::AlignLeft;
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
            const auto shortcutRect = QRect{ shortcutX, fgRect.y(), shortcutWidth, fgRect.height() };
            constexpr auto shortcutFlags =
              Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | Qt::AlignRight | Qt::TextHideMnemonic;
            painter->setPen(fgColor);
            painter->drawText(shortcutRect, shortcutFlags, shortcut);
            availableWidth -= shortcutWidth;
        }
        if (!label.isEmpty())
        {
            const auto labelWidth = fm.boundingRect(opt->rect, Qt::AlignLeft, label).width();
            const auto labelRect = QRect{ fgRect.x(), fgRect.y(), std::min(labelWidth, availableWidth), fgRect.height() };
            painter->setPen(fgColor);
            painter->drawText(labelRect, textFlags, label);
        }
    }
    return true;
}
void MenuStyle::drawMenuSeparator(QPainter* painter, const QRect& rect, const QColor& color, const int thickness) const
{
    const auto x = rect.x() + thickness;
    const auto w = rect.width() - 2 * thickness;
    const auto h = std::max(1, 2);
    const auto y = rect.y() + (rect.height() - h) / 2;
    const auto separatorRect = QRect{ x, y, w, h };
    painter->setBrush(color);
    painter->drawRoundedRect(separatorRect, 2, 2);
}
}  // namespace VanillaStyle