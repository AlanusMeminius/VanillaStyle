#pragma once
#include <QColor>
#include <QTimer>

#include "VanillaStyle/Widgets/Spinner.h"


namespace Vanilla
{
class SpinnerPrivate
{
public:
    explicit SpinnerPrivate(Spinner* q);
    void init();

private:
    void updateColor();
    void paint(QPainter* painter);

private:
    int angle = 0;

    QColor color_;
    QTimer* timer;
    Spinner* const q_ptr;
    Q_DECLARE_PUBLIC(Spinner);
};


}  // namespace Vanilla
