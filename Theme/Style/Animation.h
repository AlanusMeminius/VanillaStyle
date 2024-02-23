#pragma once
#include <QObject>
#include <QPropertyAnimation>

namespace Theme {

class Animation : public QObject{

    Q_OBJECT
public:
    explicit Animation(QObject* parent = nullptr);

    void setTargetObject(QObject* target) const;
    void setPropertyName(const QString& propertyName);
    void setValue(const QVariant& startValue, const QVariant& endValue) const;
    void setDirection(bool forward) const;
    void setDuration(int duration);
    void start() const;
    [[nodiscard]] int duration() const;

private:
    std::shared_ptr<QPropertyAnimation> mAnimation;
    int mDuration = 500;
    QString mPropertyName = "pos";
};

} // Theme
