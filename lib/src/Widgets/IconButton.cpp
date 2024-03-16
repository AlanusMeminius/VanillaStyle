#include "VanillaStyle/Widgets/IconButton.h"
#include "IconButton_p.h"
#include <QPainter>

namespace VanillaStyle
{
IconButton::IconButton(QWidget* parent)
    : QAbstractButton(parent)
    , d_ptr(new IconButtonPrivate(this))
{
    Q_D(IconButton);
    d->init();
}
IconButton::IconButton(const QIcon& icon, QWidget* parent)
    : IconButton(parent)
{
    setIcon(icon);
}

QSize IconButton::sizeHint() const
{
    Q_D(const IconButton);
    return d->sizeHint();
}
void IconButton::paintEvent(QPaintEvent* event)
{
    Q_D(IconButton);
    Q_UNUSED(event);
    QPainter painter(this);
    d->paint(&painter);
}
IconButtonPrivate::IconButtonPrivate(IconButton* q)
    : q_ptr(q)
{
}
void IconButtonPrivate::init()
{
    Q_Q(IconButton);
    q->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}
QSize IconButtonPrivate::sizeHint() const
{
    Q_Q(const IconButton);
    return q->iconSize() + QSize(padding * 2, padding * 2);
}
void IconButtonPrivate::paint(QPainter* painter)
{
    Q_Q(IconButton);
    const auto opacity = q->isEnabled() ? 1.0 : 0.2;
    painter->setOpacity(opacity);
    const auto rectCenter = q->rect().center();
    // constexpr auto padding = 2;
    const auto halfWidth = q->iconSize().width() / 2;
    const auto iconPoint = rectCenter - QPoint(halfWidth, halfWidth);
    if (const auto pixmap = q->icon().pixmap(q->iconSize()); !pixmap.isNull())
    {
        painter->drawPixmap(iconPoint, pixmap);
    }
}

}  // namespace VanillaStyle