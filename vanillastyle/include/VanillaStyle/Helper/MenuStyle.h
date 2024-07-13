#pragma once

#include <memory>
#include <QStyle>
#include <QRect>
#include <QColor>

#include "VanillaStyle/vglobal.h"

class QStyleOption;
class QPainter;
class QWidget;
class QMenu;

namespace Vanilla
{
class Theme;
class VANILLA_EXPORT MenuStyle
{
public:
    bool drawPrimitive(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget = nullptr) const;
    bool drawMenuItem(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget = nullptr) const;
    void drawMenuSeparator(QPainter* painter, const QRect& rect, QColor const& color, int padding) const;
    void eventFilter(QMenu* obj) const;
    QSize sizeFromContentsForMenuItem(QStyle::ContentsType type, const QStyleOption* option, const QSize& contentsSize, const std::shared_ptr<Theme>&, const QWidget* widget);
};

}  // namespace Vanilla
