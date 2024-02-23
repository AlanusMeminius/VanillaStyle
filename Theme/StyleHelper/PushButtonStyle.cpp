#include "PushButtonStyle.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOptionButton>

#include "Config/Color.h"

namespace Theme
{
PushButtonStyle::PushButtonStyle()
    : commonStyle(std::make_shared<CommonStyle>())
{
}
void PushButtonStyle::setupPainterForShape(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget)
{
    commonStyle->setupPainterForShape(option, painter, widget);
}
void PushButtonStyle::drawButtonShape(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget)
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    setupPainterForShape(option, painter, widget);
    painter->drawRoundedRect(QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5), 6, 6);
    painter->restore();
}
QSize PushButtonStyle::sizeFromContents(const QStyleOptionButton* option, QSize contentsSize, const QWidget* widget) const
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    const int margin = 6;      // usually this comes from PM_ButtonMargin
    const int frameWidth = 2;  // due to pen width 1 in drawButtonBevel, on each side
    return QSize(qMax(60, contentsSize.width() + margin + frameWidth), contentsSize.height() + margin + frameWidth);
}
void PushButtonStyle::adjustTextPalette(QStyleOptionButton* option) const
{
    QColor textColor;
    if (!(option->state & QStyle::State_Enabled))
    {
        textColor = option->palette.color(QPalette::ButtonText);
        textColor.setAlphaF(0.5);
    }
    else if (option->state & QStyle::State_Sunken)
    {
        textColor = Color::pressedTextColor();
    }
    else if (option->state & QStyle::State_MouseOver)
    {
        textColor = Color::hoverTextColor();
    }
    else
    {
        textColor = option->palette.color(QPalette::ButtonText);
    }
    option->palette.setColor(QPalette::ButtonText, textColor);
}
}  // namespace Theme
