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
    , mComboBoxStyle(new ComboBoxStyle)
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
        break;
    case PE_PanelLineEdit:
    {
        if (const auto* panel = qstyleoption_cast<const QStyleOptionFrame*>(option))
        {
            mLineEditStyle->drawPanel(panel, painter, widget);
        }
        break;
    }
    case PE_PanelItemViewItem:
    {
        painter->save();

        QPoint topLeft = option->rect.topLeft();
        QPoint bottomRight = option->rect.topRight();
        QLinearGradient backgroundGradient(topLeft, bottomRight);
        backgroundGradient.setColorAt(0.0, QColor(Qt::yellow).lighter(190));
        backgroundGradient.setColorAt(1.0, Qt::white);
        painter->fillRect(option->rect, QBrush(backgroundGradient));

        painter->restore();
    }
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
        if (const auto* sb = qstyleoption_cast<const QStyleOptionSpinBox*>(opt))
        {
            QStyleOptionSpinBox copy = *sb;
            copy.rect = subControlRect(CC_SpinBox, sb, SC_SpinBoxFrame, widget);
            mSpinBoxStyle->draw(&copy, painter, widget);
            copy.rect = subControlRect(CC_SpinBox, sb, SC_SpinBoxDown, widget);
            mSpinBoxStyle->drawIndicator(PE_IndicatorSpinDown, &copy, painter, widget);
            copy.rect = subControlRect(CC_SpinBox, sb, SC_SpinBoxUp, widget);
            mSpinBoxStyle->drawIndicator(PE_IndicatorSpinUp, &copy, painter, widget);
        }
        break;
    }
    case CC_ComboBox:
    {
        if (const auto* cb = qstyleoption_cast<const QStyleOptionComboBox*>(opt))
        {
            QStyleOptionComboBox copy = *cb;
            copy.rect = subControlRect(CC_ComboBox, cb, SC_ComboBoxFrame, widget);
            mSpinBoxStyle->draw(&copy, painter, widget);
            copy.rect = subControlRect(CC_ComboBox, cb, SC_ComboBoxArrow, widget);
            mCheckBoxStyle->drawIndicator(&copy, painter);
        }
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
    w->setAttribute(Qt::WA_TranslucentBackground);
    QCommonStyle::polish(w);
}
bool CustomStyle::eventFilter(QObject* obj, QEvent* event)
{
    return QCommonStyle::eventFilter(obj, event);
}

}  // namespace Theme