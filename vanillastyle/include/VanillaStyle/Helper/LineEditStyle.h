#pragma once

#include <memory>

#include <QRect>
#include <QStyle>

#include "VanillaStyle/vglobal.h"

class QPainter;
class QStyleOption;
class QWidget;

namespace Vanilla
{
class Theme;

class VANILLA_EXPORT LineEditStyle
{
public:
    bool draw(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    QRect subElementRect(QStyle::SubElement element, const QStyleOption* option, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    //    QRect subControlRect(QStyle::ComplexControl control, const QStyleOption* option, QStyle::SubControl subControl, const QWidget* widget) const;
    //    int pixelMetric(QStyle::PixelMetric pm, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const;
};

}  // namespace Vanilla
