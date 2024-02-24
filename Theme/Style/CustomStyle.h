#pragma once
#include "StyleHelper/CheckBoxStyle.h"
#include "StyleHelper/ProgressbarStyle.h"
#include "StyleHelper/PushButtonStyle.h"
#include "StyleHelper/LineEditStyle.h"
#include "StyleHelper/SpinBoxStyle.h"
#include <QCommonStyle>
#include <StyleHelper/ComboBoxStyle.h>

namespace Theme {

class CustomStyle : public QCommonStyle
{
    Q_OBJECT
public:

    explicit CustomStyle();
    void drawPrimitive(PrimitiveElement pe, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    int pixelMetric(PixelMetric pm, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    void drawComplexControl(ComplexControl complexControl, const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget = nullptr) const override;
    int styleHint(StyleHint stylehint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& contentsSize, const QWidget* widget) const override;
    QRect subElementRect(SubElement subElement, const QStyleOption* option, const QWidget* widget) const override;
    void polish(QWidget* w) override;
    bool eventFilter(QObject* obj, QEvent* event) override;


private:
    std::unique_ptr<ProgressbarStyle> mProgressbarStyle;
    std::unique_ptr<PushButtonStyle> mPushButtonStyle;
    std::unique_ptr<CheckBoxStyle> mCheckBoxStyle;
    std::unique_ptr<LineEditStyle> mLineEditStyle;
    std::unique_ptr<SpinBoxStyle> mSpinBoxStyle;
    std::unique_ptr<ComboBoxStyle> mComboBoxStyle;
};

} // Theme
