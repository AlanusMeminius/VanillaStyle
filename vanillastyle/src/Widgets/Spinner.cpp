#include "VanillaStyle/Widgets/Spinner.h"
#include "Spinner_p.h"
#include "VanillaStyle/Style/VanillaStyle.h"

namespace Vanilla
{

Spinner::Spinner(QWidget* parent)
    : QWidget(parent)
    , d_ptr(new SpinnerPrivate(this))
{
    Q_D(Spinner);
    d->init();
}

Spinner::~Spinner()
{
    delete d_ptr;
}

QSize Spinner::sizeHint() const
{
    Q_D(const Spinner);
    return d->sizeHint();
}

int Spinner::getDelta() const
{
    return delta;
}

void Spinner::setDelta(const int value)
{
    Q_D(Spinner);
    if (delta == value)
    {
        return;
    }
    delta = value;
    d->angle = 0;
    d->timer->start();
    emit deltaChanged();
}

void Spinner::updataPosition()
{
    if (const auto* parent = parentWidget(); parent != nullptr)
    {
        const int x = parent->width() / 2 - width() / 2;
        const int y = parent->height() / 2 - height() / 2;
        move(x, y);
    }
}

void Spinner::paintEvent(QPaintEvent* /*event*/)
{
    Q_D(Spinner);
    QPainter painter(this);
    updataPosition();
    d->paint(&painter);
}

SpinnerPrivate::SpinnerPrivate(Spinner* q)
    : timer(new QTimer(q))
    , q_ptr(q)
{
}

SpinnerPrivate::~SpinnerPrivate()
{
    delete timer;
}

void SpinnerPrivate::init()
{
    Q_Q(Spinner);
    q->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    q->setFocusPolicy(Qt::NoFocus);

    QObject::connect(timer, &QTimer::timeout, q, QOverload<>::of(&Spinner::update));
    timer->start(100);
    updateColor();
}

void SpinnerPrivate::updateColor()
{
    Q_Q(Spinner);
    if (auto* customStyle = qobject_cast<VanillaStyle*>(q->style()))
    {
        m_color = customStyle->getCustomColor(Theme::ColorRole::ButtonForeground);
    }
    else
    {
        m_color = QColor(22, 121, 171);  // rgb(237, 148, 85)
    }

    m_colors = std::vector(numCircles, m_color.toRgb());
    for (int i = 0; i < numCircles; i++)
    {
        const float alpha = static_cast<float>(i) / static_cast<float>(numCircles);
        m_colors[i].setAlphaF(alpha * (1.0F - alpha));
    }
}

void SpinnerPrivate::paint(QPainter* painter)
{
    Q_Q(Spinner);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(q->width() / 2, q->height() / 2);
    const auto miniSide = std::min(q->width(), q->height());
    painter->scale(miniSide / 100., miniSide / 100.);
    painter->rotate(angle);
    painter->setPen(Qt::NoPen);
    for (const auto& color : m_colors)
    {
        painter->setBrush(color);
        painter->drawEllipse(innerCircleRadius, -innerCircleRadius, circleRadius, circleRadius);
        painter->rotate(delta);
    }
    angle += delta;
    angle %= circle;
}

QSize SpinnerPrivate::sizeHint() const
{
    return {2 * (innerCircleRadius + circleRadius), 2 * (innerCircleRadius + circleRadius)};
}
}  // namespace Vanilla