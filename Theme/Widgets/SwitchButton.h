#pragma once
#include <QWidget>

class SwitchButtonPrivate;
class SwitchButton : public QWidget
{
    Q_OBJECT
    // Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY toggled)
    Q_PROPERTY(int handlePosition READ handlePosition WRITE setHandlePosition)
public:
    explicit SwitchButton(QWidget* parent = nullptr);

    [[nodiscard]] QSize sizeHint() const override;

    [[nodiscard]] int handlePosition() const;
    void setHandlePosition(int pos);
signals:
    void toggled(bool checked);
    void checked(bool checked);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    SwitchButtonPrivate* d_ptr;

private:
    Q_DECLARE_PRIVATE(SwitchButton);
};
