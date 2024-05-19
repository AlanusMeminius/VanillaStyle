#pragma once

#include <memory>

#include <QStyle>

class QPainter;
class QStyleOption;
class QWidget;

namespace Vanilla
{
class Theme;
class VANILLA_EXPORT RadioButtonStyle
{
public:
    bool draw(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget = nullptr) const;
    QRect subElementRect(QStyle::SubElement element, const QStyleOption* option, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
};
}  // namespace VanillaStyle