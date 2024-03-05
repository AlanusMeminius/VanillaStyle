#pragma once
#include <QWidget>
#include <QStyleOption>
#include "VanillaStyle/Theme/Theme.h"
namespace VanillaStyle
{

class SpinBoxStyle
{
public:
    void draw(const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget, const Theme* theme) const;
    QRect subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex* option, QStyle::SubControl subControl, const QWidget* widget) const;
    int pixelMetric(QStyle::PixelMetric pm, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const;
};

}  // namespace VanillaStyle
