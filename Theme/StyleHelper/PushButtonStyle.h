#pragma once
#include <QSize>
#include "CommonStyle.h"

class QPainter;
class QPushButton;
class QStyleOptionButton;
class QWidget;

namespace Theme
{

class PushButtonStyle
{
public:
    explicit PushButtonStyle();
    void setupPainterForShape(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget);
    void drawButtonShape(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget);
    QSize sizeFromContents(const QStyleOptionButton* option, QSize contentsSize, const QWidget* widget) const;
    void adjustTextPalette(QStyleOptionButton* option) const;

private:
    std::shared_ptr<CommonStyle> commonStyle;
};

}  // namespace Theme
