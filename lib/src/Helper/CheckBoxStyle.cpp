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
        // 计算rect
        const auto rect = QRectF(optionButton->rect);
        // 获取颜色
        const auto bgColor = theme->checkBtnBgColor(option);
        //        auto bgColor = QColor(10, 255, 255);
        const auto border = theme->getBorder(Theme::ButtonBorder);
        const auto radius = theme->getRadius(Theme::ButtonRadius);
        painter->setRenderHints(QPainter::Antialiasing);
        if (radius < 1)
        {
            painter->fillRect(rect, bgColor);
        }
        else
        {
            painter->setPen(Qt::NoPen);
            painter->setBrush(QColor(10, 255, 255));
            const auto margins = QMarginsF(border / 2., border / 2., border / 2., border / 2.);
            const auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

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
    auto fgColor = theme->checkBtnFgColor(option);
    //    auto fgColor = QColor(10, 10, 255);
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