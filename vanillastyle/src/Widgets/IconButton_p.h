#pragma once
#include <QSize>
#include <QColor>
#include "VanillaStyle/Widgets/IconButton.h"

namespace Vanilla {

class IconButtonPrivate
{
public:
    explicit IconButtonPrivate(IconButton* q);
    void init();

private:
    [[nodiscard]] QSize sizeHint() const;
    void paint(QPainter* painter);
    void setUpColor();

private:
    int padding = 2;
    QColor iconColor;
    bool isCustomIconColor = false;
    IconButton* const q_ptr;
    Q_DECLARE_PUBLIC(IconButton);
};


} // VanillaStyle
