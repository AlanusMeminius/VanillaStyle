#include <QApplication>
#include <QPainterPath>
#include <QListWidget>
#include <QPushButton>
#include <QFontDatabase>
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QScrollBar>
#include <QMenu>
#include <QUrl>

#include "VanillaStyle/Style/VanillaStyle.h"
#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle_p.h"
#include "VanillaStyle/Helper/ScrollBarStyle.h"

namespace Vanilla
{
VanillaStyle::VanillaStyle()
    : d_ptr(new VanillaStylePrivate(this))
{
    Q_D(VanillaStyle);
    d->init();
}

VanillaStyle::VanillaStyle(const Mode mode)
    : d_ptr(new VanillaStylePrivate(this, mode))
{
    Q_D(VanillaStyle);
    d->init();
}

VanillaStyle::~VanillaStyle()
{
    delete d_ptr;
}

void VanillaStyle::drawPrimitive(PrimitiveElement pe, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    Q_D(const VanillaStyle);

    ControlHelper helper{nullptr};

    switch (pe)
    {
    case PE_Frame:
    case PE_Widget:
    case PE_FrameWindow:
    case PE_PanelScrollAreaCorner:
    case PE_FrameFocusRect:
    case PE_FrameMenu:
    case PE_FrameLineEdit:
    case PE_IndicatorColumnViewArrow:
    case PE_IndicatorItemViewItemDrop:
        helper = createHelper(d->helper, &Helper::emptyControl);
        break;
    case PE_IndicatorRadioButton:
        helper = createHelper(d->radioButtonStyle, &RadioButtonStyle::draw);
        break;
    case PE_IndicatorCheckBox:
        helper = createHelper(d->checkBoxStyle, &CheckBoxStyle::draw);
        break;
    case PE_PanelMenu:
        helper = createHelper(d->menuStyle, &MenuStyle::drawPrimitive);
        break;
    case PE_PanelLineEdit:
        helper = createHelper(d->lineEditStyle, &LineEditStyle::draw);
        break;
    default:
        break;
    }

    painter->save();
    if (!(helper && helper(option, painter, d->theme, widget)))
    {
        QCommonStyle::drawPrimitive(pe, option, painter, widget);
    }
    painter->restore();
}

void VanillaStyle::drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    Q_D(const VanillaStyle);

    ControlHelper helper{nullptr};

    switch (element)
    {
    case CE_ShapedFrame:
        helper = createHelper(d->helper, &Helper::shapedFrame);
        break;
    case CE_PushButtonBevel:
        helper = createHelper(d->buttonStyle, &ButtonStyle::drawPushButtonBevel);
        break;
    case CE_ProgressBarGroove:
        helper = createHelper(d->progressBarStyle, &ProgressBarStyle::drawGroove);
        break;
    case CE_ProgressBarContents:
        helper = createHelper(d->progressBarStyle, &ProgressBarStyle::drawContents);
        break;
    case CE_ProgressBarLabel:
        helper = createHelper(d->progressBarStyle, &ProgressBarStyle::drawLabel);
        break;
    case CE_ItemViewItem:
        helper = createHelper(d->itemViewStyle, &ItemViewStyle::draw);
        break;
    case CE_MenuItem:
        helper = createHelper(d->menuStyle, &MenuStyle::drawMenuItem);
        break;
    case CE_PushButtonLabel:
        helper = createHelper(d->helper, &Helper::drawAlignCenterLabel);
        break;
    case CE_CheckBoxLabel:
    case CE_RadioButtonLabel:
        helper = createHelper(d->helper, &Helper::drawAlignLeftLabel);
        break;
    case CE_ScrollBarSlider:
        helper = createHelper(d->scrollBarStyle, &ScrollBarStyle::drawSlider);
        break;
    case CE_ScrollBarAddLine:
        helper = createHelper(d->scrollBarStyle, &ScrollBarStyle::drawAddLine);
        break;
    case CE_ScrollBarSubLine:
        helper = createHelper(d->scrollBarStyle, &ScrollBarStyle::drawSubLine);
        break;
    case CE_ScrollBarAddPage:
    case CE_ScrollBarSubPage:
        helper = createHelper(d->helper, &Helper::emptyControl);
        break;
    default:
        break;
    }

    painter->save();
    if (!(helper && helper(option, painter, d->theme, widget)))
    {
        QCommonStyle::drawControl(element, option, painter, widget);
    }
    painter->restore();
}

void VanillaStyle::drawComplexControl(ComplexControl complexControl, const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const
{
    Q_D(const VanillaStyle);

    ComplexHelper helper{nullptr};

    switch (complexControl)
    {
    case CC_SpinBox:
        helper = createHelper(d->spinBoxStyle, &SpinBoxStyle::draw);
        break;
    case CC_ComboBox:
        helper = createHelper(d->comboBoxStyle, &ComboBoxStyle::draw);
        break;
    default:
        break;
    }

    painter->save();
    if (!(helper && helper(opt, painter, d->theme, widget)))
    {
        QCommonStyle::drawComplexControl(complexControl, opt, painter, widget);
    }
    painter->restore();
}

int VanillaStyle::pixelMetric(PixelMetric pm, const QStyleOption* option, const QWidget* widget) const
{
    Q_D(const VanillaStyle);
    switch (pm)
    {
    case PM_IndicatorWidth:
    case PM_ExclusiveIndicatorWidth:
    case PM_IndicatorHeight:
    case PM_ExclusiveIndicatorHeight:
        return d->theme->getSize(Theme::IconSize);
    case PM_RadioButtonLabelSpacing:
    case PM_CheckBoxLabelSpacing:
        return d->theme->getSize(Theme::CheckBoxSpacing);
    default:
        break;
    }
    return QCommonStyle::pixelMetric(pm, option, widget);
}

int VanillaStyle::styleHint(StyleHint stylehint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const
{
    return QCommonStyle::styleHint(stylehint, option, widget, returnData);
}

QSize VanillaStyle::sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& contentsSize, const QWidget* widget) const
{
    switch (type)
    {
    case CT_MenuBar:
        return contentsSize;
    case CT_ItemViewItem:
        if (const auto* opt = qstyleoption_cast<const QStyleOptionViewItem*>(option))
        {
            const auto textH = opt->fontMetrics.height();
            return {contentsSize.width(), textH + 16};
        }
    default:
        break;
    }
    return QCommonStyle::sizeFromContents(type, option, contentsSize, widget);
}

QRect VanillaStyle::subElementRect(SubElement subElement, const QStyleOption* option, const QWidget* widget) const
{
    Q_D(const VanillaStyle);

    SubElementHelper helper{nullptr};

    switch (subElement)
    {
    case SE_ProgressBarGroove:
    case SE_ProgressBarContents:
    case SE_ProgressBarLabel:
        helper = createHelper(d->progressBarStyle, &ProgressBarStyle::subElementRect);
        break;
    case SE_LineEditContents:
        helper = createHelper(d->lineEditStyle, &LineEditStyle::subElementRect);
        break;
    case SE_RadioButtonContents:
    case SE_RadioButtonIndicator:
        helper = createHelper(d->radioButtonStyle, &RadioButtonStyle::subElementRect);
        break;
    default:
        break;
    }
    if (helper)
    {
        return helper(subElement, option, d->theme, widget);
    }
    return QCommonStyle::subElementRect(subElement, option, widget);
}

QRect VanillaStyle::subControlRect(ComplexControl control, const QStyleOptionComplex* option, SubControl subControl, const QWidget* widget) const
{
    Q_D(const VanillaStyle);
    SubControlHelper helper{nullptr};

    switch (control)
    {
    case CC_SpinBox:
    {
        helper = createHelper(d->spinBoxStyle, &SpinBoxStyle::subControlRect);
        break;
    }
    case CC_ComboBox:
        helper = createHelper(d->comboBoxStyle, &ComboBoxStyle::subControlRect);
        break;
    default:
        break;
    }
    if (helper)
    {
        return helper(control, option, subControl, d->theme, widget);
    }

    return QCommonStyle::subControlRect(control, option, subControl, widget);
}

void VanillaStyle::polish(QWidget* w)
{
    Q_D(VanillaStyle);

    QCommonStyle::polish(w);
    if (qobject_cast<QPushButton*>(w) || qobject_cast<QCheckBox*>(w) || qobject_cast<QRadioButton*>(w))
    {
        w->setAttribute(Qt::WA_Hover);
    }
    if (auto* itemView = qobject_cast<QAbstractItemView*>(w))
    {
        itemView->setAutoFillBackground(false);
        itemView->setBackgroundRole(QPalette::NoRole);
        itemView->viewport()->setBackgroundRole(QPalette::NoRole);
        itemView->viewport()->setAutoFillBackground(false);
        itemView->viewport()->setAttribute(Qt::WA_Hover);
    }
    if (const auto* combox = qobject_cast<QComboBox*>(w))
    {
        if (const auto container = qobject_cast<QWidget*>(combox->children().back()))
        {
            container->setBackgroundRole(QPalette::NoRole);
            container->setWindowFlag(Qt::FramelessWindowHint, true);
            container->setWindowFlag(Qt::NoDropShadowWindowHint, true);
            container->setAttribute(Qt::WA_OpaquePaintEvent, false);
            container->setProperty("_q_windowsDropShadow", false);
        }
    }
    if (qobject_cast<QScrollBar*>(w))
    {
        w->setAttribute(Qt::WA_OpaquePaintEvent, false);
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

void VanillaStyle::setConfigPath(const QString& path)
{
    Q_D(VanillaStyle);
    d->theme->setConfig(path);
    if (const QUrl filePath(path); !filePath.isRelative())
    {
        d->configNotifier(path);
    }
    d->updatePalette();
}

void VanillaStyle::setMode(Mode mode)
{
    Q_D(VanillaStyle);
    d->theme->setMode(mode);
    d->updatePalette();
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
    , scrollBarStyle(new ScrollBarStyle())
    , q_ptr(q)
{
}

VanillaStylePrivate::VanillaStylePrivate(VanillaStyle* q, const Mode mode)
    : VanillaStylePrivate(q)
{
    theme->setMode(mode);
    init();
}

void VanillaStylePrivate::init() const
{
    updatePalette();
    updateFont();
}

void VanillaStylePrivate::updatePalette() const
{
    // set up palette
    const auto palette = theme->standardPalette();
    QApplication::setPalette(palette);
}

void VanillaStylePrivate::updateFont() const
{
    // set up font
    const auto font = theme->getFont(Theme::TextSizeRole::Default);
    QApplication::setFont(font);
}

void VanillaStylePrivate::configNotifier(const QString& configPath)
{
    Q_Q(VanillaStyle);
    if (theme->isEnableHotReload())
    {
        configChangeNotifier = std::make_unique<ConfigChangeNotifier>(q, configPath);
    }
    else
    {
        configChangeNotifier.reset();
    }
}
}  // namespace Vanilla