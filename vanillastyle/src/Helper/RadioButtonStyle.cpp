#include <QPainter>

#include "VanillaStyle/Helper/RadioButtonStyle.h"

#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Theme/Theme.h"

bool Vanilla::RadioButtonStyle::draw(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionButton*>(option);
    if (!opt)
    {
        return true;
    }
    painter->setRenderHints(QPainter::Antialiasing);

    const auto rect = QRectF(opt->rect);
    const auto border = theme->getSize(SizeRole::CheckBoxBorder);
    const auto halfBorder = border / 2.;
    const auto margins = QMarginsF(halfBorder, halfBorder, halfBorder, halfBorder);
    const auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

    // btn background
    const auto bgColor = theme->getColor(option, ColorRole::RadioButtonBackground);
    Helper::renderEllipse(painter, buttonRect, bgColor);

    // btn border
    if (border > 0.1)
    {
        const auto borderColor = theme->getColor(option, ColorRole::CheckBoxBorderColor);
        Helper::renderEllipseBorder(painter, buttonRect, borderColor, border);
    }

    if ((theme->flags(option) & Theme::Checked) == Theme::Checked)
    {
        auto margin = theme->getSize(SizeRole::CheckBoxIndicatorMargin);
        const auto indicatorColor = theme->getColor(option, ColorRole::IndicatorColor);
        Helper::renderEllipse(painter, rect.adjusted(margin, margin, -margin, -margin), indicatorColor);
    }
    return true;
}

QRect Vanilla::RadioButtonStyle::subElementRect(QStyle::SubElement element, const QStyleOption* option, const std::shared_ptr<Theme>& theme,
                                                const QWidget* widget) const
{
    Q_UNUSED(widget);
    if (element == QStyle::SE_RadioButtonIndicator)
    {
        const auto indicatorSize = theme->getSize(SizeRole::IconSize);
        const auto indicatorY = option->rect.y() + (option->rect.height() - indicatorSize) / 2;
        return QRect{option->rect.x(), indicatorY, indicatorSize, indicatorSize};
    }
    // SE_RadioButtonContents
    const auto indicatorSize = theme->getSize(SizeRole::IconSize);
    const auto border = theme->getSize(SizeRole::CheckBoxSpacing);
    return option->rect.marginsRemoved({indicatorSize + border, 0, 0, 0});
}
