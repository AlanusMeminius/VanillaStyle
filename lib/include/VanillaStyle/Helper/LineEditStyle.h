#pragma once
#include "Helper.h"
#include "VanillaStyle/Theme/Theme.h"
namespace VanillaStyle
{
class LineEditStyle : public Helper
{
public:
    bool draw(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const;
    QRect subElementRect(QStyle::SubElement element, const QStyleOption* option, const QWidget* widget) const;
//    QRect subControlRect(QStyle::ComplexControl control, const QStyleOption* option, QStyle::SubControl subControl, const QWidget* widget) const;
//    int pixelMetric(QStyle::PixelMetric pm, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const;
};

}  // namespace VanillaStyle
