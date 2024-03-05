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
        const auto spinBoxEnabled = optionSpinBox->state.testFlag(QStyle::State_Enabled);
        if (optionSpinBox->buttonSymbols != QAbstractSpinBox::NoButtons)
        {
            const auto radius = theme->getRadius(Theme::ButtonRadius);
            const auto upButtonRect = subControlRect(QStyle::CC_SpinBox, option, QStyle::SC_SpinBoxUp, widget);
            if (upButtonRect.isValid())
            {
                painter->setPen(Qt::NoPen);
                painter->setBrush(QColor(255, 12, 23));
                painter->drawRoundedRect(upButtonRect, radius, radius);

                painter->setPen(QPen(QColor(123, 23, 34), 8, Qt::SolidLine, Qt::FlatCap));
                painter->setBrush(Qt::NoBrush);
                auto rect = upButtonRect.adjusted(4, 4, -4, -4);
                const auto p1 = QPointF{(1. / 8.) * rect.width() + rect.x(), (5. / 8.) * rect.width() + rect.y()};
                const auto p2 = QPointF{(4. / 8.) * rect.width() + rect.x(), (2. / 8.) * rect.width() + rect.y()};
                const auto p3 = QPointF{(7. / 8.) * rect.width() + rect.x(), (5. / 8.) * rect.width() + rect.y()};
                QPainterPath path;
                path.moveTo(p1);
                path.lineTo(p2);
                path.lineTo(p3);
                painter->drawPath(path);
            }

            const auto downButtonRect = subControlRect(QStyle::CC_SpinBox, option, QStyle::SC_SpinBoxDown, widget);

            if (downButtonRect.isValid())
            {
                painter->setPen(Qt::NoPen);
                painter->setBrush(QColor(255, 12, 23));
                painter->drawRoundedRect(downButtonRect, radius, radius);

                painter->setPen(QPen(QColor(123, 23, 34), 8, Qt::SolidLine, Qt::FlatCap));
                painter->setBrush(Qt::NoBrush);
                auto rect = downButtonRect.adjusted(4, 4, -4, -4);
                const auto p1 = QPointF{(1. / 8.) * rect.width() + rect.x(), (3. / 8.) * rect.width() + rect.y()};
                const auto p2 = QPointF{(4. / 8.) * rect.width() + rect.x(), (6. / 8.) * rect.width() + rect.y()};
                const auto p3 = QPointF{(7. / 8.) * rect.width() + rect.x(), (3. / 8.) * rect.width() + rect.y()};
                QPainterPath path;
                path.moveTo(p1);
                path.lineTo(p2);
                path.lineTo(p3);
                painter->drawPath(path);
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
                else
                {
                    return {};
                }
                break;
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
                else
                {
                    return {};
                }
                break;
            case QStyle::SC_SpinBoxEditField:
                if (spinboxOpt->buttonSymbols != QAbstractSpinBox::NoButtons)
                {
                    const auto iconDimension = pixelMetric(QStyle::PM_ButtonIconSize);
                    const auto buttonW = iconDimension + 2 * 2 + 1;
                    const auto& totalRect = spinboxOpt->rect;
                    return QRect{totalRect.x(), totalRect.y(), totalRect.width() - buttonW, totalRect.height()};
                }
                else
                {
                    return spinboxOpt->rect;
                }
                break;
            case QStyle::SC_SpinBoxFrame:
                return option->rect;
                break;
            default:
                break;
            }
        }
    }
    return {};
}
int SpinBoxStyle::pixelMetric(QStyle::PixelMetric pm, const QStyleOption* option, const QWidget* widget) const
{
    return 18;
}

}  // namespace VanillaStyle