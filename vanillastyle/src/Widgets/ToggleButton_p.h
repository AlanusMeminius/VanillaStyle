#pragma once
#include "VanillaStyle/Widgets/ToggleButton.h"
#include <QPropertyAnimation>
#include <QtCore/QSizeF>

namespace Vanilla {

class ToggleButtonPrivate {
public:

    enum ButtonMode
    {
        IconOnly,
        TextOnly,
        IconWithText
    };

    explicit ToggleButtonPrivate(ToggleButton* q);
    void setCurrentIndex(int index);

private:
    void init();
    [[nodiscard]] QSize sizeHint() const;
    void setupAnimation();
    void paint(QPainter* painter);
    void paintIcon(QPainter* painter, QRect& rect);
    void paintText(QPainter* painter, QRectF& rect);
    void setColor();
    void checkMode();

private:
    QStringList itemList;
    QStringList iconList;
    int itemSize = 0;
    ButtonMode mode = IconOnly;
    bool m_mouseDown = false;
    bool isCustomIconColor = false;
    int currentIndex = 0;
    int preIndex = 0;
    int offset = 0;
    int radius = 6;
    int handleRadius = 5;
    int rowHeight = 28;
    int columnWidth = 70;
    int padding = 5;
    int handlePadding = 2;
    int handleSize = rowHeight - handlePadding * 2;
    int iconSize = rowHeight - padding * 2;

    QColor handleColor;
    QColor backgroundColor;
    QColor textColor;
    QColor iconColor;
    QColor styleIconColor;

    QPropertyAnimation handleAnimation;

private:
    ToggleButton* const q_ptr;
    Q_DECLARE_PUBLIC(ToggleButton);
};

} // VanillaStyle
