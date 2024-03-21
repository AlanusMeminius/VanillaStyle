#pragma once
#include "Helper.h"
#include "VanillaStyle/Theme/Theme.h"
namespace VanillaStyle
{

class SpinBoxStyle : public Helper
{
public:
    bool draw(const QStyleOptionComplex* option, QPainter* painter, const Theme* theme, const QWidget* widget) const;
    QRect subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex* option, QStyle::SubControl subControl, const QWidget* widget) const;
    int pixelMetric(QStyle::PixelMetric pm, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const;
};

}  // namespace VanillaStyle
