#pragma once
#include "Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle
{

class ProgressBarStyle : public Helper
{
public:
    bool drawGroove(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const;
    bool drawContents(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const;
    bool drawLabel(const QStyleOption* option, QPainter* painter, const Theme* theme, const QWidget* widget) const;
    QRect subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const;
};

}  // namespace VanillaStyle
