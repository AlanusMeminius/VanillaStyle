#pragma once
#include <QAbstractButton>

namespace VanillaStyle {

class IconButtonPrivate;
class IconButton : public QAbstractButton{

    Q_OBJECT
public:
    explicit IconButton(QWidget* parent = nullptr);
    explicit IconButton(const QIcon& icon, QWidget* parent = nullptr);

    [[nodiscard]] QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;
    IconButtonPrivate* d_ptr;

private:
    Q_DECLARE_PRIVATE(IconButton);
};

} // VanillaStyle
