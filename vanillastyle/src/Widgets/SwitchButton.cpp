#include "VanillaStyle/Widgets/SwitchButton.h"
#include "SwitchButton_p.h"
#include "VanillaStyle/Style/VanillaStyle.h"
#include "VanillaStyle/Theme/Theme.h"

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

namespace Vanilla
{

SwitchButton::SwitchButton(QWidget* parent)
    : QWidget(parent)
    , d_ptr(new SwitchButtonPrivate(this))
{
    Q_D(SwitchButton);
    d->init();
}

SwitchButton::~SwitchButton()
{
    delete d_ptr;
}

QSize SwitchButton::sizeHint() const
{
    Q_D(const SwitchButton);
    return d->sizeHint();
}

void SwitchButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    Q_D(SwitchButton);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QColor handleColor;
    QColor backgroundColor;
    if (auto * customStyle = qobject_cast<VanillaStyle*>(style()))
    {
        handleColor = customStyle->getCustomColor(ColorRole::ButtonForeground);
        backgroundColor = customStyle->getCustomColor(ColorRole::ButtonBackground);
    }
    painter.setPen(Qt::NoPen);
    painter.setBrush(handleColor);
    const auto radius = height() / 2;
    painter.drawRoundedRect(QRectF(rect()).adjusted(1, 1, -1, -1), radius, radius);

    const auto handlePosition = d->handleAnimation.currentValue().toDouble();
    QPainterPath handle;
    handle.addEllipse(d->margin + d->handleSize * handlePosition, d->margin, d->handleSize, d->handleSize);
    painter.fillPath(handle, QBrush(backgroundColor));
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
    setupAnimation();
}

void SwitchButtonPrivate::setChecked(const bool checked)
{
    Q_Q(SwitchButton);

    if (m_checked == checked)
    {
        return;
    }
    m_checked = checked;
    startAnimation();
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

void SwitchButtonPrivate::setupAnimation()
{
    Q_Q(SwitchButton);
    constexpr auto animationDuration = 0;
    handleAnimation.setDuration(animationDuration);
    handleAnimation.setEasingCurve(QEasingCurve::Type::OutCubic);
    handleAnimation.setStartValue(0.);
    handleAnimation.setEndValue(0.);
    QObject::connect(&handleAnimation, &QVariantAnimation::valueChanged, q, [this, q](const QVariant& value) {
        q->update();
    });
}

void SwitchButtonPrivate::startAnimation()
{
    const auto currentPosition = handleAnimation.currentValue();
    handleAnimation.stop();
    handleAnimation.setDuration(500);
    handleAnimation.setStartValue(currentPosition);
    handleAnimation.setEndValue(isChecked() ? 1. : 0.);
    handleAnimation.start();
}
}  // namespace VanillaStyle