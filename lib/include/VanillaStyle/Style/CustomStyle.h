#pragma once
#include <QCommonStyle>

namespace VanillaStyle
{
class CustomStylePrivate;
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


    void setConfigPath(const std::string& path);

private:
    Q_DECLARE_PRIVATE(CustomStyle);
//    Q_DISABLE_COPY(CustomStyle);
    CustomStylePrivate* const d_ptr;
};

}  // namespace VanillaStyle
