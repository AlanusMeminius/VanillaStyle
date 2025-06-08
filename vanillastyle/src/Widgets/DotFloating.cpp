#include "VanillaStyle/Widgets/DotFloating.h"

#include <QPainter>
#include <QPaintEvent>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPauseAnimation>
#include <QPointer>
#include <QPropertyAnimation>
#include <ranges>

namespace Vanilla
{

CircleItem::CircleItem(QObject* parent)
    : QObject(parent)
    , m_x(0.0f)
    , m_opacity(1.0f)
{
}
float CircleItem::x() const
{
    return m_x;
}
void CircleItem::setX(float x)
{
    if (m_x != x)
    {
        m_x = x;
        emit valueChanged();
    }
}
float CircleItem::opacity() const
{
    return m_opacity;
}
void CircleItem::setOpacity(float opacity)
{
    if (m_opacity != opacity)
    {
        m_opacity = opacity;
        emit valueChanged();
    }
}

DotFloating::DotFloating(QWidget* parent, int radius, const QColor& color, const QColor& backgroundColor)
    : QWidget(parent)
    , m_radius(radius)
    , m_color(color)
    , m_backgroundColor(backgroundColor)
{
    initAnimations();
}

int DotFloating::radius() const
{
    return m_radius;
}
void DotFloating::setRadius(int radius)
{
    if (m_radius != radius)
    {
        m_radius = radius;
        update();
    }
}
QColor DotFloating::color() const
{
    return m_color;
}

void DotFloating::setColor(const QColor& color)
{
    if (m_color != color)
    {
        m_color = color;
        update();
    }
}
QColor DotFloating::backgroundColor() const
{
    return m_backgroundColor;
}

void DotFloating::setBackgroundColor(const QColor& backgroundColor)
{
    if (m_backgroundColor != backgroundColor)
    {
        m_backgroundColor = backgroundColor;
        update();
    }
}

void DotFloating::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), m_backgroundColor);
    painter.setPen(Qt::NoPen);

    for (const auto& item : m_items | std::views::keys)
    {
        if (!item)
        {
            continue;
        }
        painter.save();

        QColor color = m_color.toRgb();
        color.setAlphaF(item->opacity());
        painter.setBrush(color);

        // 限制半径在 5 <= radius <= 10
        const float radius = qBound(static_cast<float>(m_radius), m_radius / 200.0f * height(), 2.0f * m_radius);
        const float diameter = 2 * radius;

        painter.drawRoundedRect(QRectF(item->x() / 100.0f * width() - diameter, (height() - radius) / 2.0f, diameter, diameter), radius, radius);

        painter.restore();
    }
}

void DotFloating::initAnimations()
{
    // 创建5个圆形动画
    for (int index = 0; index < 5; ++index)
    {
        auto* item = new CircleItem(this);
        connect(item, &CircleItem::valueChanged, this, QOverload<>::of(&QWidget::update));

        // 串行动画组（无限循环）
        auto* seqAnimation = new QSequentialAnimationGroup(this);
        seqAnimation->setLoopCount(-1);

        m_items.append(qMakePair(item, seqAnimation));

        // 暂停延迟动画
        seqAnimation->addAnimation(new QPauseAnimation(150 * index, this));

        // 加速阶段 - 并行动画组1
        QPointer parAnimation1 = new QParallelAnimationGroup(this);

        // 透明度动画：0 -> 1.0
        QPointer opacityAnim1 = new QPropertyAnimation(item, "opacity", this);
        opacityAnim1->setDuration(400);
        opacityAnim1->setStartValue(0.0f);
        opacityAnim1->setEndValue(1.0f);
        parAnimation1->addAnimation(opacityAnim1);

        // x坐标动画：0 -> 25
        QPointer xAnim1 = new QPropertyAnimation(item, "x", this);
        xAnim1->setDuration(400);
        xAnim1->setStartValue(0.0f);
        xAnim1->setEndValue(25.0f);
        parAnimation1->addAnimation(xAnim1);

        seqAnimation->addAnimation(parAnimation1);

        // 匀速阶段
        QPointer xAnim2 = new QPropertyAnimation(item, "x", this);
        xAnim2->setDuration(1500);
        xAnim2->setStartValue(25.0f);
        xAnim2->setEndValue(75.0f);
        seqAnimation->addAnimation(xAnim2);

        // 减速阶段 - 并行动画组2
        QPointer parAnimation2 = new QParallelAnimationGroup(this);

        // 透明度动画：1.0 -> 0
        QPointer opacityAnim2 = new QPropertyAnimation(item, "opacity", this);
        opacityAnim2->setDuration(400);
        opacityAnim2->setStartValue(1.0f);
        opacityAnim2->setEndValue(0.0f);
        parAnimation2->addAnimation(opacityAnim2);

        // x坐标动画：75 -> 100
        QPointer xAnim3 = new QPropertyAnimation(item, "x", this);
        xAnim3->setDuration(400);
        xAnim3->setStartValue(75.0f);
        xAnim3->setEndValue(100.0f);
        parAnimation2->addAnimation(xAnim3);

        seqAnimation->addAnimation(parAnimation2);

        // 结束延迟动画
        seqAnimation->addAnimation(new QPauseAnimation((5 - index - 1) * 150, this));
    }

    for (const auto& val : m_items | std::views::values)
    {
        val->start();
    }
}

QSize DotFloating::sizeHint() const
{
    return QSize(100, m_radius * 2);
}
void DotFloating::stopAnimation()
{
    for (const auto& val : m_items | std::views::values)
    {
        if (val)
        {
            val->stop();
        }
    }
}
void DotFloating::startAnimation()
{
    for (const auto& val : m_items | std::views::values)
    {
        if (val)
        {
            val->start();
        }
    }
}

void DotFloating::resetAnimation()
{
    stopAnimation();

    for (const auto& item : m_items | std::views::keys)
    {
        if (item)
        {
            item->setX(0.0f);
            item->setOpacity(0.0f);
        }
    }
    startAnimation();
}
}  // namespace Vanilla