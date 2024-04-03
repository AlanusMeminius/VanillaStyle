#pragma once
#include "VanillaStyle/Widgets/IconLabel.h"
#include <QSize>
#include <QIcon>

namespace Vanilla
{

class IconLabelPrivate
{
public:
    explicit IconLabelPrivate(IconLabel* q);
    void init();

private:
    QSize iconSize;
    int labelWidth = 0;
    int padding = 4;
    QIcon icon;
    QString label;
    Qt::LayoutDirection layoutDirection = Qt::LeftToRight;

    [[nodiscard]] QSize sizeHint() const;
    void paint(QPainter* painter);

private:
    IconLabel* const q_ptr;
    Q_DECLARE_PUBLIC(IconLabel);
};

}  // namespace VanillaStyle
