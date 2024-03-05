#include "VanillaStyle/Helper/MenuStyle.h"
#include "VanillaStyle/Helper/EventFilters.h"
#include <QPainter>
#include <QMenu>

namespace VanillaStyle
{
void MenuStyle::drawPrimitive(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const
{
    //        const auto radius = d->m_theme->getRadius(Theme::ButtonRadius);
    const auto radius = 5;
    const auto bgColor = QColor(245, 245, 245);
    const auto border = theme->getBorder(Theme::ButtonBorder);
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
void MenuStyle::drawMenuBarItem(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const
{
    if (const auto* optMenuItem = qstyleoption_cast<const QStyleOptionMenuItem*>(option))
    {
        // MenuBar background.
        const auto& barBgColor = QColor(55, 55, 55);
        painter->fillRect(optMenuItem->rect, barBgColor);
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
        painter->drawText(optMenuItem->rect, textFlags, optMenuItem->text);
    }
}
void MenuStyle::drawMenuItem(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const
{
    if (const auto* opt = qstyleoption_cast<const QStyleOptionMenuItem*>(option))
    {
        if (opt->menuItemType == QStyleOptionMenuItem::Separator)
        {
            const auto& color = QColor(100, 100, 100);
            const auto rect = opt->rect;
            const auto thickness = theme->getBorder(Theme::ButtonBorder);
            drawMenuSeparator(painter, rect, color, thickness);
        }
        else if (opt->menuItemType == QStyleOptionMenuItem::Normal || opt->menuItemType == QStyleOptionMenuItem::SubMenu)
        {
            // Background.
            const auto& bgRect = opt->rect.adjusted(4,0,4,0);
//            const auto& bgColor = QColor(200, 200, 200);
//            const auto menuItemRadius = theme->getRadius(Theme::MenuItemRadius);
//            painter->setRenderHint(QPainter::Antialiasing);
//            painter->setPen(Qt::NoPen);
//            painter->setBrush(bgColor);
//            painter->drawRoundedRect(opt->rect, menuItemRadius, menuItemRadius);

            // Foreground.
            const auto& fgColor = QColor(12, 12, 12);
            const auto spacing = theme->getBorder(Theme::NormalBorder);

            const auto menuHasCheckable = opt->menuHasCheckableItems;
            const auto checkable = opt->checkType != QStyleOptionMenuItem::NotCheckable;
//            const auto checkState = opt->checked ? CheckState::Checked : CheckState::NotChecked;

//            const auto useMnemonic = styleHint(SH_UnderlineShortcut, opt, w);

            const auto* parent = widget ? widget->parentWidget() : nullptr;
            const auto hasFocus = (widget && widget->hasFocus()) || (parent && parent->hasFocus());
            const auto hasSubMenu = opt->menuItemType == QStyleOptionMenuItem::SubMenu;
            const auto showMnemonic = hasFocus;
            int textFlags =
                Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | Qt::TextShowMnemonic | Qt::AlignLeft;

            const auto& fm = opt->fontMetrics;

            painter->setPen(fgColor);
            painter->drawText(bgRect, textFlags, opt->text, nullptr);

        }
    }
}
void MenuStyle::drawMenuSeparator(QPainter* painter, const QRect& rect, const QColor& color, const int thickness) const
{
    const auto x = rect.x();
    const auto w = rect.width();
    const auto h = std::max(1, thickness);
    const auto y = rect.y() + (rect.height() - h) / 2;
    painter->fillRect(QRect{x, y, w, h}, color);
}
}  // namespace VanillaStyle