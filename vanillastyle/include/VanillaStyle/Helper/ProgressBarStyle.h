#pragma once

#include <memory>

#include <QRect>
#include <QStyle>

class QPainter;
class QStyleOption;
class QWidget;

namespace Vanilla
{
class Theme;

class VANILLA_EXPORT ProgressBarStyle
{
public:
    bool drawGroove(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    bool drawContents(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    bool drawLabel(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    QRect subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
};

}  // namespace VanillaStyle
