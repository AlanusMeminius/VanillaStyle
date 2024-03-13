#pragma once
#include "VanillaStyle/Widgets/IconLabel.h"
#include <QSize>

namespace VanillaStyle
{

class IconLabelPrivate
{
public:
    explicit IconLabelPrivate(IconLabel* q);
    void init();

private:
    QSize m_iconSize;
    int m_labelWidth = 0;
    int padding = 4;
    QIcon m_icon;
    QString m_label;
    Qt::LayoutDirection m_layoutDirection = Qt::LeftToRight;

    [[nodiscard]] QSize sizeHint() const;
    void paint(QPainter* painter);

private:
    IconLabel* const q_ptr;
    Q_DECLARE_PUBLIC(IconLabel);
};

}  // namespace VanillaStyle
