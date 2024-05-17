#pragma once
#include <QAbstractButton>
#include <QColor>
#include <QFont>

#include "VanillaStyle/Theme/Theme.h"


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

    void usingOriginalIconColor();
    void setIconColor(const QColor& color);
    void setIconFirst();
    void setTextColor(const QColor& textColor);
    void setTextSizeRole(const TextSizeRole& textSizeRole);
    void setButtonBorderColor(const QColor& color);

protected:
    void paintEvent(QPaintEvent* event) override;

protected:
    IconButtonPrivate* d_ptr;

private:
    Q_DECLARE_PRIVATE(IconButton);
};

}  // namespace Vanilla
