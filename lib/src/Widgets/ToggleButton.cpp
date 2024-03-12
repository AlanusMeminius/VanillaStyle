#include "VanillaStyle/Widgets/ToggleButton.h"
#include "ToggleButton_p.h"
#include "VanillaStyle/Style/VanillaStyle.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QSvgRenderer>

namespace VanillaStyle
{
ToggleButton::ToggleButton(QWidget* parent)
    : QWidget(parent)
    , d_ptr(new ToggleButtonPrivate(this))
{
    Q_D(ToggleButton);
    d->init();
    setFixedHeight(28);
    setMinimumWidth(300);
}

ToggleButton::ToggleButton(const QStringList& list, QWidget* parent)
    : ToggleButton(parent)
{
    Q_D(ToggleButton);
    d->itemList = list;
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
}
const QStringList& ToggleButton::itemList() const
{
    Q_D(const ToggleButton);
    return d->itemList;
}
bool ToggleButton::useIcon()
{
    Q_D(ToggleButton);
    return d->m_useIcon;
}
void ToggleButton::setUseIcon(const bool isIcon)
{
    Q_D(ToggleButton);
    d->m_useIcon = isIcon;
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
    update();
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
        if (const auto index = qIntCast(event->position().x()) / d->columnWidth; index < static_cast<int>(d->itemList.size()))
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
void ToggleButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    Q_D(ToggleButton);
    QPainter painter(this);
    d->paint(&painter);
}

QSize ToggleButtonPrivate::sizeHint() const
{
    return {columnWidth * static_cast<int>(itemList.size()), rowHeight};
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

void ToggleButtonPrivate::setCurrentIndex(const int index)
{
    Q_Q(ToggleButton);
    if (currentIndex != index)
    {
        preIndex = currentIndex;
        currentIndex = index;
        handleAnimation.setStartValue(preIndex * columnWidth);
        handleAnimation.setEndValue(currentIndex * columnWidth);
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

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    if (!m_useIcon)
    {
        painter->setPen(Qt::NoPen);
        QPainterPath background;
        const QRectF backgroundRect(0, 0, sizeHint().width(), rowHeight);
        background.addRoundedRect(backgroundRect, radius, radius);
        painter->fillPath(background, QBrush(QColor(229, 230, 235)));
    }

    QPainterPath handlePath;
    const QRectF handleRect(offset + handlePadding, handlePadding, columnWidth - 2 * handlePadding, handleSize);
    handlePath.addRoundedRect(handleRect, radius, radius);
    QColor handleColor;
    QColor backgroundColor;
    if (auto * customStyle = qobject_cast<VanillaStyle*>(q->style()))
    {
        handleColor = customStyle->handleColor();
        backgroundColor = customStyle->buttonBackgroud();
    }
    painter->fillPath(handlePath, QBrush(handleColor));

    if (itemList.empty())
    {
        return;
    }
    if (m_useIcon)
    {
        QRect iconRectF((columnWidth - iconSize) / 2, padding, iconSize, iconSize);
        QSvgRenderer grid;
        for (const auto& item : itemList)
        {
            grid.load(item);
            grid.render(painter, iconRectF.toRectF());
            iconRectF.translate(columnWidth, 0);
        }
    }
    else
    {
        QRectF textRect(0, 0, columnWidth, rowHeight);
        for (const auto& item : itemList)
        {
            painter->setPen(backgroundColor);
            painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignHCenter, item);
            textRect.translate(columnWidth, 0);
        }
    }
    painter->restore();
}

}  // namespace VanillaStyle