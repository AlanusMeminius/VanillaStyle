#pragma once
#include "CommonStyle.h"
#include <QStyleOption>
class QStyleOption;
class QPainter;
class QWidget;


class SpinBoxStyle
{
public:
    explicit SpinBoxStyle();

    void draw(const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const;
    void drawIndicator(QStyle::PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const;

private:
  std::shared_ptr<Theme::CommonStyle> commonStyle;
};
