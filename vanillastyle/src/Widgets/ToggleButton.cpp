#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QSvgRenderer>
#include <QToolTip>

#include "VanillaStyle/Widgets/ToggleButton.h"
#include "VanillaStyle/Style/VanillaStyle.h"
#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle/Helper/Common.h"
#include "ToggleButton_p.h"

namespace Vanilla
{
ToggleButton::ToggleButton(QWidget* parent)
    : QWidget(parent)
    , d_ptr(new ToggleButtonPrivate(this))
{
    Q_D(ToggleButton);
    d->init();
}

ToggleButton::ToggleButton(const QStringList& list, QWidget* parent)
    : ToggleButton(parent)
{
    Q_D(ToggleButton);
    d->itemList = list;
}

ToggleButton::~ToggleButton()
{
    delete d_ptr;
}

QSize ToggleButton::sizeHint() const
{
    Q_D(const ToggleButton);
    return d->sizeHint();
}

void ToggleButton::setItemList(const QStringList& list)
{
    Q_D(ToggleButton);
    d->itemList = list;
    d->checkMode();
    setSize();
}

const QStringList& ToggleButton::itemList() const
{
    Q_D(const ToggleButton);
    return d->itemList;
}

void ToggleButton::setIconList(const QStringList& list)
{
    Q_D(ToggleButton);
    d->iconList = list;
    d->checkMode();
    setSize();
}

const QStringList& ToggleButton::iconList() const
{
    Q_D(const ToggleButton);
    return d->iconList;
}

void ToggleButton::setToolTips(const QStringList& list)
{
    Q_D(ToggleButton);
    d->toolTipsList = list;
}

const QStringList& ToggleButton::toolTips() const
{
    Q_D(const ToggleButton);
    return d->toolTipsList;
}

void ToggleButton::setIconColor(const QColor& color)
{
    Q_D(ToggleButton);
    d->iconColor = color;
    d->isCustomIconColor = true;
}

int ToggleButton::count() const
{
    Q_D(const ToggleButton);
    return d->itemList.size();
}

void ToggleButton::setEnableBackground(bool enable)
{
    Q_D(ToggleButton);
    d->enableBackground = enable;
}

bool ToggleButton::enableBackground() const
{
    Q_D(const ToggleButton);
    return d->enableBackground;
}

void ToggleButton::setVertical()
{
    Q_D(ToggleButton);
    d->isVertical = true;
}

int ToggleButton::offset() const
{
    Q_D(const ToggleButton);
    return d->offset;
}

void ToggleButton::setOffset(const int pos)
{
    Q_D(ToggleButton);
    d->offset = pos;
    update();
}

int ToggleButton::columnWidth() const
{
    Q_D(const ToggleButton);
    return d->columnWidth;
}

void ToggleButton::setColumnWidth(const int width)
{
    Q_D(ToggleButton);
    d->columnWidth = width;
    setSize();
}

int ToggleButton::rowHeight() const
{
    Q_D(const ToggleButton);
    return d->rowHeight;
}

void ToggleButton::setRowHeight(const int height)
{
    Q_D(ToggleButton);
    d->rowHeight = height;
    d->handleSize = d->getHandleSize();
    update();
}

int ToggleButton::currentIndex() const
{
    Q_D(const ToggleButton);
    return d->currentIndex;
}

void ToggleButton::setCurrentIndex(int index)
{
    Q_D(ToggleButton);
    if (index != d->currentIndex)
    {
        d->setCurrentIndex(index);
        emit currentItemChanged(index);
    }
    update();
}

void ToggleButton::mousePressEvent(QMouseEvent* event)
{
    Q_D(ToggleButton);
    if (event->button() == Qt::LeftButton)
    {
        d->m_mouseDown = true;
    }
    else
    {
        event->ignore();
    }
}

void ToggleButton::mouseReleaseEvent(QMouseEvent* event)
{
    Q_D(ToggleButton);
    if (event->button() == Qt::LeftButton)
    {
        d->m_mouseDown = false;
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
        const auto index = d->isVertical ? qIntCast(event->position().y()) / d->rowHeight : qIntCast(event->position().x()) / d->columnWidth;
#else
        const auto index = d->isVertical ? event->pos().y() / d->rowHeight : event->pos().x() / d->columnWidth;
#endif
        if (index < d->itemSize)
        {
            d->setCurrentIndex(index);
            emit currentItemChanged(index);
            update();
        }
    }
    else
    {
        event->ignore();
    }
}

bool ToggleButton::event(QEvent* event)
{
    Q_D(ToggleButton);
    switch (event->type())
    {
    case QEvent::ToolTip:
    {
        const auto helpEvent = dynamic_cast<QHelpEvent*>(event);
        const auto index = d->isVertical ? helpEvent->y() / d->rowHeight : helpEvent->x() / d->columnWidth;

        if (!d->toolTipsList.isEmpty() && (index >= 0 && index < d->toolTipsList.size()))
        {
            QToolTip::showText(dynamic_cast<QHelpEvent*>(event)->globalPos(), d->toolTipsList.at(index), this, QRect(), toolTipDuration());
        }
        else
        {
            QWidget::event(event);
        }
        break;
    }
    default:
        return QWidget::event(event);
    }

    return true;
}

void ToggleButton::setSize()
{
    Q_D(ToggleButton);
    adjustSize();
    update();
}

void ToggleButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    Q_D(ToggleButton);
    QPainter painter(this);
    d->paint(&painter);
}

QSize ToggleButtonPrivate::sizeHint() const
{
    if (isVertical)
    {
        return {columnWidth, itemSize * rowHeight};
    }
    return {columnWidth * itemSize, rowHeight};
}

ToggleButtonPrivate::ToggleButtonPrivate(ToggleButton* q)
    : q_ptr(q)
{
}

void ToggleButtonPrivate::init()
{
    Q_Q(ToggleButton);
    q->setObjectName(QStringLiteral("IconToggleButton"));
    q->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setupAnimation();
}

void ToggleButtonPrivate::setColor()
{
    Q_Q(ToggleButton);

    if (auto* customStyle = qobject_cast<VanillaStyle*>(q->style()))
    {
        if (!isCustomIconColor)
        {
            styleIconColor = customStyle->getColor(q, ColorRole::ToggleButtonIconColor);
        }
        handleColor = customStyle->getColor(q, ColorRole::ToggleButtonIndicatorColor);
        backgroundColor = customStyle->getColor(q, ColorRole::ToggleButtonBackground);
        textColor = customStyle->getColor(q, ColorRole::PrimaryText);
        iconsColorizeMode = customStyle->getTheme()->getIconsColorizeMode();
    }
}

void ToggleButtonPrivate::checkMode()
{
    if (itemList.empty() && iconList.empty())
    {
        return;
    }
    if (itemList.empty() && !iconList.empty())
    {
        mode = IconOnly;
        itemSize = static_cast<int>(iconList.size());
    }
    else if (iconList.empty() && !itemList.empty())
    {
        mode = TextOnly;
        itemSize = static_cast<int>(itemList.size());
    }
    else if (!iconList.empty() && !itemList.empty())
    {
        mode = IconWithText;
        itemSize = static_cast<int>(iconList.size());
        getMaxLenStr(itemList);
    }
}

void ToggleButtonPrivate::getMaxLenStr(const QStringList& list)
{
    Q_Q(ToggleButton);

    const auto maxElem = std::max_element(list.begin(), list.end(), [](const QString& a, const QString& b) {
        return a.size() < b.size();
    });
    if (maxElem != list.end())
    {
        const auto& text = *maxElem;
        const auto fm = QFontMetrics(q->font());
        textWidth = fm.horizontalAdvance(text);
    }
}

void ToggleButtonPrivate::setCurrentIndex(const int index)
{
    Q_Q(ToggleButton);
    if (currentIndex != index)
    {
        preIndex = currentIndex;
        currentIndex = index;
        const auto startValue = isVertical ? preIndex * rowHeight : preIndex * columnWidth;
        const auto endValue = isVertical ? currentIndex * rowHeight : currentIndex * columnWidth;
        handleAnimation.setStartValue(startValue);
        handleAnimation.setEndValue(endValue);
        handleAnimation.start();
    }
}

void ToggleButtonPrivate::setupAnimation()
{
    Q_Q(ToggleButton);
    constexpr auto animationDuration = 500;
    handleAnimation.setTargetObject(q);
    handleAnimation.setDuration(animationDuration);
    handleAnimation.setEasingCurve(QEasingCurve::Type::OutCubic);
    handleAnimation.setPropertyName(QStringLiteral("offset").toUtf8());
}

void ToggleButtonPrivate::paint(QPainter* painter)
{
    Q_Q(const ToggleButton);
    if (itemList.empty() && iconList.empty())
    {
        return;
    }

    setColor();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    // draw background
    if (enableBackground)
    {
        QPainterPath background;
        const QRectF backgroundRect(0, 0, sizeHint().width(), sizeHint().height());
        background.addRoundedRect(backgroundRect, radius, radius);
        painter->fillPath(background, QBrush(backgroundColor));
    }
    // draw handle
    QPainterPath handlePath;
    const auto topLeft = isVertical ? QPointF(handlePadding, offset + handlePadding) : QPointF(offset + handlePadding, handlePadding);
    const QRectF handleRect(topLeft, QSizeF(columnWidth - 2 * handlePadding, handleSize));
    handlePath.addRoundedRect(handleRect, handleRadius, handleRadius);

    painter->fillPath(handlePath, QBrush(handleColor));

    switch (mode)
    {
    case IconOnly:
    {
        QRectF iconRect((columnWidth - iconSize) / 2.0, (rowHeight - iconSize) / 2.0, iconSize, iconSize);
        paintIcon(painter, iconRect);
        break;
    }
    case TextOnly:
    {
        QRectF textRect(0, 0, columnWidth, rowHeight);
        paintText(painter, textRect);
        break;
    }
    case IconWithText:
    {
        const auto iconWithTextWidth = iconSize + textWidth + padding;
        QRectF iconRect((columnWidth - iconWithTextWidth) / 2.0, (rowHeight - iconSize) / 2.0, iconSize, iconSize);
        QRectF textRect(iconRect.right() + 2 * padding, 0, iconWithTextWidth, rowHeight);
        paintIcon(painter, iconRect);
        paintText(painter, textRect);
        break;
    }
    }

    painter->restore();
}

void ToggleButtonPrivate::paintIcon(QPainter* painter, QRectF& rect)
{
    Q_Q(const ToggleButton);
    QSvgRenderer grid;
    for (const auto& item : iconList)
    {
        const auto pixmap = renderSvgToPixmap(item, iconSize, q->devicePixelRatio());
        const auto colorizedPixmap = getColorizedPixmap(pixmap, q, isCustomIconColor ? iconColor : styleIconColor, iconsColorizeMode);
        if (!colorizedPixmap.isNull())
        {
            painter->drawPixmap(rect, colorizedPixmap, QRectF());
        }
        const auto translatePoint = isVertical ? QPoint(0, rowHeight) : QPoint(columnWidth, 0);
        rect.translate(translatePoint);
    }
}

void ToggleButtonPrivate::paintText(QPainter* painter, QRectF& rect)
{
    Q_Q(const ToggleButton);
    for (const auto& item : itemList)
    {
        painter->setPen(textColor);
        const int flag = (mode == IconWithText) ? (Qt::AlignVCenter | Qt::AlignLeft) : Qt::AlignCenter;
        painter->drawText(rect, flag, item);
        const auto translatePoint = isVertical ? QPoint(0, rowHeight) : QPoint(columnWidth, 0);
        rect.translate(translatePoint);
    }
}

}  // namespace Vanilla