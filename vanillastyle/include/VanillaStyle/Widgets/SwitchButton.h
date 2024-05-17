#pragma once
#include <QWidget>

namespace Vanilla
{
class SwitchButtonPrivate;
class SwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget* parent = nullptr);
    ~SwitchButton();
    [[nodiscard]] QSize sizeHint() const override;


    Q_SIGNAL void toggled(bool checked);
    Q_SIGNAL void checked(bool checked);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    SwitchButtonPrivate* d_ptr;

private:
    Q_DECLARE_PRIVATE(SwitchButton);
};
}  // namespace Vanilla