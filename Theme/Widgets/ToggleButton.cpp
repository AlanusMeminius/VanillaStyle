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
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);

    if (!useIcon())
    {
        painter.setPen(Qt::NoPen);
        QPainterPath background;
        const QRectF backgroundRect(0, 0, width(), d->rowHeight);
        background.addRoundedRect(backgroundRect, d->radius, d->radius);
        painter.fillPath(background, QBrush(Theme::Color::toogleButtonBackground()));
    }

    QPainterPath handlePath;
    const QRectF handleRect(d->offset + d->handlePadding, d->handlePadding, d->columnWidth - 2 * d->handlePadding, d->handleSize);
    handlePath.addRoundedRect(handleRect, d->radius, d->radius);
    painter.fillPath(handlePath, QBrush(Theme::Color::toogleButtonHandleColor()));

    if (d->itemList.empty())
    {
        return;
    }
    for (int count = 0; count < itemList().length(); ++count)
    {
        if (useIcon())
        {
            QSvgRenderer grid;
            const int x = (d->columnWidth - d->iconSize) / 2 + count * d->columnWidth;
            QRectF iconRectF(x, d->padding, d->iconSize, d->iconSize);
            grid.load(itemList().at(count));
            grid.render(&painter, iconRectF);
        }
        else
        {
            // 画按钮分割线
            if (itemList().length() > 1 && count > 0)
            {
                painter.setPen(QPen(QColor(105, 109, 120), 1, Qt::SolidLine, Qt::SquareCap));
                if (d->offset < d->columnWidth * (count - 1) || d->offset > d->columnWidth * (count))
                {
                    painter.drawLine(d->columnWidth * count, 8, d->columnWidth * count, d->rowHeight - 8);
                }
            }
            painter.setPen(QColor(105, 109, 120));
            QRect textRect(count * columnWidth(), 0, columnWidth(), height());
            painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignHCenter, itemList().at(count));
        }
    }
    painter.restore();
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
