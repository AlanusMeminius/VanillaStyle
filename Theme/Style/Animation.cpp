#include "Animation.h"

namespace Theme
{
Animation::Animation(QObject* parent)
    : QObject(parent)
{
    mAnimation = std::make_shared<QPropertyAnimation>(this);
    mAnimation->setDuration(mDuration);
    mAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    mAnimation->setPropertyName(mPropertyName.toUtf8().constData());
}
void Animation::setTargetObject(QObject* target) const
{
    mAnimation->setTargetObject(target);
}
void Animation::setPropertyName(const QString& propertyName)
{
    mPropertyName = propertyName;
    mAnimation->setPropertyName(mPropertyName.toUtf8().constData());
}
void Animation::setValue(const QVariant& startValue, const QVariant& endValue) const
{
    mAnimation->setStartValue(startValue);
    mAnimation->setEndValue(endValue);
}
void Animation::setDirection(const bool forward) const
{
    if (forward)
    {
        mAnimation->setDirection(QPropertyAnimation::Forward);
    }
    else
    {
        mAnimation->setDirection(QPropertyAnimation::Backward);
    }
}
void Animation::setDuration(const int duration)
{
    mDuration = duration;
    mAnimation->setDuration(mDuration);
}
void Animation::start() const
{
    mAnimation->start();
}
int Animation::duration() const
{
    return mDuration;
}

}  // namespace Theme