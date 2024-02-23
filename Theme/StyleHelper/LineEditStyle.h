#pragma once
#include <QSize>
#include <QStyle>
#include <QtCore/QRect>

class QStyleOption;
class QPainter;
class QStyleOptionFrame;
class QWidget;

namespace Theme {

class LineEditStyle {

public:
    explicit LineEditStyle();

    void drawPanel(const QStyleOptionFrame* option, QPainter* painter, const QWidget* widget) const;
    // QSize sizeFromContents(const QStyleOptionFrame* option, const QSize& contentsSize, const QWidget* widget) const;
    QRect subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const;
};

} // Theme
