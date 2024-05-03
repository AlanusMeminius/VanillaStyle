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
    if (!opt)
    {
        return true;
    }
    QRectF rect = opt->rect;
    const auto padding = theme->getSize(Theme::NormalPadding);
    QRectF handleRect = centerRectF(rect, rect.width() - 3 * padding, rect.height());
    painter->setRenderHint(QPainter::Antialiasing, true);
    const auto radius = theme->getSize(Theme::NormalRadius);
    const auto color = theme->getColor(option, Theme::ColorRole::IndicatorColor);
    Helper::renderRoundRect(painter, handleRect, color, radius);
    return true;
}

bool ScrollBarStyle::drawAddLine(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionSlider*>(option);
    if (!opt)
    {
        return true;
    }
    painter->setRenderHint(QPainter::Antialiasing);
    const auto indicatorRect = QRectF(opt->rect);
    const auto iconPath = theme->getIconPath(Theme::IconRole::DownArrow);
    const auto iconSize = theme->getSize(Theme::IconSize);
    auto iconRect = QRectF(0, 0, iconSize, iconSize);
    iconRect.moveCenter(indicatorRect.center());
    const auto svg = theme->getCachedIcon(iconPath, theme->getColor(option, Theme::ColorRole::IndicatorColor));
    renderSvgFromString(svg, painter, iconRect);
    return true;
}

bool ScrollBarStyle::drawSubLine(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionSlider*>(option);
    if (!opt)
    {
        return true;
    }
    painter->setRenderHint(QPainter::Antialiasing);
    const auto indicatorRect = QRectF(opt->rect);
    const auto iconPath = theme->getIconPath(Theme::IconRole::UpArrow);
    const auto iconSize = theme->getSize(Theme::IconSize);
    auto iconRect = QRectF(0, 0, iconSize, iconSize);
    iconRect.moveCenter(indicatorRect.center());
    const auto svg = theme->getCachedIcon(iconPath, theme->getColor(option, Theme::ColorRole::IndicatorColor));
    renderSvgFromString(svg, painter, iconRect);
    return true;
}
}  // namespace Vanilla