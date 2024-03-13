#include "VanillaStyle/Widgets/IconLabel.h"
#include "IconLabel_p.h"

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
    return d->m_label;
}
void IconLabel::setLabel(const QString& label)
{
    Q_D(IconLabel);
    if (d->m_label != label)
    {
        d->m_label = label;
        const QFontMetrics fm(font());
        d->m_labelWidth = fm.horizontalAdvance(label);
        updateGeometry();
        update();
        Q_EMIT labelChanged();
    }
}
const QIcon& IconLabel::icon() const
{
    Q_D(const IconLabel);
    return d->m_icon;
}
void IconLabel::setIcon(const QIcon& icon)
{
    Q_D(IconLabel);
    d->m_icon = icon;
    update();
}
const QSize& IconLabel::iconSize() const
{
    Q_D(const IconLabel);
    return d->m_iconSize;
}
void IconLabel::setIconSize(const QSize& iconSize)
{
    Q_D(IconLabel);

    if (iconSize != d->m_iconSize)
    {
        d->m_iconSize = iconSize;
        emit iconSizeChanged();
        updateGeometry();
        update();
    }
}
const Qt::LayoutDirection& IconLabel::dirction() const
{
    Q_D(const IconLabel);
    return d->m_layoutDirection;
}
void IconLabel::setDirction(const Qt::LayoutDirection& dirction)
{
    Q_D(IconLabel);
    if (d->m_layoutDirection != dirction)
    {
        d->m_layoutDirection = dirction;
        emit dirctionChanged();
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
    m_iconSize = QSize(size, size);
}
QSize IconLabelPrivate::sizeHint() const
{
    return {m_iconSize.width() + padding + m_labelWidth, m_iconSize.height()};
}
void IconLabelPrivate::paint(QPainter* painter)
{
    Q_Q(IconLabel);
    painter->setRenderHint(QPainter::Antialiasing);

    QPoint iconPoint;
    QRect textRect;
    if (q->layoutDirection() == Qt::LeftToRight)
    {
        iconPoint = QPoint(m_labelWidth + padding, 0);
        textRect = QRect(0, 0, m_labelWidth, q->height());
    }
    else
    {
        iconPoint = QPoint(0, 0);
        textRect = QRect(m_iconSize.width() + padding, 0, m_labelWidth, q->height());
    }
    if (const auto pixmap = m_icon.pixmap(m_iconSize.height()); !pixmap.isNull())
    {
        painter->drawPixmap(iconPoint, pixmap);
    }

    if (!m_label.isEmpty())
    {
        const auto font = q->font();
        painter->setFont(font);
        painter->setPen(Qt::black);
        // const auto textRect = QRect(m_iconSize.width() + padding, 0, m_labelWidth, q->height());
        painter->drawText(textRect, Qt::AlignCenter | Qt::TextSingleLine, m_label);
    }
}

}  // namespace VanillaStyle