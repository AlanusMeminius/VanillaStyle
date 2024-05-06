#include <QPainter>

#include "VanillaStyle/Helper/ComboBoxStyle.h"
#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Helper/Common.h"
#include "VanillaStyle/Theme/Theme.h"

namespace Vanilla
{
bool ComboBoxStyle::draw(const QStyleOptionComplex* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionComboBox*>(option);
    if (!opt)
    {
        return true;
    }
    if (opt->editable)
    {
        painter->setRenderHints(QPainter::Antialiasing);
        const auto rect = opt->rect;
        Helper::renderRoundRect(painter, rect, theme->getColor(opt, Theme::ColorRole::LineEditOutline), 5);
        drawIndicator(opt, painter, theme, widget);
        return true;
    }
    else
    {
        painter->setRenderHints(QPainter::Antialiasing);
        const auto rect = opt->rect.adjusted(1, 1, -1, -1);
        const auto fgColor = theme->getColor(opt, Theme::ColorRole::LineEditOutline);
        Helper::renderRoundBorder(painter, rect, fgColor, 1, 5);
        drawIndicator(opt, painter, theme, widget);
        return true;
    }
    return true;
}

bool ComboBoxStyle::drawIndicator(const QStyleOptionComplex* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto indicatorRect = subControlRect(QStyle::CC_ComboBox, option, QStyle::SC_ComboBoxArrow, theme, widget);
    if (indicatorRect.isValid())
    {
        const auto iconPath = theme->getIconPath(Theme::IconRole::DownArrow);
        const auto iconSize = theme->getSize(Theme::IconSize);
        auto iconRect = QRectF(0, 0, iconSize, iconSize);
        iconRect.moveCenter(indicatorRect.center());
        const auto svg = theme->getCachedIcon(iconPath, theme->getColor(option, Theme::ColorRole::IndicatorColor));
        renderSvgFromString(svg, painter, iconRect);
    }
    return true;
}

QRect ComboBoxStyle::subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex* option, QStyle::SubControl subControl,
                                    const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    if (control == QStyle::CC_ComboBox)
    {
        const auto* opt = qstyleoption_cast<const QStyleOptionComboBox*>(option);
        if (!opt)
        {
            return {};
        }
        const auto iconSize = theme->getSize(Theme::IconSize);
        const auto padding = theme->getSize(Theme::NormalPadding);
        switch (subControl)
        {
        case QStyle::SC_ComboBoxArrow:
        {
            return QRect{opt->rect.right() - iconSize, opt->rect.top(), iconSize, opt->rect.height()};
        }
        case QStyle::SC_ComboBoxEditField:
            return opt->rect.adjusted(padding, 0, -iconSize, 0);
        case QStyle::SC_ComboBoxFrame:
        case QStyle::SC_ComboBoxListBoxPopup:
            return opt->rect;
        default:
            break;
        }
        return {};
    }
    return {};
}

void ComboBoxStyle::eventFilter(QComboBox* obj) const
{
}
}  // namespace Vanilla