#include <QPainter>
#include <QPainterPath>

#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle/Theme/Utils.h"

namespace Vanilla
{

bool Helper::emptyControl(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*) const
{
    return true;
}

bool Helper::shapedFrame(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    if (const bool isComboPopList = widget->inherits("QComboBoxPrivateContainer"); isComboPopList)
    {
        painter->setRenderHint(QPainter::Antialiasing);

        const auto radius = theme->getSize(SizeRole::NormalRadius);
        renderRoundRect(painter, option->rect, theme->getColor(option, ColorRole::ComboBoxDropDownBackground), radius);
        return true;
    }

    // if (const auto classname = QString(widget->metaObject()->className()); classname == "QLabel")
    // {
    //     const auto propertyValue = getPatchProperty(widget);
    //     if (!propertyValue.isEmpty() && propertyValue == "QLabelPatch")
    //     {
    //         painter->setRenderHint(QPainter::Antialiasing);
    //         const auto radius = theme->getSize(NormalRadius);
    //         renderRoundBorder(painter, option->rect.adjusted(1, 1, -1, -1), theme->getColor(option, LabelBorderColor), 1, radius);
    //         return true;
    //     }
    //     return true;
    // }

    return true;
}
bool Helper::drawLabel(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget, int flag) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionButton*>(option);
    if (!opt)
    {
        return true;
    }
    if (!opt->text.isEmpty())
    {
        painter->setRenderHints(QPainter::Antialiasing);

        const auto rect = opt->rect;
        const auto textFlags = flag | Qt::AlignVCenter | Qt::AlignBaseline | Qt::TextSingleLine | Qt::TextHideMnemonic;
        const auto elidedText = opt->fontMetrics.elidedText(opt->text, Qt::ElideRight, rect.width(), Qt::TextSingleLine);
        painter->setBrush(Qt::NoBrush);
        const auto fgcolor = theme->getColor(option, ColorRole::LabelText);
        painter->setPen(fgcolor);
        painter->drawText(rect, textFlags, elidedText);
    }
    return true;
}

bool Helper::drawSplitter(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto& rect = option->rect;
    const auto height = theme->getSize(SizeRole::ScrollBarWidth);
    const auto width = theme->getSize(SizeRole::IconSize);
    const auto radius = theme->getSize(SizeRole::SmallRadius);
    const auto color = theme->getColor(option, ColorRole::ButtonForeground);
    const auto center = centerRectF(QRectF(rect), width, height);
    painter->setRenderHints(QPainter::Antialiasing);
    renderRoundRect(painter, center, color, radius);
    return true;
}

QSize Helper::sizeFromContentsForSplitterHandle(QStyle::ContentsType type, const QStyleOption* option, const QSize& contentsSize,
                                                const std::shared_ptr<Theme>& theme, const QWidget* widget)
{
    const auto height = theme->getSize(SizeRole::ScrollBarWidth);
    return {contentsSize.width(), height};
}

bool Helper::drawAlignCenterLabel(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    return drawLabel(option, painter, theme, widget, Qt::AlignCenter);
}

bool Helper::drawAlignLeftLabel(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    return drawLabel(option, painter, theme, widget, Qt::AlignLeft);
}

void Helper::renderRoundBorder(QPainter* painter, const QRectF& rect, const QColor& color, const qreal border, const qreal radius)
{
    painter->setPen(QPen(color, border, Qt::SolidLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(rect, radius, radius);
}

void Helper::renderRoundRect(QPainter* painter, const QRectF& rect, const QColor& color, qreal radius)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(color));
    painter->drawRoundedRect(rect, radius, radius);
}

void Helper::renderEllipse(QPainter* painter, const QRectF& rect, const QColor& color)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(rect);
}

void Helper::renderEllipseBorder(QPainter* painter, const QRectF& rect, const QColor& color, qreal border)
{
    painter->setPen(QPen(color, border, Qt::SolidLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(rect);
}

bool Helper::drawCheckBox(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget)
{
    const auto* opt = qstyleoption_cast<const QStyleOptionButton*>(option);
    if (!opt)
    {
        return true;
    }
    drawCheckBoxHelper(opt, painter, theme, widget);
    return true;
}

void Helper::drawCheckBoxHelper(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget)
{
    painter->setRenderHints(QPainter::Antialiasing);
    const auto rect = QRectF(option->rect);
    const auto bgColor = theme->getColor(option, ColorRole::CheckBoxBackground);
    const auto borderColor = theme->getColor(option, ColorRole::CheckBoxBorderColor);
    const auto border = theme->getSize(SizeRole::CheckBoxBorder);
    const auto radius = theme->getSize(SizeRole::ButtonRadius);
    const auto halfBorder = border / 2.;
    const auto margins = QMarginsF(halfBorder, halfBorder, halfBorder, halfBorder);
    const auto buttonRect = border > 0.1 ? rect.marginsRemoved(margins) : rect;

    renderRoundRect(painter, buttonRect, bgColor, radius);

    if (border > 0.1)
    {
        renderRoundBorder(painter, buttonRect, borderColor, border, radius);
    }

    if ((theme->flags(option) & Theme::Checked) == Theme::Checked)
    {
        drawCheckBoxIndicator(option, rect, painter, theme);
    }
}

void Helper::drawCheckBoxIndicator(const QStyleOption* option, const QRectF rect, QPainter* painter, const std::shared_ptr<Theme>& theme)
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

}  // namespace Vanilla