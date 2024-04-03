#pragma once
#include "VanillaStyle/Widgets/ToggleButton.h"
#include <QPropertyAnimation>
#include <QtCore/QSizeF>

namespace Vanilla {

class ToggleButtonPrivate {
public:
    explicit ToggleButtonPrivate(ToggleButton* q);
    void init();
    void setCurrentIndex(int index);

    void setupAnimation();
private:
    QStringList itemList;

    bool m_useIcon = true;

    bool m_mouseDown = false;

    int currentIndex = 0;
    int preIndex = 0;
    int offset = 0;
    int radius = 6;
    int rowHeight = 26;
    int columnWidth = 70;
    int padding = 5;
    int handlePadding = 2;
    int handleSize = rowHeight - handlePadding * 2;
    int iconSize = rowHeight - padding * 2;
    QPropertyAnimation handleAnimation;

public:
    [[nodiscard]] QSize sizeHint() const;

private:
    void paint(QPainter* painter);
    ToggleButton* const q_ptr;
    Q_DECLARE_PUBLIC(ToggleButton);
};

} // VanillaStyle
