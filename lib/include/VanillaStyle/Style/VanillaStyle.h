#pragma once
#include <QCommonStyle>

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
    int styleHint(StyleHint stylehint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& contentsSize, const QWidget* widget) const override;
    QRect subElementRect(SubElement subElement, const QStyleOption* option, const QWidget* widget) const override;
    void polish(QWidget* w) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    void polish(QPalette& palette) override;
    void polish(QApplication* app) override;
    void unpolish(QWidget* w) override;
    void unpolish(QApplication* app) override;
    QIcon standardIcon(StandardPixmap standardIcon, const QStyleOption *opt = nullptr,
                   const QWidget *widget = nullptr) const override;
    QPixmap standardPixmap(StandardPixmap sp, const QStyleOption *opt = nullptr,
                           const QWidget *widget = nullptr) const override;

    QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap,
                                const QStyleOption *opt) const override;
    int layoutSpacing(QSizePolicy::ControlType control1, QSizePolicy::ControlType control2,
                      Qt::Orientation orientation, const QStyleOption *option = nullptr,
                      const QWidget *widget = nullptr) const override;
    SubControl hitTestComplexControl(ComplexControl cc, const QStyleOptionComplex *opt,
                                     const QPoint &pt, const QWidget *w = nullptr) const override;

    void setConfigPath(const std::string& path);

private:
    Q_DECLARE_PRIVATE(VanillaStyle);
//    Q_DISABLE_COPY(CustomStyle);
    VanillaStylePrivate* const d_ptr;
};

}  // namespace VanillaStyle
