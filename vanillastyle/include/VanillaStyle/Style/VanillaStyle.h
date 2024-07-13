#pragma once

#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Theme/Mode.h"
// #include "VanillaStyle/Theme/Theme.h"

#include <QCommonStyle>
#include <QPainter>

namespace Vanilla
{
class VanillaStylePrivate;
class VANILLA_EXPORT VanillaStyle : public QCommonStyle
{
    Q_OBJECT
public:
    explicit VanillaStyle();
    explicit VanillaStyle(Mode mode);
    ~VanillaStyle();

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

    void setConfigPath(const QString& path);
    void setMode(Mode mode);

    const std::shared_ptr<Theme>& getTheme(const QWidget* widget, const std::shared_ptr<Theme>& theme) const;
    const std::shared_ptr<Theme>& getTheme() const;
    void appendPatch(const QString& patchPath);

    QColor getColor(const QWidget* widget, ColorRole role);
    int getSize(const QWidget* widget, SizeRole role);

private:
    using ControlHelper = std::function<bool(const QStyleOption*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*)>;
    using ComplexHelper = std::function<bool(const QStyleOptionComplex*, QPainter*, const std::shared_ptr<Theme>&, const QWidget*)>;
    using SubElementHelper = std::function<QRect(SubElement, const QStyleOption*, const std::shared_ptr<Theme>&, const QWidget*)>;
    using SubControlHelper = std::function<QRect(ComplexControl, const QStyleOptionComplex*, SubControl, const std::shared_ptr<Theme>&, const QWidget*)>;
    using SizeFromContents =
        std::function<QSize(ContentsType type, const QStyleOption* option, const QSize& contentsSize, const std::shared_ptr<Theme>&, const QWidget* widget)>;

    template <typename T, typename F>
    auto createHelper(const std::shared_ptr<T>& objectPtr, F fptr) const;

private:
    Q_DECLARE_PRIVATE(VanillaStyle);
    Q_DISABLE_COPY(VanillaStyle);
    VanillaStylePrivate* const d_ptr;
};

template <typename T, typename F>
auto VanillaStyle::createHelper(const std::shared_ptr<T>& objectPtr, F fptr) const
{
    return [objectPtr, fptr = std::move(fptr)]<typename... P>(P&&... params) -> decltype(auto){
        return std::invoke(fptr, objectPtr, std::forward<P>(params)...);
    };
}

}  // namespace Vanilla
