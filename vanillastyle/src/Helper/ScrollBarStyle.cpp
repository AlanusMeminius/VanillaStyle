#include <QPainter>

#include "VanillaStyle/Helper/ScrollBarStyle.h"
#include "VanillaStyle/Helper/Common.h"
#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle/Helper/Helper.h"

namespace Vanilla
{

bool ScrollBarStyle::drawSlider(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionSlider*>(option);
    if (opt == nullptr)
    {
        return true;
    }
    painter->setRenderHint(QPainter::Antialiasing, true);
    const QRectF rect = opt->rect;
    const auto radius = theme->getSize(SizeRole::SmallRadius);
    const auto color = theme->getColor(option, ColorRole::ScrollBarSliderColor);
    const auto scrollBarWidth = theme->getSize(SizeRole::ScrollBarWidth);
    if (opt->orientation == Qt::Horizontal)
    {
        const QRectF handleRect = centerRectF(rect, rect.width(), scrollBarWidth);
        Helper::renderRoundRect(painter, handleRect, color, radius);
        return true;
    }
    else
    {
        const QRectF handleRect = centerRectF(rect, scrollBarWidth, rect.height());
        Helper::renderRoundRect(painter, handleRect, color, radius);
        return true;
    }

}

bool ScrollBarStyle::drawAddLine(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionSlider*>(option);
    if (opt == nullptr)
    {
        return true;
    }
    painter->setRenderHint(QPainter::Antialiasing);
    const auto indicatorRect = QRectF(opt->rect);
    const auto iconPath = theme->getIconPath(opt->orientation == Qt::Horizontal ? IconRole::RightArrow : IconRole::DownArrow);
    const auto iconSize = theme->getSize(SizeRole::IconSize);
    auto iconRect = QRectF(0, 0, iconSize, iconSize);
    iconRect.moveCenter(indicatorRect.center());
    const auto svg = theme->getCachedIcon(iconPath, theme->getColor(option, ColorRole::IndicatorColor));
    renderSvgFromString(svg, painter, iconRect);
    return true;
}

bool ScrollBarStyle::drawSubLine(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionSlider*>(option);
    if (opt == nullptr)
    {
        return true;
    }
    painter->setRenderHint(QPainter::Antialiasing);
    const auto indicatorRect = QRectF(opt->rect);
    const auto iconPath = theme->getIconPath(opt->orientation == Qt::Horizontal ? IconRole::LeftArrow : IconRole::UpArrow);
    const auto iconSize = theme->getSize(SizeRole::IconSize);
    auto iconRect = QRectF(0, 0, iconSize, iconSize);
    iconRect.moveCenter(indicatorRect.center());
    const auto svg = theme->getCachedIcon(iconPath, theme->getColor(option, ColorRole::IconColor));
    renderSvgFromString(svg, painter, iconRect);
    return true;
}
}  // namespace Vanilla