#include <QPainter>
#include <QtWidgets/QListWidget>
#include "VanillaStyle/Helper/Helper.h"
namespace VanillaStyle {

bool Helper::drawListWidgetBackground(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const
{
    qDebug() << "drawWidget" << widget->objectName();

    if (const auto opt = qobject_cast<const QListWidget*>(widget))
    {
        qDebug() << "drawListWidgetBackground" << widget->objectName();
        painter->fillRect(option->rect, Qt::red);
        return true;
    }
    return true;
}
} // VanillaStyle