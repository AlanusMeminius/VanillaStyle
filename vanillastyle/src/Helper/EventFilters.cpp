#include "VanillaStyle/Helper/EventFilters.h"

#include "VanillaStyle/Helper/Common.h"
#include "VanillaStyle/Style/VanillaStyle.h"

#include <QEvent>
#include <QMenuBar>
#include <QTimer>
#include <QToolButton>

namespace Vanilla
{
MenuEventFilter::MenuEventFilter(QMenu* menu)
    : QObject(menu)
    , _menu(menu)
{
    _menu->installEventFilter(this);
}
bool MenuEventFilter::eventFilter(QObject* watchedObject, QEvent* evt)
{
    Q_UNUSED(watchedObject)
    const auto type = evt->type();
    if (type == QEvent::Show)
    {
        const auto isMenuBarMenu = qobject_cast<QMenuBar*>(_menu->parentWidget()) != nullptr;
        const auto isSubMenu = qobject_cast<QMenu*>(_menu->parentWidget()) != nullptr;
        const auto alignForMenuBar = isMenuBarMenu && !isSubMenu;
        const auto menuItemHPadding = 1;
        const auto menuDropShadowWidth = 1;
        const auto menuOriginalPos = _menu->pos();
        const auto menuBarTranslation = alignForMenuBar ? QPoint(-menuItemHPadding, 0) : QPoint(0, 0);
        const auto shadowTranslation = QPoint(-menuDropShadowWidth, -menuDropShadowWidth);
        const auto menuNewPos = menuOriginalPos + menuBarTranslation + shadowTranslation;

        // Menus have weird sizing bugs when moving them from this event.
        // We have to wait for the event loop to be processed before setting the final position.
        const auto menuSize = _menu->size();
        if (menuSize != QSize(0, 0))
        {
            _menu->resize(0, 0);  // Hide the menu for now until we can set the position.
            QTimer::singleShot(0, _menu, [this, menuNewPos, menuSize]() {
                _menu->move(menuNewPos);
                _menu->resize(menuSize);
            });
        }
    }

    return QObject::eventFilter(watchedObject, evt);
}
LineEditButtonEventFilter::LineEditButtonEventFilter(QToolButton* button, VanillaStyle& style)
    : QObject(button)
    , m_style(style)
    , m_button(button)
{
}

bool LineEditButtonEventFilter::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::Paint)
    {
        if (const auto enable = m_button->isEnabled(); !enable) {
            event->accept();
            return true;
        }
        const auto rect = m_button->rect();
        const auto bgColor = m_style.getColor(m_button, ColorRole::ButtonBackground);
        const auto fgColor = m_style.getColor(m_button, ColorRole::ButtonForeground);
        const auto iconSize = m_style.getSize(m_button, SizeRole::IconSize);
        const auto opacity = m_button->property(QByteArrayLiteral("opacity")).toDouble();
        const auto pixmap = getIconPixmap(m_button->icon(), QSize(iconSize,iconSize), m_button);
        const auto colorizedPixmap = getColorizedPixmap(pixmap, m_button, fgColor);

        const auto iconRect = centerRect(rect, iconSize, iconSize);

        QPainter p(m_button);
        p.setOpacity(opacity);
        p.setPen(Qt::NoPen);
        p.setBrush(bgColor);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.drawPixmap(iconRect, colorizedPixmap);
    }
    return QObject::eventFilter(watched, event);
}

}  // namespace Vanilla