#include "CustomStyle.h"
#include <QApplication>
#include <QCheckBox>
#include <QLineEdit>
#include <QPainter>
#include <QPushButton>
#include <QScrollBar>

namespace Theme
{

CustomStyle::CustomStyle()
    : mProgressbarStyle(new ProgressbarStyle)
    , mPushButtonStyle(new PushButtonStyle)
    , mCheckBoxStyle(new CheckBoxStyle)
    , mLineEditStyle(new LineEditStyle)
    , mSpinBoxStyle(new SpinBoxStyle)
// , mSwitchButtonStyle(new SwitchButtonStyle)
{
}
void CustomStyle::drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    switch (pe)
    {
    case PE_IndicatorCheckBox:
    {
        if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
        {
            mCheckBoxStyle->draw(optionButton, painter, widget);
        }
        return;
    }
    case PE_FrameFocusRect:
        // {
        //     if (const auto *fropt = qstyleoption_cast<const QStyleOptionFocusRect
        //     *>(option)) {
        //         qDebug() << "PE_FrameFocusRect" << widget->objectName();
        //         const QRect focusRect = fropt->rect.adjusted(1, 1, -1, -1);
        //         painter->setPen(QColor(183, 132, 183));
        //         painter->drawRoundedRect(focusRect, 5, 5);
        //     }
        //     break;
        // }
        break;
    case PE_PanelLineEdit:
    {
        if (const auto* panel = qstyleoption_cast<const QStyleOptionFrame*>(option))
        {
            mLineEditStyle->drawPanel(panel, painter, widget);
        }
        break;
    }
    // case PE_IndicatorSpinUp:
    // case PE_IndicatorSpinDown:
    // {
    //     mSpinBoxStyle->drawIndicator(pe, option, painter, widget);
    //     break;
    // }

    default:
        QCommonStyle::drawPrimitive(pe, option, painter, widget);

        break;
    }
}
int CustomStyle::pixelMetric(QStyle::PixelMetric pm, const QStyleOption* option, const QWidget* widget) const
{
    switch (pm)
    {
    case PM_IndicatorHeight:  // checkboxes
    case PM_IndicatorWidth:
    {
        // checkboxes
        return mCheckBoxStyle->indicatorSize();
    }

    case PM_ButtonShiftHorizontal:
    case PM_ButtonShiftVertical:
        return 0;  // no shift

        // case (SwitchButtonStyle::PM_SwitchButtonHandleWidth):
        // case (SwitchButtonStyle::PM_SwithcButtonHandleHeight):
        // {
        //     return mSwitchButtonStyle->indicatorSize(pm);
        // }

    default:
        return QCommonStyle::pixelMetric(pm, option, widget);
    }
}
void CustomStyle::drawControl(QStyle::ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    switch (element)
    {
        /* PushButton */
    case CE_PushButton:
    {
        QCommonStyle::drawControl(element, option, painter, widget);
        return;
    }
    case CE_PushButtonBevel:
    {
        // Draw button shape (background and border)
        if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
        {
            mPushButtonStyle->drawButtonShape(optionButton, painter, widget);
        }
        return;
    }
    case CE_PushButtonLabel:
    {
        if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
        {
            QStyleOptionButton copy = *optionButton;
            mPushButtonStyle->adjustTextPalette(&copy);
            QCommonStyle::drawControl(element, &copy, painter, widget);
        }
        return;
    }

        /* RadioButton */
    case CE_RadioButton:
    case CE_RadioButtonLabel:

        /* CheckBox */
    case CE_CheckBox:
    case CE_CheckBoxLabel:
    {
        QCommonStyle::drawControl(element, option, painter, widget);
        return;
    }

        /* ProgressBar */
    case CE_ProgressBar:
    {
        QCommonStyle::drawControl(element, option, painter, widget);
        return;
    }
    case CE_ProgressBarGroove:
    {
        if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
        {
            mProgressbarStyle->drawGroove(progressBarOption, painter, widget);
        }
        break;
    }
    case CE_ProgressBarContents:
    {
        if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
        {
            mProgressbarStyle->drawContents(progressBarOption, painter, widget);
        }
        break;
    }
    case CE_ProgressBarLabel:
    {
        if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
        {
            mProgressbarStyle->drawText(progressBarOption, painter, widget);
        }
        break;
    }
    default:
        QCommonStyle::drawControl(element, option, painter, widget);
    }
}
void CustomStyle::drawComplexControl(ComplexControl complexControl, const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const
{
    switch (complexControl)
    {
    case CC_SpinBox:
    {
        if (const auto* spinBoxOption = qstyleoption_cast<const QStyleOptionSpinBox*>(opt))
        {
            QRect rect = subControlRect(CC_SpinBox, spinBoxOption, SC_SpinBoxFrame, widget);
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing);
            // QPainterPath path;
            // path.addRoundedRect(rect.toRectF().adjusted(0.5, 0.5, -0.5, -0.5), 5, 5);
            // painter->fillPath(path, QColor(172, 195, 166));
            painter->setPen(QColor(172, 195, 166));
            painter->drawRoundedRect(QRectF(rect).adjusted(1, 1, -1, -1), 5, 5);
            painter->restore();
            // mSpinBoxStyle->draw(spinBoxOption, painter, widget);
        }
        break;
    }
    default:
        QCommonStyle::drawComplexControl(complexControl, opt, painter, widget);
    }
}
int CustomStyle::styleHint(StyleHint stylehint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const
{
    switch (stylehint)
    {
    case SH_DialogButtonBox_ButtonsHaveIcons:
        return 0;
    default:
        break;
    }
    return QCommonStyle::styleHint(stylehint, option, widget, returnData);
}
QSize CustomStyle::sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& contentsSize, const QWidget* widget) const
{
    switch (type)
    {
    case CT_PushButton:
        if (const auto* buttonOption = qstyleoption_cast<const QStyleOptionButton*>(option))
        {
            return mPushButtonStyle->sizeFromContents(buttonOption, contentsSize, widget);
        }
        break;
    case CT_RadioButton:
    case CT_CheckBox:
        return QCommonStyle::sizeFromContents(type, option, contentsSize, widget);

    // case CT_LineEdit:
    //     if (const auto* lineEditOption = qstyleoption_cast<const
    //     QStyleOptionFrame*>(option))
    //     {
    //         return mLineEditStyle->sizeFromContents(lineEditOption,
    //         contentsSize, widget);
    //     }
    //     break;
    default:
        break;
    }
    return QCommonStyle::sizeFromContents(type, option, contentsSize, widget);
}
QRect CustomStyle::subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const
{
    switch (subElement)
    {
    case SE_ProgressBarGroove:
    case SE_ProgressBarContents:
    case SE_ProgressBarLabel:
        if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
        {
            return mProgressbarStyle->subElementRect(subElement, progressBarOption, widget);
        }
        break;
    case SE_LineEditContents:
        if (const auto* lineEditOption = qstyleoption_cast<const QStyleOptionFrame*>(option))
        {
            return mLineEditStyle->subElementRect(subElement, lineEditOption, widget);
        }
    default:
        break;
    }
    return QCommonStyle::subElementRect(subElement, option, widget);
}
void CustomStyle::polish(QWidget* w)
{
    if (qobject_cast<QPushButton*>(w) || qobject_cast<QCheckBox*>(w))
    {
        w->setAttribute(Qt::WA_Hover);
    }
    // if (qobject_cast<QScrollBar*>(w))
    // {
    //     w->setAttribute(Qt::WA_Hover, false);
    // }
    // if (const auto scrollBar = qobject_cast<QScrollBar*>(w))
    // {
    //     scrollBar->setAttribute(Qt::WA_OpaquePaintEvent, false);
    // }
    QCommonStyle::polish(w);
}
bool CustomStyle::eventFilter(QObject* obj, QEvent* event)
{
    return QCommonStyle::eventFilter(obj, event);
}

}  // namespace Theme