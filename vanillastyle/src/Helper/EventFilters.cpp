#include "VanillaStyle/Helper/EventFilters.h"
#include <QEvent>
#include <QMenuBar>
#include <QTimer>

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

}  // namespace Vanilla