#pragma once
// #include "../../../src/Style/VanillaStyle_p.h"
#include "VanillaStyle/Helper/ButtonStyle.h"

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

    QPalette getStandardPalette() const;
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
    QColor getCustomColor(Theme::ColorRole role);

    using ControlHelper = bool (Helper::*)(const QStyleOption*, QPainter*, const Theme*, const QWidget*) const;
    using ComplexHelper = bool (Helper::*)(const QStyleOptionComplex*, QPainter*, const Theme*, const QWidget*) const;
    using SubElementHelper = QRect (Helper::*)(SubElement, const QStyleOption*, const QWidget*) const;
    using subControlHelper = QRect (Helper::*)(ComplexControl, const QStyleOptionComplex*, SubControl, const QWidget*) const;

    template <typename Func, typename T, typename F>
    std::pair<std::shared_ptr<Helper>, Func> StyleHelper(T& h, F f) const;
    template <typename Func, typename... Args>
    decltype(auto) check(std::pair<std::shared_ptr<Helper>, Func>& fcn, Args&&... args) const;
    template <typename Func, typename... Args>
    decltype(auto) call(std::pair<std::shared_ptr<Helper>, Func>& fcn, Args&&... args) const;

private:
    Q_DECLARE_PRIVATE(VanillaStyle);
    Q_DISABLE_COPY(VanillaStyle);
    VanillaStylePrivate* const d_ptr;
};

template <typename Func, typename T, typename F>
std::pair<std::shared_ptr<Helper>, Func> VanillaStyle::StyleHelper(T& h, F f) const
{
    return std::make_pair(h, static_cast<Func>(f));
}
template <typename Func, typename... Args>
decltype(auto) VanillaStyle::check(std::pair<std::shared_ptr<Helper>, Func>& fcn, Args&&... args) const
{
    return !(fcn.second && call(fcn, std::forward<Args>(args)...));
}
template <typename Func, typename... Args>
decltype(auto) VanillaStyle::call(std::pair<std::shared_ptr<Helper>, Func> &fcn, Args&&... args) const
{
    return (fcn.first.get()->*fcn.second)(std::forward<Args>(args)...);
}

}  // namespace VanillaStyle
