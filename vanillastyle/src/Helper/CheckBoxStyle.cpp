#include <QPainter>
#include <QPainterPath>

#include "VanillaStyle/Helper/CheckBoxStyle.h"

#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace Vanilla
{
bool CheckBoxStyle::draw(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionButton*>(option);
    if (!opt)
    {
        return true;
    }

    painter->setRenderHints(QPainter::Antialiasing);
    const auto rect = QRectF(opt->rect);
    const auto bgColor = theme->getColor(option, ColorRole::CheckBoxBackground);
    const auto borderColor = theme->getColor(option, ColorRole::CheckBoxBorderColor);
    const auto border = theme->getSize(SizeRole::CheckBoxBorder);
    const auto halfBorder = border / 2.;
    const auto margins = QMarginsF(halfBorder, halfBorder, halfBorder, halfBorder);
    const auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

    const auto radius = theme->getSize(SizeRole::ButtonRadius);
    Helper::renderRoundRect(painter, buttonRect, bgColor, radius);

    if (border > 0.1)
    {
        Helper::renderRoundBorder(painter, buttonRect, borderColor, border, radius);
    }

    if ((theme->flags(option) & Theme::Checked) == Theme::Checked)
    {
        drawIndicator(option, rect, painter, theme);
    }

    return true;
}

void CheckBoxStyle::drawIndicator(const QStyleOption* option, const QRectF rect, QPainter* painter, const std::shared_ptr<Theme>& theme) const
{
    const auto indicatorColor = theme->getColor(option, ColorRole::IndicatorColor);

    painter->setPen(QPen{indicatorColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    const auto w = rect.width();
    const auto h = rect.width();
    const auto x = rect.x();
    const auto y = rect.y();
    constexpr auto intendedSize = 16.;

    const auto p1 = QPointF{(4.5 / intendedSize) * w + x, (8.5 / intendedSize) * h + y};
    const auto p2 = QPointF{(7 / intendedSize) * w + x, (11. / intendedSize) * h + y};
    const auto p3 = QPointF{(11.5 / intendedSize) * w + x, (5.5 / intendedSize) * h + y};

    QPainterPath indicatorPath;
    indicatorPath.moveTo(p1);
    indicatorPath.lineTo(p2);
    indicatorPath.lineTo(p3);
    painter->drawPath(indicatorPath);
}

int CheckBoxStyle::indicatorSize() const
{
    return 0;
}
}  // namespace Vanilla