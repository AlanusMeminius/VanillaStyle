#pragma once
#include <QColor>
#include <QTimer>
#include <vector>

#include "VanillaStyle/Widgets/Spinner.h"

namespace Vanilla
{
constexpr int circle = 360;

class SpinnerPrivate
{
public:
    explicit SpinnerPrivate(Spinner* q);
    ~SpinnerPrivate();
    void init();

private:
    void updateColor();
    void paint(QPainter* painter);
    [[nodiscard]] QSize sizeHint() const;

private:
    int angle = 0;
    int delta = 36;
    int circleRadius = 15;
    int innerCircleRadius = 25;
    int numCircles = circle / delta + 1;

    std::vector<QColor> m_colors;
    QColor m_color;
    QTimer* timer;
    Spinner* const q_ptr;
    Q_DECLARE_PUBLIC(Spinner);
};

}  // namespace Vanilla
