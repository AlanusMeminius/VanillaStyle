#pragma once
#include <QSize>
#include "VanillaStyle/Widgets/IconButton.h"

namespace VanillaStyle {

class IconButtonPrivate
{
public:
    explicit IconButtonPrivate(IconButton* q);
    void init();

private:

    [[nodiscard]] QSize sizeHint() const;
    void paint(QPainter* painter);
    IconButton* const q_ptr;
    Q_DECLARE_PUBLIC(IconButton);
};


} // VanillaStyle
