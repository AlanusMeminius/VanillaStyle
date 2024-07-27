#pragma once

#include <memory>

#include "VanillaStyle/vglobal.h"

class QPainter;
class QStyleOption;
class QWidget;

namespace Vanilla
{
class Theme;
class VANILLA_EXPORT ItemViewStyle
{
public:
    bool draw(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    void drawBackground(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget = nullptr) const;
    void drawCheck(const QStyleOptionViewItem*, QPainter*, const std::shared_ptr<Theme>&, const QWidget* = nullptr) const;
    QSize sizeFromContentsForItemView(QStyle::ContentsType type, const QStyleOption* option, const QSize& contentsSize, const std::shared_ptr<Theme>&, const QWidget* widget);

};

}  // namespace Vanilla
