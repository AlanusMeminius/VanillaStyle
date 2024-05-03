#pragma once
#include <QAbstractButton>

namespace Vanilla
{

class IconButtonPrivate;
class IconButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit IconButton(QWidget* parent = nullptr);
    explicit IconButton(const QIcon& icon, QWidget* parent = nullptr);
    ~IconButton();
    [[nodiscard]] QSize sizeHint() const override;
    void setCustomIconColor(const QColor& color);

protected:
    void paintEvent(QPaintEvent* event) override;
    IconButtonPrivate* d_ptr;

private:
    Q_DECLARE_PRIVATE(IconButton);
};

}  // namespace Vanilla
