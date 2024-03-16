#include <QPushButton>
#include <QCheckBox>
#include <QMenu>
#include <QListWidget>
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
    d->theme->initPalette();
    return d->theme->palette;
}

void VanillaStyle::drawPrimitive(PrimitiveElement pe, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    Q_D(const VanillaStyle);
    std::pair<std::shared_ptr<Helper>, ControlHelper> fcn = std::make_pair(nullptr, nullptr);

    switch (pe)
    {
    case PE_Widget:
    case PE_Frame:
    case PE_FrameWindow:
    case PE_PanelScrollAreaCorner:
    case PE_FrameFocusRect:
    case PE_FrameMenu:
    case PE_IndicatorColumnViewArrow:
    case PE_IndicatorItemViewItemDrop:
        fcn = StyleHelper<ControlHelper>(d->helper, &Helper::emptyControl);
        break;
    case PE_IndicatorRadioButton:
        fcn = StyleHelper<ControlHelper>(d->radioButtonStyle, &RadioButtonStyle::drawIndicator);
        break;
    case PE_IndicatorCheckBox:
        fcn = StyleHelper<ControlHelper>(d->checkBoxStyle, &CheckBoxStyle::draw);
        break;
    case PE_PanelMenu:
        fcn = StyleHelper<ControlHelper>(d->menuStyle, &MenuStyle::drawPrimitive);
        break;
    case PE_PanelLineEdit:
        fcn = StyleHelper<ControlHelper>(d->lineEditStyle, &LineEditStyle::draw);
        break;
    default:
        break;
    }
    painter->save();
    if (check(fcn, option, painter, d->theme, widget))
    {
        QCommonStyle::drawPrimitive(pe, option, painter, widget);
    }
    painter->restore();
}

void VanillaStyle::drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    Q_D(const VanillaStyle);

    std::pair<std::shared_ptr<Helper>, ControlHelper> fcn = std::make_pair(nullptr, nullptr);
    switch (element)
    {
    case CE_PushButtonBevel:
        fcn = StyleHelper<ControlHelper>(d->buttonStyle, &ButtonStyle::drawPushButtonBevel);
        break;
    case CE_ProgressBarGroove:
        fcn = StyleHelper<ControlHelper>(d->progressBarStyle, &ProgressBarStyle::drawGroove);
        break;
    case CE_ProgressBarContents:
        fcn = StyleHelper<ControlHelper>(d->progressBarStyle, &ProgressBarStyle::drawContents);
        break;
    case CE_ProgressBarLabel:
        fcn = StyleHelper<ControlHelper>(d->progressBarStyle, &ProgressBarStyle::drawLabel);
        break;
    case CE_ItemViewItem:
        fcn = StyleHelper<ControlHelper>(d->itemViewStyle, &ItemViewStyle::draw);
        break;
    default:
        break;
    }
    painter->save();
    if (check(fcn, option, painter, d->theme, widget))
    {
        QCommonStyle::drawControl(element, option, painter, widget);
    }
    painter->restore();
}

void VanillaStyle::drawComplexControl(ComplexControl complexControl, const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const
{
    Q_D(const VanillaStyle);
    std::pair<std::shared_ptr<Helper>, ComplexHelper> fcn = std::make_pair(nullptr, nullptr);
    switch (complexControl)
    {
    case CC_SpinBox:
        fcn = StyleHelper<ComplexHelper>(d->spinBoxStyle, &SpinBoxStyle::draw);
        break;
    case CC_ComboBox:
        fcn = StyleHelper<ComplexHelper>(d->comboBoxStyle, &ComboBoxStyle::draw);
        break;
    default:
        break;
    }
    painter->save();
    if (check(fcn, opt, painter, d->theme, widget))
    {
        QCommonStyle::drawComplexControl(complexControl, opt, painter, widget);
    }
    painter->restore();
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
    std::pair<std::shared_ptr<Helper>, SubElementHelper> fcn = std::make_pair(nullptr, nullptr);
    switch (subElement)
    {
    case SE_ProgressBarGroove:
    case SE_ProgressBarContents:
    case SE_ProgressBarLabel:
        fcn = StyleHelper<SubElementHelper>(d->progressBarStyle, &ProgressBarStyle::subElementRect);
        break;
    case SE_LineEditContents:
        fcn = StyleHelper<SubElementHelper>(d->lineEditStyle, &LineEditStyle::subElementRect);
        break;
    default:
        break;
    }
    if (fcn.second)
    {
        return call(fcn, subElement, option, widget);
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
    if (auto* itemView =  qobject_cast<QAbstractItemView*>(w))
    {
        itemView->setBackgroundRole(QPalette::NoRole);
        itemView->viewport()->setBackgroundRole(QPalette::NoRole);
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
    Q_D(VanillaStyle);
    d->theme->setConfig(path);

    d->theme->initPalette();
    const auto palette = d->theme->standardPalette();
    QApplication::setPalette(palette);
    // const auto topLevelWidgets = QApplication::topLevelWidgets();
    // for (auto* widget : topLevelWidgets) {
    //     widget->update();
    // }
}
QColor VanillaStyle::getCustomColor(const Theme::ColorRole role)
{
    Q_D(VanillaStyle);
    return d->theme->customColor(role);
}
QFont VanillaStyle::getCustomFont(Theme::TextSizeRole sizeRole)
{
    Q_D(VanillaStyle);
    return d->theme->getFont(sizeRole);
}

int VanillaStyle::styleHint(StyleHint stylehint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const
{
    return QCommonStyle::styleHint(stylehint, option, widget, returnData);
}

QRect VanillaStyle::subControlRect(ComplexControl control, const QStyleOptionComplex* option, SubControl subControl, const QWidget* widget) const
{
    Q_D(const VanillaStyle);
    std::pair<std::shared_ptr<Helper>, subControlHelper> fcn = std::make_pair(nullptr, nullptr);
    switch (control)
    {
    case CC_SpinBox:
    {
        fcn = StyleHelper<subControlHelper>(d->spinBoxStyle, &SpinBoxStyle::subControlRect);
        break;
    }
    default:
        break;
    }
    if (fcn.second)
    {
        return call(fcn, control, option, subControl, widget);
    }
    return QCommonStyle::subControlRect(control, option, subControl, widget);
}

VanillaStylePrivate::VanillaStylePrivate(VanillaStyle* q)
    : theme(new Theme())
    , helper(new Helper())
    , checkBoxStyle(new CheckBoxStyle())
    , radioButtonStyle(new RadioButtonStyle())
    , buttonStyle(new ButtonStyle())
    , progressBarStyle(new ProgressBarStyle())
    , menuStyle(new MenuStyle())
    , spinBoxStyle(new SpinBoxStyle())
    , lineEditStyle(new LineEditStyle())
    , comboBoxStyle(new ComboBoxStyle())
    , itemViewStyle(new ItemViewStyle())
    , q_ptr(q)

{
}
}  // namespace VanillaStyle