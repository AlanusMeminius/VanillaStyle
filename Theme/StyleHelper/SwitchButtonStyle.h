#pragma once
#include <QStyleOptionButton>

namespace Theme
{

class SwitchButtonStyle
{
public:

    enum ControlElement {
        CE_SwitchButton = QStyle::CE_CustomBase + 1,
        CE_SwitchButtonGroove,
        CE_SwitchButtonHandle,
        CE_CustomBase = QStyle::CE_CustomBase + 0xf00000
    };

    enum SubElement {
        SE_SwitchButton = QStyle::SE_CustomBase + 1,
        SE_SwitchButtonGroove,             //滑槽矩形大小
        SE_SwitchButtonHandle,                                         //滑块矩形大小
        SE_CustomBase = QStyle::SE_CustomBase + 0xf00000
    };

    enum PixelMetric {
        PM_SwitchButtonHandleWidth = QStyle::PM_CustomBase + 1,        //switch Handle width
        PM_SwithcButtonHandleHeight,                                   //switch Handle height
        PM_CustomBase = QStyle::PM_CustomBase + 0xf00000
    };
    enum PrimitiveElement {
        PE_SwitchButton = QStyle::PE_CustomBase + 1,
        PE_CustomBase = QStyle::PE_CustomBase + 0xf00000
    };

    void drawGroove(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget);
    void drawHandle(const QStyleOptionButton* option, QPainter* painter, const QWidget* widget);
    QRect subElementRect(QStyle::SubElement subElement, const QStyleOptionButton* option, const QWidget* widget);
    int indicatorSize(QStyle::PixelMetric pm) const;

    void drawControl(QStyleOptionButton* option, QPainter* painter, const QWidget* widget = nullptr);
    inline QRect subElementRect(SubElement subElement, const QStyleOptionButton* option, const QWidget* widget);
    inline int indicatorSize(PixelMetric pm) const;
};

}  // namespace Theme
