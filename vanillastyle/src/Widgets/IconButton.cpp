#include "VanillaStyle/Widgets/IconButton.h"
#include "IconButton_p.h"
#include "VanillaStyle/Helper/Common.h"
#include "VanillaStyle/Style/VanillaStyle.h"

#include <QPainter>

namespace Vanilla
{
IconButton::IconButton(QWidget* parent)
    : QAbstractButton(parent)
    , d_ptr(new IconButtonPrivate(this))
{
    Q_D(IconButton);
    d->init();
}

IconButton::IconButton(const QIcon& icon, QWidget* parent)
    : IconButton(parent)
{
    setIcon(icon);
}

IconButton::~IconButton()
{
    delete d_ptr;
}

QSize IconButton::sizeHint() const
{
    Q_D(const IconButton);
    return d->sizeHint();
}
void IconButton::usingOriginalIconColor()
{
    Q_D(IconButton);
    d->isCustomIconColor = true;
}

void IconButton::setIconColor(const QColor& color)
{
    Q_D(IconButton);
    d->iconColor = color;
    d->isCustomIconColor = true;
}

void IconButton::setIconFirst()
{
    Q_D(IconButton);
    d->isIconFirst = true;
}

void IconButton::setTextColor(const QColor& textColor)
{
    Q_D(IconButton);
    d->textColor = textColor;
    d->isCustomTextColor = true;
}

void IconButton::setTextSizeRole(const Theme::TextSizeRole& textSizeRole)
{
    Q_D(IconButton);
    d->textSizeRole = textSizeRole;
    d->isCustomFont = true;
}

void IconButton::setButtonBorderColor(const QColor& color)
{
    Q_D(IconButton);
    d->buttonBorderColor = color;
    d->isCutomBorderColor = true;
}

void IconButton::paintEvent(QPaintEvent* event)
{
    Q_D(IconButton);
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    d->paint(&painter);
}

IconButtonPrivate::IconButtonPrivate(IconButton* q)
    : q_ptr(q)
{
}

void IconButtonPrivate::init()
{
    Q_Q(IconButton);
    q->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // q->textFont
}

QSize IconButtonPrivate::sizeHint() const
{
    Q_Q(const IconButton);
    return {totalWidth, q->iconSize().height() + 2 * padding};
}

void IconButtonPrivate::paint(QPainter* painter)
{
    Q_Q(IconButton);
    setUpStyle();
    const auto opacity = q->isEnabled() ? 1.0 : 0.2;
    painter->setOpacity(opacity);
    const auto iconSize = q->iconSize().width();
    const QRect rect = q->rect();

    if (isCutomBorderColor)
    {
        Helper::renderRoundBorder(painter, QRectF(rect).adjusted(1, 1, -1, -1), buttonBorderColor, 1, 5);
    }

    QRect iconOuterRect;
    QRect textOuterRect;
    if (q->text().isEmpty())
    {
        totalWidth = iconSize + padding * 2;
        iconOuterRect = QRect(0, 0, iconSize + 2 * padding, rect.height());
    }
    else
    {
        const QFontMetrics fm(textFont);
        textWidth = fm.horizontalAdvance(q->text());

        totalWidth = iconSize + textWidth + padding * 4;

        const auto iconLeft = isIconFirst ? 0 : textWidth + padding * 2;
        iconOuterRect = QRect(iconLeft, 0, iconSize + 2 * padding, rect.height());
        const auto textLeft = isIconFirst ? iconSize + padding * 2 : 0;
        textOuterRect = QRect(textLeft, 0, textWidth + 2 * padding, rect.height());
    }

    if (const auto pixmap = q->icon().pixmap(q->iconSize()); !pixmap.isNull())
    {
        const auto iconRect = centerRect(iconOuterRect, iconSize, iconSize);
        painter->drawPixmap(iconRect, isCustomIconColor ? pixmap : getCachedPixmap(pixmap, iconColor));
    }
    if (!q->text().isEmpty())
    {
        const auto fontRect = centerRect(textOuterRect, textWidth, rect.height());
        painter->setFont(textFont);
        painter->setPen(textColor);
        painter->drawText(fontRect, Qt::AlignCenter | Qt::TextSingleLine, q->text());
    }
}

void IconButtonPrivate::setUpStyle()
{
    Q_Q(IconButton);
    auto* customStyle = qobject_cast<VanillaStyle*>(q->style());
    if (!customStyle)
    {
        return;
    }
    if (!isCustomIconColor)
    {
        iconColor = customStyle->getCustomColor(Theme::ColorRole::IconColor);
    }

    if (!isCustomFont)
    {
        textFont = customStyle->getCustomFont(textSizeRole);
    }
    else
    {
        textFont = q->font();
    }

    if (!isCustomTextColor)
    {
        textColor = customStyle->getCustomColor(Theme::ColorRole::LabelText);
    }
    else
    {
        textColor = q->palette().color(QPalette::ButtonText);
    }
}

}  // namespace Vanilla