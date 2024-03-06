#pragma once
#include <QWidget>
#include <QStyleOption>
#include "VanillaStyle/Theme/Theme.h"
namespace VanillaStyle
{
class LineEditStyle
{
public:
    void draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme) const;
    QRect subElementRect(QStyle::SubElement element, const QStyleOption* option, const QWidget* widget) const;
//    QRect subControlRect(QStyle::ComplexControl control, const QStyleOption* option, QStyle::SubControl subControl, const QWidget* widget) const;
//    int pixelMetric(QStyle::PixelMetric pm, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const;
};

}  // namespace VanillaStyle
