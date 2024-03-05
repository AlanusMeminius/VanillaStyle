#include <QPushButton>
#include <QCheckBox>
#include <QMenu>
#include <QPainter>
#include <QPainterPath>
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
    case PE_Frame:
        return;
    case PE_FrameDefaultButton:
        break;
    case PE_FrameDockWidget:
        break;
    case PE_FrameFocusRect:
        break;
    case PE_FrameGroupBox:
        break;
    case PE_FrameLineEdit:
        break;
    case PE_FrameMenu:
        return;  // Nothing to draw.
    case PE_FrameStatusBarItem:
        break;
    case PE_FrameTabWidget:
        break;
    case PE_FrameWindow:
        break;
    case PE_Widget:
        break;
    case PE_PanelMenuBar:
        break;
    case PE_IndicatorColumnViewArrow:
        break;
    case PE_IndicatorItemViewItemDrop:
        break;
    case PE_IndicatorRadioButton:
    {
        d->m_radioButtonStyle->draw(option, painter, widget, d->m_theme);
        return;
    }
    case PE_IndicatorCheckBox:
    {
        d->m_checkBoxStyle->draw(option, painter, widget, d->m_theme);
        return;
    }
    case PE_PanelMenu:
    {
        d->m_menuStyle->drawPrimitive(option, painter, d->m_theme, widget);
        return;
    }
    default:
        break;
    }
    QCommonStyle::drawPrimitive(pe, option, painter, widget);
}

void VanillaStyle::drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    Q_D(const VanillaStyle);

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
        d->m_buttonStyle->draw(option, painter, widget, d->m_theme);
        return;
    }
    case CE_PushButtonLabel:
    {
        if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
        {
            QStyleOptionButton copy = *optionButton;
            //            mPushButtonStyle->adjustTextPalette(&copy);
            QCommonStyle::drawControl(element, &copy, painter, widget);
        }
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
        d->m_progressBarStyle->drawGroove(option, painter, widget, d->m_theme);
        return;
    }
    case CE_ProgressBarContents:
    {
        d->m_progressBarStyle->drawContents(option, painter, widget);
        return;
    }
    case CE_ProgressBarLabel:
    {
        d->m_progressBarStyle->drawText(option, painter, widget);
        return;
    }
    case CE_FocusFrame:
        return;
    case CE_MenuItem:
        d->m_menuStyle->drawMenuItem(option, painter, d->m_theme, widget);
        return;
    case CE_MenuVMargin:
        // Nothing to draw.
        return;
    case CE_MenuHMargin:
        // Nothing to draw.
        return;
    case CE_MenuEmptyArea:
        // Nothing to draw.
        return;
    case CE_MenuTearoff:
        return;
    case CE_MenuBarItem:
        d->m_menuStyle->drawMenuBarItem(option, painter, d->m_theme, widget);
        return;
    case CE_MenuBarEmptyArea:
    {
        //        painter->fillRect(option->rect, QColor(255, 255, 255));
        return;
    }
    case CE_ToolBoxTabShape:
        break;
    case CE_ToolBoxTabLabel:
        break;
    case CE_ColumnViewGrip:
        break;
    case CE_ShapedFrame:
        return;
    default:
        break;
    }
    QCommonStyle::drawControl(element, option, painter, widget);
}

void VanillaStyle::drawComplexControl(ComplexControl complexControl, const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const
{
    Q_D(const VanillaStyle);

    switch (complexControl)
    {
    case CC_SpinBox:
    {
        d->m_spinBoxStyle->draw(opt, painter, widget, d->m_theme);
        return;
    }
    default:
        break;
    }
    QCommonStyle::drawComplexControl(complexControl, opt, painter, widget);
}

int VanillaStyle::pixelMetric(PixelMetric pm, const QStyleOption* option, const QWidget* widget) const
{
    return QCommonStyle::pixelMetric(pm, option, widget);
}

QSize VanillaStyle::sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& contentsSize, const QWidget* widget) const
{
    switch (type)
    {
    case CT_MenuBar:
        return contentsSize;
    default:
        break;
    }
    return QCommonStyle::sizeFromContents(type, option, contentsSize, widget);
}
QRect VanillaStyle::subElementRect(SubElement subElement, const QStyleOption* option, const QWidget* widget) const
{
    Q_D(const VanillaStyle);
    switch (subElement)
    {
    case SE_ProgressBarGroove:
    case SE_ProgressBarContents:
    case SE_ProgressBarLabel:
    {
        return d->m_progressBarStyle->subElementRect(subElement, option, widget);
    }
    default:
        break;
    }
    return QCommonStyle::subElementRect(subElement, option, widget);
}
void VanillaStyle::polish(QWidget* w)
{
    Q_D(VanillaStyle);

    QCommonStyle::polish(w);
    if (qobject_cast<QPushButton*>(w) || qobject_cast<QCheckBox*>(w))
    {
        w->setAttribute(Qt::WA_Hover);
    }

    if (auto* menu = qobject_cast<QMenu*>(w))
    {
        d->m_menuStyle->eventFilter(menu);
    }
}
bool VanillaStyle::eventFilter(QObject* obj, QEvent* event)
{
    return QCommonStyle::eventFilter(obj, event);
}

void VanillaStyle::setConfigPath(const std::string& path)
{
}
int VanillaStyle::styleHint(QStyle::StyleHint stylehint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const
{
    switch (stylehint)
    {
        // Menu
    case SH_Menu_AllowActiveAndDisabled:
        return false;
    case SH_Menu_SpaceActivatesItem:
        return true;
    case SH_Menu_SubMenuPopupDelay:
        return 300;
    case SH_Menu_MouseTracking:
        return true;
    case SH_Menu_Scrollable:
        return true;
    case SH_Menu_SloppySubMenus:
        break;
    case SH_Menu_FillScreenWithScroll:
        return true;
    case SH_Menu_KeyboardSearch:
        return true;
    case SH_Menu_SelectionWrap:
        return true;
    case SH_Menu_Mask:
        break;
    case SH_Menu_FlashTriggeredItem:
        return true;
    case SH_Menu_FadeOutOnHide:
        return true;
    case SH_Menu_SupportsSections:
        return false;
    case SH_Menu_SubMenuUniDirection:
        break;
    case SH_Menu_SubMenuUniDirectionFailCount:
        break;
    case SH_Menu_SubMenuSloppySelectOtherActions:
        break;
    case SH_Menu_SubMenuSloppyCloseTimeout:
        break;
    case SH_Menu_SubMenuResetWhenReenteringParent:
        break;
    case SH_Menu_SubMenuDontStartSloppyOnLeave:
        break;
    case SH_UnderlineShortcut:
        break;
    default:
        break;
    }
    return QCommonStyle::styleHint(stylehint, option, widget, returnData);
}
QRect VanillaStyle::subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex* option, QStyle::SubControl subControl,
                                   const QWidget* widget) const
{
    Q_D(const VanillaStyle);

    switch (control)
    {
    case CC_SpinBox:
    {
        return d->m_spinBoxStyle->subControlRect(control, option, subControl, widget);
    }
    case CC_ComboBox:
        break;
    case CC_ScrollBar:
        break;
    case CC_Slider:
        break;
    case CC_ToolButton:
        break;
    case CC_TitleBar:
        break;
    case CC_Dial:
        break;
    case CC_GroupBox:
        break;
    case CC_MdiControls:
        break;
    case CC_CustomBase:
        break;
    }
    return QCommonStyle::subControlRect(control, option, subControl, widget);
}

VanillaStylePrivate::VanillaStylePrivate(VanillaStyle* q)
    : q_ptr(q)
    , m_theme(new Theme())
    , m_checkBoxStyle(new CheckBoxStyle())
    , m_radioButtonStyle(new RadioButtonStyle())
    , m_buttonStyle(new ButtonStyle())
    , m_progressBarStyle(new ProgressBarStyle())
    , m_menuStyle(new MenuStyle())
    , m_spinBoxStyle(new SpinBoxStyle())
{
}
}  // namespace VanillaStyle