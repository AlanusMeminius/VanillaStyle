#pragma once
#include "CommonStyle.h"
#include <QStyleOption>
class QStyleOption;
class QPainter;
class QWidget;

class ComboBoxStyle
{
public:
    explicit ComboBoxStyle();
    void draw(const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const;
    void drawIndicator(const QStyleOption* option, QPainter* painter) const;

private:
    std::shared_ptr<Theme::CommonStyle> commonStyle;
};
