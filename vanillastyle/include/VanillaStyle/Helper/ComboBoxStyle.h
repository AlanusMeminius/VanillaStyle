#pragma once

#include <QStyle>
#include <memory>

class QComboBox;
class QPainter;
class QStyleOptionComplex;
class QWidget;

namespace Vanilla
{
class Theme;

class ComboBoxStyle
{
public:
    bool draw(const QStyleOptionComplex* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    bool drawIndicator(const QStyleOptionComplex* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    QRect subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex* option, QStyle::SubControl subControl, const std::shared_ptr<Theme>& theme,
                     const QWidget* widget) const;
    void eventFilter(QComboBox* obj) const;
};

}  // namespace Vanilla
