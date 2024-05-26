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
    void getMaxLenStr(const QStringList& list);

    [[nodiscard]] int getHandleSize() const
    {
        return rowHeight - handlePadding * 2;
    }
    [[nodiscard]] int getIconSize() const
    {
        return rowHeight - padding * 2;
    }

private:
    QStringList itemList;
    QStringList iconList;
    int itemSize = 0;
    ButtonMode mode = IconOnly;
    bool m_mouseDown = false;
    bool isCustomIconColor = false;
    bool enableBackground = true;
    bool isVertical = false;
    int currentIndex = 0;
    int preIndex = 0;
    int offset = 0;
    int radius = 6;
    int handleRadius = 5;
    int padding = 5;
    int textWidth = 0;
    int rowHeight = 28;
    int columnWidth = 70;
    int handlePadding = 2;
    int handleSize = getHandleSize();
    int iconSize = getIconSize();

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
