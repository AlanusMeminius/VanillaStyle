#pragma once
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QColor>

namespace Vanilla
{
class SpinnerPrivate;
class Spinner : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int delta READ getDelta WRITE setDelta NOTIFY deltaChanged)

public:
    explicit Spinner(QWidget* parent = nullptr);
    ~Spinner();
    [[nodiscard]] QSize sizeHint() const override;

    [[nodiscard]] int getDelta() const;
    void setDelta(int value);

signals:
    void deltaChanged();

protected:
    void paintEvent(QPaintEvent* event) override;
    SpinnerPrivate* d_ptr;

private:
    int delta = 36;
    Q_DECLARE_PRIVATE(Spinner);
};

}  // namespace Vanilla
