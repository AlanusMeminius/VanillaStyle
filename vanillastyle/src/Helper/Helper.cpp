#include <QPainter>

#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace Vanilla
{

bool Helper::emptyControl(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*) const
{
    return true;
}

bool Helper::shapedFrame(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    if (const bool isComboPopList = widget->inherits("QComboBoxPrivateContainer"); !isComboPopList)
    {
        return true;
    }
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QBrush(Qt::white));
    painter->setPen(Qt::NoPen);
    const auto radius = theme->getRadius(Theme::NormalRadius);
    painter->drawRoundedRect(option->rect, radius, radius);

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
        const auto fgcolor = theme->getColor(option, Theme::LabelText);
        painter->setPen(fgcolor);
        painter->drawText(rect, textFlags, elidedText);
    }
    return true;
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

}  // namespace Vanilla