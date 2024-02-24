#include "ToggleButton.h"
#include "ToggleButton_p.h"
#include "Config/Color.h"

#include <QMouseEvent>
#include <QSvgRenderer>
#include <QPainter>
#include <QPainterPath>

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
void ToggleButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    Q_D(ToggleButton);
    QPainter painter(this);
    d->paint(&painter);
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

ToggleButtonPrivate::ToggleButtonPrivate(ToggleButton* q)
    : q_ptr(q)
    , mAnimation(std::make_shared<Theme::Animation>())
{
}
void ToggleButtonPrivate::init()
{
    Q_Q(ToggleButton);
    q->setObjectName(QStringLiteral("IconToggleButton"));
    q->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mAnimation->setTargetObject(q);
    mAnimation->setPropertyName(QStringLiteral("offset"));
}
void ToggleButtonPrivate::setCurrentIndex(const int index)
{
    Q_Q(ToggleButton);
    if (currentIndex != index)
    {
        preIndex = currentIndex;
        currentIndex = index;
        mAnimation->setValue(QVariant(preIndex * columnWidth), QVariant(currentIndex * columnWidth));
        mAnimation->start();
    }
}
QSize ToggleButtonPrivate::sizeHint() const
{
    return {columnWidth * static_cast<int>(itemList.size()), rowHeight};
}
void ToggleButtonPrivate::paint(QPainter* painter) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    if (!m_useIcon)
    {
        painter->setPen(Qt::NoPen);
        QPainterPath background;
        const QRectF backgroundRect(0, 0, sizeHint().width(), rowHeight);
        background.addRoundedRect(backgroundRect, radius, radius);
        painter->fillPath(background, QBrush(Theme::Color::toogleButtonBackground()));
    }

    QPainterPath handlePath;
    const QRectF handleRect(offset + handlePadding, handlePadding, columnWidth - 2 * handlePadding, handleSize);
    handlePath.addRoundedRect(handleRect, radius, radius);
    painter->fillPath(handlePath, QBrush(Theme::Color::toogleButtonHandleColor()));

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
            iconRectF.translate(columnWidth,0);
        }
    }
    else
    {
        QRectF textRect(0, 0, columnWidth, rowHeight);
        for (const auto& item : itemList)
        {
            painter->setPen(QColor(105, 109, 120));
            painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignHCenter, item);
            textRect.translate(columnWidth, 0);
        }
    }
    painter->restore();
}
