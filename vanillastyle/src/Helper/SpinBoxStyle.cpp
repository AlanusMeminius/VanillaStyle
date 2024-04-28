#include <QPainterPath>
#include <QPainter>

#include "VanillaStyle/Helper/SpinBoxStyle.h"

#include "VanillaStyle/Helper/Common.h"
#include "VanillaStyle/Theme/Theme.h"

namespace Vanilla
{
bool SpinBoxStyle::draw(const QStyleOptionComplex* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionSpinBox*>(option);
    if (!opt)
    {
        return true;
    }
    painter->setRenderHint(QPainter::Antialiasing, true);

    // 画边框
    const auto spinBoxRect = opt->rect.adjusted(1, 1, -1, -1);
    painter->setPen(theme->getColor(opt, Theme::ColorRole::LineEditOutline));
    painter->drawRoundedRect(spinBoxRect, 5, 5);

    // 画箭头
    if (opt->buttonSymbols != QAbstractSpinBox::NoButtons)
    {
        if (const auto upButtonRect = subControlRect(QStyle::CC_SpinBox, option, QStyle::SC_SpinBoxUp, theme, widget); upButtonRect.isValid())
        {
            const auto iconPath = theme->getIconPath(Theme::IconRole::UpArrow);
            const auto svg = theme->getCachedIcon(iconPath, theme->getColor(option, Theme::ColorRole::IndicatorColor));
            renderSvgFromString(svg, painter, upButtonRect);
        }
        if (const auto downButtonRect = subControlRect(QStyle::CC_SpinBox, option, QStyle::SC_SpinBoxDown, theme, widget); downButtonRect.isValid())
        {
            const auto iconPath = theme->getIconPath(Theme::IconRole::DownArrow);
            const auto svg = theme->getCachedIcon(iconPath, theme->getColor(option, Theme::ColorRole::IndicatorColor));
            renderSvgFromString(svg, painter, downButtonRect);
        }
    }
    return true;
}
QRect SpinBoxStyle::subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex* option, QStyle::SubControl subControl,
                                   const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    if (control == QStyle::CC_SpinBox)
    {
        const auto* opt = qstyleoption_cast<const QStyleOptionSpinBox*>(option);
        if (!opt)
        {
            return {};
        }
        const auto padding = theme->getSize(Theme::SizeRole::NormalBorder);
        const auto& rect = opt->rect;
        const auto iconSize = theme->getSize(Theme::IconSize);

        switch (subControl)
        {
        case QStyle::SC_SpinBoxUp:
            if (opt->buttonSymbols != QAbstractSpinBox::NoButtons)
            {
                return rect.adjusted(rect.width() - iconSize, 0, 0, -rect.height() / 2);
            }
            return {};

        case QStyle::SC_SpinBoxDown:
            if (opt->buttonSymbols != QAbstractSpinBox::NoButtons)
            {
                return rect.adjusted(rect.width() - iconSize, rect.height() / 2, 0, 0);
            }

            return {};

        case QStyle::SC_SpinBoxEditField:
            if (opt->buttonSymbols != QAbstractSpinBox::NoButtons)
            {
                return rect.adjusted(0, 0, -iconSize + 2 * padding, 0);
            }
            return opt->rect;

        case QStyle::SC_SpinBoxFrame:
            return option->rect;
        default:
            break;
        }
    }
    return {};
}
int SpinBoxStyle::pixelMetric(QStyle::PixelMetric pm, const QStyleOption* option, const QWidget* widget) const
{
    return 12;
}

}  // namespace Vanilla