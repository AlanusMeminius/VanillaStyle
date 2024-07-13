#pragma once

#include <memory>

#include <QStyle>
#include <QRect>

#include "VanillaStyle/vglobal.h"

class QStyleOptionComplex;
class QPainter;
class QWidget;

namespace Vanilla
{
class Theme;

class VANILLA_EXPORT SpinBoxStyle
{
public:
    bool draw(const QStyleOptionComplex* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    QRect subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex* option, QStyle::SubControl subControl, const std::shared_ptr<Theme>& theme,
                         const QWidget* widget) const;
    int pixelMetric(QStyle::PixelMetric pm, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const;
};

}  // namespace Vanilla
