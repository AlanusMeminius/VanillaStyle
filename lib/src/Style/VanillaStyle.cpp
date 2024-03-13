#include <QPushButton>
#include <QCheckBox>
#include <QMenu>
#include <QPainterPath>
#include "VanillaStyle/Style/VanillaStyle.h"
#include "VanillaStyle_p.h"
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle
{
VanillaStyle::VanillaStyle()
    : d_ptr(new VanillaStylePrivate(this))
{
    Q_D(VanillaStyle);

}
QPalette VanillaStyle::getStandardPalette() const
{
    Q_D(const VanillaStyle);
    return d->theme->palette;
}

void VanillaStyle::drawPrimitive(PrimitiveElement pe, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    Q_D(const VanillaStyle);
    switch (pe)
    {
    case PE_Frame:
        return;
    case PE_FrameFocusRect:
        return;
    case PE_FrameMenu:
        return;  // Nothing to draw.
    case PE_IndicatorRadioButton:
    {
        d->radioButtonStyle->draw(option, painter, widget, d->theme);
        return;
    }
    case PE_IndicatorCheckBox:
    {
        d->checkBoxStyle->draw(option, painter, widget, d->theme);
        return;
    }
    case PE_PanelMenu:
    {
        d->menuStyle->drawPrimitive(option, painter, d->theme, widget);
        return;
    }
    case PE_PanelLineEdit:
        d->lineEditStyle->draw(option, painter, widget, d->theme);
        return;
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
        d->buttonStyle->draw(option, painter, widget, d->theme);
        return;
    }
    case CE_PushButtonLabel:
    {
        if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
        {
            QStyleOptionButton copy = *optionButton;
            d->theme->adjustTextPalette(&copy);
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
        d->progressBarStyle->drawGroove(option, painter, widget, d->theme);
        return;
    }
    case CE_ProgressBarContents:
    {
        d->progressBarStyle->drawContents(option, painter, widget, d->theme);
        return;
    }
    case CE_ProgressBarLabel:
    {
        d->progressBarStyle->drawText(option, painter, widget, d->theme);
        return;
    }
    case CE_FocusFrame:
        return;
    case CE_MenuItem:
        d->menuStyle->drawMenuItem(option, painter, d->theme, widget);
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
        d->menuStyle->drawMenuBarItem(option, painter, d->theme, widget);
        return;
    case CE_MenuBarEmptyArea:
    {
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
    case CE_CheckBox:
        break;
    case CE_CheckBoxLabel:
        break;
    case CE_RadioButton:
        break;
    case CE_RadioButtonLabel:
        break;
    case CE_TabBarTab:
        break;
    case CE_TabBarTabShape:
        break;
    case CE_TabBarTabLabel:
        break;
    case CE_MenuScroller:
        break;
    case CE_ToolButtonLabel:
        break;
    case CE_Header:
        break;
    case CE_HeaderSection:
        break;
    case CE_HeaderLabel:
        break;
    case CE_ToolBoxTab:
        break;
    case CE_SizeGrip:
        break;
    case CE_Splitter:
        break;
    case CE_RubberBand:
        break;
    case CE_DockWidgetTitle:
        break;
    case CE_ScrollBarAddLine:
        break;
    case CE_ScrollBarSubLine:
        break;
    case CE_ScrollBarAddPage:
        break;
    case CE_ScrollBarSubPage:
        break;
    case CE_ScrollBarSlider:
        break;
    case CE_ScrollBarFirst:
        break;
    case CE_ScrollBarLast:
        break;
    case CE_ComboBoxLabel:
        break;
    case CE_ToolBar:
        break;
    case CE_HeaderEmptyArea:
        break;
    case CE_ItemViewItem:
        break;
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
        d->spinBoxStyle->draw(opt, painter, widget, d->theme);
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
        return d->progressBarStyle->subElementRect(subElement, option, widget);
    }
    case SE_LineEditContents:
    {
        return d->lineEditStyle->subElementRect(subElement, option, widget);
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
        d->menuStyle->eventFilter(menu);
    }
}
bool VanillaStyle::eventFilter(QObject* obj, QEvent* event)
{
    return QCommonStyle::eventFilter(obj, event);
}

void VanillaStyle::setConfigPath(const std::string& path)
{
}
QColor VanillaStyle::getCustomColor(const Theme::ColorRole role)
{
    Q_D(VanillaStyle);
    return d->theme->customColor(role);
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
        return d->spinBoxStyle->subControlRect(control, option, subControl, widget);
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
    : theme(new Theme())
    , checkBoxStyle(new CheckBoxStyle())
    , radioButtonStyle(new RadioButtonStyle())
    , buttonStyle(new ButtonStyle())
    , progressBarStyle(new ProgressBarStyle())
    , menuStyle(new MenuStyle())
    , spinBoxStyle(new SpinBoxStyle())
    , lineEditStyle(new LineEditStyle())
    , comboBoxStyle(new ComboBoxStyle())
    , q_ptr(q)

{

}
}  // namespace VanillaStyle