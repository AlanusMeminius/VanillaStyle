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
    return {100,100};
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

void Spinner::paintEvent(QPaintEvent* event)
{
    Q_D(Spinner);
    QPainter painter(this);
    d->paint(&painter);
}

SpinnerPrivate::SpinnerPrivate(Spinner* q)
    : timer(new QTimer(q))
    , q_ptr(q)
{
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
        color_ = customStyle->getCustomColor(Theme::ColorRole::ButtonForeground);
    } else
    {
        color_ = QColor(237, 148, 85);  //rgb(237, 148, 85)
    }
}

void SpinnerPrivate::paint(QPainter* painter)
{
    Q_Q(Spinner);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(q->width() / 2, q->height() / 2);
    int sideLength = qMin(q->width(), q->height());
    painter->scale(sideLength / 100.0, sideLength / 100.0);
    painter->rotate(angle);
    painter->setPen(Qt::NoPen);

    QColor currentColor = color_.toRgb();
    int numCircles = 360 / q->delta + 1;
    for (int i = 0; i < numCircles; i++)
    {
        double alpha = 1.0 * i / 10;
        currentColor.setAlphaF(alpha);
        painter->setBrush(currentColor);
        painter->drawEllipse(30, -10, 20, 20);
        painter->rotate(q->delta);
    }
    angle += q->delta;
    angle %= 360;
}
}  // namespace Vanilla