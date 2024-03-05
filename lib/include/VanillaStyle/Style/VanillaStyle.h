#pragma once
#include <QCommonStyle>
#include <QPainter>
#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle/Helper/CheckBoxStyle.h"
#include "VanillaStyle/Theme/Config.h"

namespace VanillaStyle
{
class VanillaStylePrivate;
class VanillaStyle : public QCommonStyle
{
    Q_OBJECT
public:
    explicit VanillaStyle();

    void drawPrimitive(PrimitiveElement pe, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    int pixelMetric(PixelMetric pm, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    void drawComplexControl(ComplexControl complexControl, const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget = nullptr) const override;
    int styleHint(StyleHint stylehint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& contentsSize, const QWidget* widget) const override;
    QRect subElementRect(SubElement subElement, const QStyleOption* option, const QWidget* widget) const override;
    QRect subControlRect(ComplexControl control, const QStyleOptionComplex* option, SubControl subControl, const QWidget* widget) const override;
    void polish(QWidget* w) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

    void setConfigPath(const std::string& path);

private:
    Q_DECLARE_PRIVATE(VanillaStyle);
    Q_DISABLE_COPY(VanillaStyle);
    VanillaStylePrivate* const d_ptr;
};

}  // namespace VanillaStyle
