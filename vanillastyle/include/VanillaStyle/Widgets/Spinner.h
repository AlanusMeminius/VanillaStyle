#pragma once
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QColor>
#include "VanillaStyle/vglobal.h"

namespace Vanilla
{
class SpinnerPrivate;
class VANILLA_EXPORT Spinner : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int delta READ getDelta WRITE setDelta NOTIFY deltaChanged)

public:
    explicit Spinner(QWidget* parent = nullptr);
    ~Spinner();
    [[nodiscard]] QSize sizeHint() const override;

    [[nodiscard]] int getDelta() const;
    void setDelta(int value);

    void updataPosition();

signals:
    void deltaChanged();

protected:
    void paintEvent(QPaintEvent* event) override;
    SpinnerPrivate* d_ptr;

private:
    int delta = 36;
    int circleRadius = 15;
    int innerCircleRadius = 20;
    Q_DECLARE_PRIVATE(Spinner);
};

}  // namespace Vanilla
