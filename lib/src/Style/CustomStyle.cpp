#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QStyleOptionProgressBar>
#include "VanillaStyle/Style/CustomStyle.h"
#include "../private/CustomStyle_p.h"

namespace VanillaStyle
{
CustomStyle::CustomStyle()
    : d_ptr(new CustomStylePrivate(this))
{
}

void CustomStyle::drawPrimitive(PrimitiveElement pe, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    Q_D(const CustomStyle);
    switch (pe)
    {
    case PE_FrameLineEdit:
        break;
    case PE_FrameMenu:
        return;
    case PE_FrameButtonBevel:
    {
    }
    case PE_IndicatorCheckBox:
    case PE_IndicatorRadioButton:
    {
        d->m_checkBoxStyle->draw(option, painter, widget);
        return;
    }
    default:
        QCommonStyle::drawPrimitive(pe, option, painter, widget);
        break;
    }
}

void CustomStyle::drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
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
    }
    default:
        QCommonStyle::drawControl(element, option, painter, widget);
    }
}

void CustomStyle::drawComplexControl(ComplexControl complexControl, const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const
{
    switch (complexControl)
    {
    default:
        QCommonStyle::drawComplexControl(complexControl, opt, painter, widget);
    }
}

int CustomStyle::pixelMetric(PixelMetric pm, const QStyleOption* option, const QWidget* widget) const
{
    switch (pm)
    {
    case PM_IndicatorHeight:  // checkboxes
    case PM_IndicatorWidth:
    {
        // checkboxes
        //        return mCheckBoxStyle->indicatorSize();
    }

    case PM_ButtonShiftHorizontal:
    case PM_ButtonShiftVertical:
        return 0;  // no shift

    default:
        return QCommonStyle::pixelMetric(pm, option, widget);
    }
}

QSize CustomStyle::sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& contentsSize, const QWidget* widget) const
{
    switch (type)
    {
    case CT_PushButton:
        //        if (const auto* buttonOption = qstyleoption_cast<const QStyleOptionButton*>(option))
        //        {
        //            return mPushButtonStyle->sizeFromContents(buttonOption, contentsSize, widget);
        //        }
        break;
    case CT_RadioButton:
    case CT_CheckBox:
        return QCommonStyle::sizeFromContents(type, option, contentsSize, widget);

    default:
        break;
    }
    return QCommonStyle::sizeFromContents(type, option, contentsSize, widget);
}
QRect CustomStyle::subElementRect(SubElement subElement, const QStyleOption* option, const QWidget* widget) const
{
    switch (subElement)
    {
    case SE_ProgressBarGroove:
    case SE_ProgressBarContents:
    case SE_ProgressBarLabel:
        if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
        {
            if (subElement == QStyle::SE_ProgressBarLabel)
                return option->rect.adjusted(0, 0, -6, 0);  // right-align before the round rect
            // The area for both groove and content is the whole rect. The drawing will take care of actual contents rect.
            return option->rect;
        }
        break;

    case SE_PushButtonBevel:
    {
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
    // w->setAttribute(Qt::WA_TranslucentBackground);
    QCommonStyle::polish(w);
}
bool CustomStyle::eventFilter(QObject* obj, QEvent* event)
{
    return QCommonStyle::eventFilter(obj, event);
}
int CustomStyle::styleHint(QStyle::StyleHint stylehint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const
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
void CustomStyle::setConfigPath(const std::string& path)
{
    Q_D(CustomStyle);
    d->m_config->setConfigPath(path);
}

CustomStylePrivate::CustomStylePrivate(CustomStyle* q)
    : q_ptr(q)
    , m_config(std::make_shared<Config>())
    , m_checkBoxStyle(std::make_shared<CheckBoxStyle>())
{
    auto error = m_config->readConfig(m_styleConfig);
}
}  // namespace VanillaStyle