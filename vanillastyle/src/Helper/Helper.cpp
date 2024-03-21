#include <QPainter>
#include <QtWidgets/QListWidget>
#include "VanillaStyle/Helper/Helper.h"

#include <QPainterPath>
namespace VanillaStyle {

bool Helper::shapedFrame(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const
{
    if (const bool isComboPopList = widget->inherits("QComboBoxPrivateContainer"); !isComboPopList)
    {
        return true;
    }
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QBrush(Qt::white));
    painter->setPen(Qt::NoPen);
    const auto radius = theme->getRadius(Theme::NormalRadius);
    painter->drawRoundedRect(option->rect, radius, radius);

    return true;
}
} // VanillaStyle