#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include "VanillaStyle/Style/VanillaStyle.h"
#include "VanillaStyle_p.h"
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle
{
VanillaStyle::VanillaStyle()
    : d_ptr(new VanillaStylePrivate(this))
{
}

void VanillaStyle::drawPrimitive(PrimitiveElement pe, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    Q_D(const VanillaStyle);
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

void VanillaStyle::drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
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

void VanillaStyle::drawComplexControl(ComplexControl complexControl, const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const
{
    switch (complexControl)
    {
    default:
        QCommonStyle::drawComplexControl(complexControl, opt, painter, widget);
    }
}

int VanillaStyle::pixelMetric(PixelMetric pm, const QStyleOption* option, const QWidget* widget) const
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

QSize VanillaStyle::sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& contentsSize, const QWidget* widget) const
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
QRect VanillaStyle::subElementRect(SubElement subElement, const QStyleOption* option, const QWidget* widget) const
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
void VanillaStyle::polish(QWidget* w)
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
bool VanillaStyle::eventFilter(QObject* obj, QEvent* event)
{
    return QCommonStyle::eventFilter(obj, event);
}
void VanillaStyle::polish(QPalette& palette)
{
    QCommonStyle::polish(palette);
}
void VanillaStyle::polish(QApplication* app)
{
    QCommonStyle::polish(app);
}
void VanillaStyle::unpolish(QWidget* w)
{
    QCommonStyle::unpolish(w);
}
void VanillaStyle::unpolish(QApplication* app)
{
    QCommonStyle::unpolish(app);
}
QIcon VanillaStyle::standardIcon(StandardPixmap standardIcon, const QStyleOption* opt, const QWidget* widget) const
{
    return QCommonStyle::standardIcon(standardIcon, opt, widget);
}
QPixmap VanillaStyle::standardPixmap(StandardPixmap sp, const QStyleOption* opt, const QWidget* widget) const
{
    return QCommonStyle::standardPixmap(sp, opt, widget);
}
QPixmap VanillaStyle::generatedIconPixmap(QIcon::Mode iconMode, const QPixmap& pixmap, const QStyleOption* opt) const
{
    return QCommonStyle::generatedIconPixmap(iconMode, pixmap, opt);
}
int VanillaStyle::layoutSpacing(QSizePolicy::ControlType control1, QSizePolicy::ControlType control2, Qt::Orientation orientation, const QStyleOption* option,
                               const QWidget* widget) const
{
    return QCommonStyle::layoutSpacing(control1, control2, orientation, option, widget);
}
QStyle::SubControl VanillaStyle::hitTestComplexControl(ComplexControl cc, const QStyleOptionComplex* opt, const QPoint& pt, const QWidget* w) const
{
    return QCommonStyle::hitTestComplexControl(cc, opt, pt, w);
}
int VanillaStyle::styleHint(QStyle::StyleHint stylehint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const
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
void VanillaStyle::setConfigPath(const std::string& path)
{
    Q_D(VanillaStyle);
    d->m_theme->setConfig(path);
}

VanillaStylePrivate::VanillaStylePrivate(VanillaStyle* q)
    : q_ptr(q)
    , m_theme(std::make_shared<Theme>())
    , m_checkBoxStyle(std::make_shared<CheckBoxStyle>())
{
//    auto error = m_config->readConfig(m_styleConfig);
}
}  // namespace VanillaStyle