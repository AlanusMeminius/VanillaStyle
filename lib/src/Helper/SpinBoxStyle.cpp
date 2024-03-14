#include "VanillaStyle/Helper/SpinBoxStyle.h"
#include <QPainter>
#include <QPainterPath>

namespace VanillaStyle
{
void SpinBoxStyle::draw(const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget, const Theme* theme) const
{
    if (const auto* optionSpinBox = qstyleoption_cast<const QStyleOptionSpinBox*>(option))
    {
        painter->setRenderHint(QPainter::Antialiasing, true);

        // 画边框
        const auto spinBoxRect = optionSpinBox->rect.adjusted(1, 1, -1, -1);
        painter->setPen(theme->getColor(optionSpinBox, Theme::ColorRole::LineEditOutline));
        painter->drawRoundedRect(spinBoxRect, 5, 5);

        // 画箭头
        if (optionSpinBox->buttonSymbols != QAbstractSpinBox::NoButtons)
        {
            if (const auto upButtonRect = subControlRect(QStyle::CC_SpinBox, option, QStyle::SC_SpinBoxUp, widget); upButtonRect.isValid())
            {
                const auto iconPath = theme->getIconPath(Theme::IconRole::UpArrow);
                drawUpArrow(iconPath, painter, upButtonRect, QColor(255, 255, 255));
            }
            if (const auto downButtonRect = subControlRect(QStyle::CC_SpinBox, option, QStyle::SC_SpinBoxDown, widget); downButtonRect.isValid())
            {
                const auto iconPath = theme->getIconPath(Theme::IconRole::DownArrow);
                drawDownArrow(iconPath, painter, downButtonRect, QColor(255, 255, 255));
            }
        }
    }
}
QRect SpinBoxStyle::subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex* option, QStyle::SubControl subControl,
                                   const QWidget* widget) const
{
    if (control == QStyle::CC_SpinBox)
    {
        if (const auto* spinboxOpt = qstyleoption_cast<const QStyleOptionSpinBox*>(option))
        {
            switch (subControl)
            {
            case QStyle::SC_SpinBoxUp:
                if (spinboxOpt->buttonSymbols != QAbstractSpinBox::NoButtons)
                {
                    const auto iconDimension = pixelMetric(QStyle::PM_ButtonIconSize);
                    const auto buttonW = iconDimension + 2 * 2;
                    const auto& totalRect = spinboxOpt->rect;
                    const auto buttonH = totalRect.height() / 2;
                    const auto buttonX = totalRect.right() - buttonW;
                    const auto buttonY = totalRect.top();
                    return QRect{buttonX, buttonY, buttonW, buttonH};
                }
                return {};

            case QStyle::SC_SpinBoxDown:
                if (spinboxOpt->buttonSymbols != QAbstractSpinBox::NoButtons)
                {
                    const auto iconDimension = pixelMetric(QStyle::PM_ButtonIconSize);
                    const auto buttonW = iconDimension + 2 * 2;
                    const auto& totalRect = spinboxOpt->rect;
                    const auto buttonH = totalRect.height() / 2;
                    const auto buttonX = totalRect.right() - buttonW;
                    const auto buttonY = totalRect.bottom() + 1 - buttonH;  // cf. Qt documentation.
                    return QRect{buttonX, buttonY, buttonW, buttonH};
                }

                return {};

            case QStyle::SC_SpinBoxEditField:
                if (spinboxOpt->buttonSymbols != QAbstractSpinBox::NoButtons)
                {
                    const auto iconDimension = pixelMetric(QStyle::PM_ButtonIconSize);
                    const auto buttonW = iconDimension + 2 * 2 + 1;
                    const auto& totalRect = spinboxOpt->rect;
                    return QRect{totalRect.x(), totalRect.y(), totalRect.width() - buttonW, totalRect.height()};
                }
                return spinboxOpt->rect;

            case QStyle::SC_SpinBoxFrame:
                return option->rect;
            default:
                break;
            }
        }
    }
    return {};
}
int SpinBoxStyle::pixelMetric(QStyle::PixelMetric pm, const QStyleOption* option, const QWidget* widget) const
{
    return 12;
}

}  // namespace VanillaStyle