#include "VanillaStyle/Widgets/IconLabel.h"
#include "IconLabel_p.h"
#include "VanillaStyle/Style/VanillaStyle.h"
#include "VanillaStyle/Theme/Theme.h"

#include <QPainter>
#include <QStyle>
#include <qevent.h>

namespace VanillaStyle
{
IconLabel::IconLabel(QWidget* parent)
    : QWidget(parent)
    , d_ptr(new IconLabelPrivate(this))
{
    Q_D(IconLabel);
    d->init();
}
IconLabel::IconLabel(const QIcon& icon, QWidget* parent)
    : IconLabel(parent)
{
    setIcon(icon);
}
IconLabel::IconLabel(const QString& label, QWidget* parent)
    : IconLabel(parent)
{
    setLabel(label);
}
IconLabel::IconLabel(const QIcon& icon, const QString& label, QWidget* parent)
    : IconLabel(parent)
{
    setIcon(icon);
    setLabel(label);
}
QSize IconLabel::sizeHint() const
{
    Q_D(const IconLabel);
    return d->sizeHint();
}
const QString& IconLabel::label() const
{
    Q_D(const IconLabel);
    return d->label;
}
void IconLabel::setLabel(const QString& label)
{
    Q_D(IconLabel);
    if (d->label != label)
    {
        d->label = label;
        const QFontMetrics fm(font());
        d->labelWidth = fm.horizontalAdvance(label);
        updateGeometry();
        update();
        Q_EMIT labelChanged();
    }
}
const QIcon& IconLabel::icon() const
{
    Q_D(const IconLabel);
    return d->icon;
}
void IconLabel::setIcon(const QIcon& icon)
{
    Q_D(IconLabel);
    d->icon = icon;
    update();
}
const QSize& IconLabel::iconSize() const
{
    Q_D(const IconLabel);
    return d->iconSize;
}
void IconLabel::setIconSize(const QSize& iconSize)
{
    Q_D(IconLabel);

    if (iconSize != d->iconSize)
    {
        d->iconSize = iconSize;
        emit iconSizeChanged();
        updateGeometry();
        update();
    }
}

void IconLabel::paintEvent(QPaintEvent* event)
{
    // Q_UNUSED(event);
    Q_D(IconLabel);
    QPainter painter(this);
    d->paint(&painter);
}

IconLabelPrivate::IconLabelPrivate(IconLabel* q)
    : q_ptr(q)
{
}
void IconLabelPrivate::init()
{
    Q_Q(IconLabel);

    q->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    q->setFocusPolicy(Qt::NoFocus);

    auto size = 16;

    if (const auto* style = q->style())
    {
        size = style->pixelMetric(QStyle::PM_ButtonIconSize);
    }
    iconSize = QSize(size, size);
}
QSize IconLabelPrivate::sizeHint() const
{
    return {iconSize.width() + padding + labelWidth, iconSize.height()};
}
void IconLabelPrivate::paint(QPainter* painter)
{
    Q_Q(IconLabel);
    painter->setRenderHint(QPainter::Antialiasing);
    const auto rect = q->rect();
    const auto isIconFirst = q->isIconFirst();
    const auto iconPoint = QPoint(isIconFirst ? rect.x() : rect.x() + labelWidth + padding, rect.y());
    const auto textRect = QRect(isIconFirst ? iconSize.width() + padding : rect.x(), rect.y(), labelWidth, rect.height());
    if (const auto pixmap = icon.pixmap(iconSize.height()); !pixmap.isNull())
    {
        painter->drawPixmap(iconPoint, pixmap);
    }
    if (!label.isEmpty())
    {
        QColor textColor;
        QFont font;
        if (auto* customStyle = qobject_cast<VanillaStyle*>(q->style()))
        {
            textColor = customStyle->getCustomColor(Theme::ColorRole::IconLabelText);
            font = customStyle->getCustomFont(Theme::TextSizeRole::H5);
        }
        painter->setFont(font);
        painter->setPen(textColor);
        painter->drawText(textRect, Qt::AlignCenter | Qt::TextSingleLine, label);
    }
}

}  // namespace VanillaStyle