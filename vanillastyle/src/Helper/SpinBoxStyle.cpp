#include <QPainterPath>
#include <QPainter>

#include "VanillaStyle/Helper/SpinBoxStyle.h"

#include "VanillaStyle/Helper/Common.h"
#include "VanillaStyle/Helper/Helper.h"
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

    const auto rect = QRectF(opt->rect).adjusted(1, 1, -1, -1);
    // 画背景
    const auto bgColor = theme->getColor(opt, ColorRole::LineEditBackground);
    Helper::renderRoundRect(painter, rect, bgColor, 5);

    // 画边框
    const auto fgColor = theme->getColor(opt, ColorRole::LineEditOutline);
    Helper::renderRoundBorder(painter, rect, fgColor, 1.5, 5);


    // 画箭头
    if (opt->buttonSymbols != QAbstractSpinBox::NoButtons)
    {
        if (const auto upButtonRect = subControlRect(QStyle::CC_SpinBox, option, QStyle::SC_SpinBoxUp, theme, widget); upButtonRect.isValid())
        {
            const auto iconPath = theme->getIconPath(IconRole::UpArrow);
            const auto svg = theme->getCachedIcon(iconPath, theme->getColor(option, ColorRole::IconColor));
            renderSvgFromString(svg, painter, upButtonRect);
        }
        if (const auto downButtonRect = subControlRect(QStyle::CC_SpinBox, option, QStyle::SC_SpinBoxDown, theme, widget); downButtonRect.isValid())
        {
            const auto iconPath = theme->getIconPath(IconRole::DownArrow);
            const auto svg = theme->getCachedIcon(iconPath, theme->getColor(option, ColorRole::IndicatorColor));
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
        const auto padding = theme->getSize(SizeRole::NormalBorder);
        const auto& rect = opt->rect;
        const auto iconSize = theme->getSize(SizeRole::IconSize);

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
                return rect.adjusted(1, 1, -iconSize + padding, 0);
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