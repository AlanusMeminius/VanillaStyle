#include "VanillaStyle/Helper/CheckBoxStyle.h"
#include "VanillaStyle/Theme/Theme.h"
#include <QPainter>
#include <QPainterPath>

namespace VanillaStyle
{
void CheckBoxStyle::draw(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme) const
{
    if (const auto* optionButton = qstyleoption_cast<const QStyleOptionButton*>(option))
    {
        painter->setRenderHints(QPainter::Antialiasing);
        // 计算rect
        const auto rect = QRectF(optionButton->rect);
        // theme->setupPainter(option, painter, Theme::CheckBox);
        const auto bgColor = theme->getColor(option, Theme::ButtonBackground);
        const auto border = theme->getBorder(Theme::ButtonBorder);
        const auto radius = theme->getRadius(Theme::ButtonRadius);
        if (radius < 1)
        {
            painter->fillRect(rect, bgColor);
        }
        else
        {
            const auto margins = QMarginsF(border / 2., border / 2., border / 2., border / 2.);
            const auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;
            painter->setPen(Qt::NoPen);
            painter->setBrush(QBrush(bgColor));
            painter->drawRoundedRect(buttonRect, radius, radius);
        }
        if (option->state & QStyle::State_On)
        {
            drawIndicator(option, rect, painter, theme);
        }
    }
}
void CheckBoxStyle::drawIndicator(const QStyleOption* option, const QRectF rect, QPainter* painter, const Theme* theme) const
{
    const auto fgColor = theme->getColor(option, Theme::ButtonForeground);

    // auto fgColor = painter->pen().color();
    painter->setPen(QPen{fgColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
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
}  // namespace VanillaStyle