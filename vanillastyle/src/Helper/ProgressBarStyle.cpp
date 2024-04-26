#include <QPainter>
#include <QSvgRenderer>

#include "VanillaStyle/Helper/ProgressBarStyle.h"

#include "VanillaStyle/Helper/Common.h"
#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Theme/Theme.h"

namespace Vanilla
{
bool ProgressBarStyle::drawGroove(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    const auto* opt = qstyleoption_cast<const QStyleOptionProgressBar*>(option);
    if (!opt)
    {
        return true;
    }
    painter->setRenderHint(QPainter::Antialiasing);
    const auto rect = opt->rect.toRectF();

    const QColor bgColor = theme->getColor(option, Theme::ProgressBarBackground);
    if (const auto mode = theme->getProgressMode(); mode == Theme::ModeOne)
    {
        painter->setPen(QPen(bgColor, 2, Qt::DashLine));
        painter->drawLine(QPointF(rect.left(), rect.center().y()), QPointF(rect.right(), rect.center().y()));
    }
    else if (mode == Theme::ModeTwo)
    {
        const auto progressHeight = theme->getSize(Theme::ProgressBarHeight);
        auto modeTwoRect = rect;
        modeTwoRect.setHeight(progressHeight);
        modeTwoRect.moveCenter(rect.center());
        const auto radius = theme->getRadius(Theme::ProgressRadius);
        Helper::renderRoundRect(painter, modeTwoRect, bgColor, radius);
    }
    return true;
}

bool ProgressBarStyle::drawContents(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    Q_UNUSED(widget);
    const auto* opt = qstyleoption_cast<const QStyleOptionProgressBar*>(option);
    if (!opt)
    {
        return true;
    }
    const auto value = opt->progress - opt->minimum;
    const auto range = opt->maximum - opt->minimum;
    if (value > 0)
    {
        painter->setRenderHint(QPainter::Antialiasing);
        const auto rect = opt->rect;
        const QColor fgColor = theme->getColor(option, Theme::ProgressBarForeground);
        const auto mode = theme->getProgressMode();
        const auto percentage = 1 - static_cast<double>(value) / static_cast<double>(range);
        const auto progressRect = rect.adjusted(0, 0, -static_cast<int>(rect.width() * percentage), 0).toRectF();
        if (mode == Theme::ModeOne)
        {
            painter->setPen(QPen(fgColor, 2, Qt::SolidLine));
            painter->drawLine(QPointF(progressRect.left(), progressRect.center().y()), QPointF(progressRect.right(), progressRect.center().y()));
            const double indicatorSize = progressRect.height();
            const auto planeRect = QRectF(progressRect.right(), progressRect.center().y() - indicatorSize / 2, indicatorSize, indicatorSize);
            const auto path = theme->getIconPath(Theme::IconRole::ProgressIndicator);
            if (path.isEmpty())
            {
                return true;
            }
            renderSvgFromPath(path, painter, planeRect);
        }
        else if (mode == Theme::ModeTwo)
        {
            const auto progressHeight = theme->getSize(Theme::ProgressBarHeight);
            const double indicatorSize = progressRect.height() / 2;
            const auto margin = (progressRect.height() - progressHeight) / 2;
            const auto radius = theme->getRadius(Theme::ProgressRadius);
            const auto modeTwoRect = progressRect.adjusted(0, margin, 0, -margin);
            Helper::renderRoundRect(painter, modeTwoRect, fgColor, radius);

            const auto topRightPoint = QPointF(modeTwoRect.right() - indicatorSize, modeTwoRect.center().y() - indicatorSize / 2);
            const auto indicatorRect = QRectF(topRightPoint, QSizeF(indicatorSize, indicatorSize));
            Helper::renderEllipse(painter, indicatorRect, Qt::white);

            const auto innerIndicatorRect = indicatorRect.adjusted(2, 2, -2, -2);
            Helper::renderEllipse(painter, innerIndicatorRect, fgColor);
        }
    }
    return true;
}
bool ProgressBarStyle::drawLabel(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const
{
    Q_UNUSED(widget)
    const auto* opt = qstyleoption_cast<const QStyleOptionProgressBar*>(option);
    if (!opt)
    {
        return true;
    }
    const QPen oldPen = painter->pen();
    // progressBarTextColor
    const QColor tColor = theme->getColor(option, Theme::ProgressBarText);
    painter->setPen(tColor);
    // const auto textRext = opt->rect.adjusted(0, 0, 0, -opt->rect.height());
    painter->drawText(opt->rect, Qt::AlignRight | Qt::AlignVCenter | Qt::TextSingleLine, opt->text);
    painter->setPen(oldPen);
    return true;
}

QRect ProgressBarStyle::subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const std::shared_ptr<Theme>& theme,
                                       const QWidget* widget) const
{
    Q_UNUSED(widget)
    if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
    {
        if (subElement == QStyle::SE_ProgressBarLabel)
        {
            return progressBarOption->rect.adjusted(0, 0, 0, 0);
        }
        else if (subElement == QStyle::SE_ProgressBarContents)
        {
            const auto textWidth = theme->getSize(Theme::ProgressBarTextMargin);
            return progressBarOption->rect.adjusted(0, 0, -textWidth - option->rect.height() / 2, 0);
        }
        else if (subElement == QStyle::SE_ProgressBarGroove)
        {
            const auto textWidth = theme->getSize(Theme::ProgressBarTextMargin);
            return progressBarOption->rect.adjusted(0, 0, -textWidth, 0);
        }
    }
    return option->rect;
}
}  // namespace Vanilla