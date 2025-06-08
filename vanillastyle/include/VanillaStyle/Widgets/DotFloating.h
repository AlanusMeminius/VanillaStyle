#pragma once
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QWidget>
namespace Vanilla
{
class CircleItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float x READ x WRITE setX NOTIFY valueChanged)
    Q_PROPERTY(float opacity READ opacity WRITE setOpacity NOTIFY valueChanged)

public:
    explicit CircleItem(QObject* parent = nullptr);

    float x() const;
    void setX(float x);

    float opacity() const;
    void setOpacity(float opacity);

signals:
    void valueChanged();

private:
    float m_x;        // x坐标
    float m_opacity;  // 透明度0~1
};
class DotFloating : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int radius READ radius WRITE setRadius)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit DotFloating(QWidget* parent = nullptr, int radius = 5, const QColor& color = QColor(24, 189, 155),
                         const QColor& backgroundColor = Qt::transparent);
    ~DotFloating() override = default;

    int radius() const;
    void setRadius(int radius);

    QColor color() const;
    void setColor(const QColor& color);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor& backgroundColor);

    QSize sizeHint() const override;

    void stopAnimation();
    void startAnimation();
    void resetAnimation();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void initAnimations();

    template <typename T>
    static T qBound(T min, T val, T max)
    {
        return qMax(min, qMin(val, max));
    }

private:
    int m_radius;
    QColor m_color;
    QColor m_backgroundColor;

    QVector<QPair<CircleItem*, QSequentialAnimationGroup*>> m_items;
};
}  // namespace Vanilla
