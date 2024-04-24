#pragma once
#include <QSize>
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

private:
    int padding = 2;
    IconButton* const q_ptr;
    Q_DECLARE_PUBLIC(IconButton);
};


} // VanillaStyle
