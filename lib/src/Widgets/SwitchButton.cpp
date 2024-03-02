#include "VanillaStyle/Widgets/SwitchButton.h"
#include "SwitchButton_p.h"

namespace VanillaStyle {

SwitchButton::SwitchButton(QWidget* parent)
{
}
QSize SwitchButton::sizeHint() const
{
    return QWidget::sizeHint();
}
int SwitchButton::handlePosition() const
{
}
void SwitchButton::setHandlePosition(int pos)
{
}
void SwitchButton::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
}
void SwitchButton::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);
}
void SwitchButton::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
}
void SwitchButton::keyPressEvent(QKeyEvent* event)
{
    QWidget::keyPressEvent(event);
}

SwitchButtonPrivate::SwitchButtonPrivate(SwitchButton* q): q_ptr(q)
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
}
void SwitchButtonPrivate::setChecked(const bool checked)
{
    Q_Q(SwitchButton);

    if (m_checked == checked)
    {
        return;
    }
    m_checked = checked;
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
} // VanillaStyle