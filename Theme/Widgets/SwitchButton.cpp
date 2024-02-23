#include "SwitchButton_p.h"
#include "Config/Color.h"
#include <QStylePainter>
#include <QPainterPath>
#include <QMouseEvent>

SwitchButton::SwitchButton(QWidget* parent)
    : QWidget(parent)
    , d_ptr(new SwitchButtonPrivate(this))
{
    Q_D(SwitchButton);
    d->init();
}
QSize SwitchButton::sizeHint() const
{
    Q_D(const SwitchButton);
    return d->sizeHint();
}
int SwitchButton::handlePosition() const
{
    Q_D(const SwitchButton);
    return d->m_handlePosition;
}
void SwitchButton::setHandlePosition(int pos)
{
    Q_D(SwitchButton);
    d->m_handlePosition = pos;
    update();
}
void SwitchButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    Q_D(SwitchButton);
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    if (!isEnabled())
    {
        painter.setPen(Theme::Color::buttonOutlineColor());
        painter.setOpacity(0.5);
    }
    else if (d->m_mouseDown)
    {
        painter.setPen(Theme::Color::pressedOutlineColor());
    }
    else if (underMouse() || hasFocus())
    {
        painter.setPen(QPen(Theme::Color::hoverOutlineBrush(rect()), 1));
    }
    else
    {
        painter.setPen(Theme::Color::buttonOutlineColor());
    }

    if (d->m_checked)
    {
        painter.setBrush(Theme::Color::swichButtonCheckedBackground());
    }
    const auto radius = height() / 2;
    painter.drawRoundedRect(QRectF(rect()).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);

    QPainterPath handle;
    handle.addEllipse(d->margin + d->m_handlePosition, d->margin, d->handleSize, d->handleSize);
    painter.fillPath(handle, QBrush(Theme::Color::swichButtonHandleColor()));

    painter.restore();
}
void SwitchButton::mousePressEvent(QMouseEvent* event)
{
    Q_D(SwitchButton);
    if (event->button() == Qt::LeftButton)
    {
        d->m_mouseDown = true;
    }
    else
    {
        event->ignore();
    }
}
void SwitchButton::mouseReleaseEvent(QMouseEvent* event)
{
    Q_D(SwitchButton);
    if (event->button() == Qt::LeftButton && d->m_mouseDown)
    {
        d->m_mouseDown = false;
        d->toggle();
        emit checked(d->m_checked);
    }
    else
    {
        event->ignore();
    }
}
void SwitchButton::keyPressEvent(QKeyEvent* event)
{
    Q_D(SwitchButton);
    if (event->key() == Qt::Key_Space)
    {
        d->toggle();
        emit checked(d->m_checked);
    }
    else
    {
        event->ignore();
    }
}

SwitchButtonPrivate::SwitchButtonPrivate(SwitchButton* q)
    : q_ptr(q)
    , mAnimation(std::make_shared<Theme::Animation>())
{
}
void SwitchButtonPrivate::init()
{
    Q_Q(SwitchButton);

    m_checked = false;
    q->setObjectName(QStringLiteral("SwitchButton"));
    q->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    q->setFocusPolicy(Qt::TabFocus);
    q->setAttribute(Qt::WA_Hover);
    mAnimation->setTargetObject(q);
    mAnimation->setPropertyName(QStringLiteral("handlePosition"));
    mAnimation->setValue(QVariant(0), QVariant(handleSize));
    mAnimation->setDuration(300);
}
void SwitchButtonPrivate::setChecked(const bool checked)
{
    Q_Q(SwitchButton);

    if (m_checked == checked)
    {
        return;
    }
    m_checked = checked;
    mAnimation->setDirection(m_checked);
    mAnimation->start();
    emit q->toggled(checked);
}
bool SwitchButtonPrivate::isChecked() const
{
    return m_checked;
}
void SwitchButtonPrivate::toggle()
{
    setChecked(!m_checked);
}

QSize SwitchButtonPrivate::sizeHint() const
{
    return {width, height};
}