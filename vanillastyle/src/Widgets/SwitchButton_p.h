#pragma once
#include "VanillaStyle/Widgets/SwitchButton.h"
#include <QSize>
#include <QVariantAnimation>

namespace VanillaStyle
{
class SwitchButtonPrivate
{
public:
    explicit SwitchButtonPrivate(SwitchButton* q);
    void init();
    void setChecked(bool checked);
    [[nodiscard]] bool isChecked() const;
    void toggle();

    [[nodiscard]] QSize sizeHint() const;

    void setupAnimation();
    void startAnimation();

private:
    bool m_checked = false;
    bool m_mouseDown = false;
    const int height = 26;
    const int margin = 4;
    int handleSize = height - margin * 2;
    int width = handleSize * 2 + margin * 2;
    QVariantAnimation handleAnimation;

private:
    SwitchButton* const q_ptr;
    Q_DECLARE_PUBLIC(SwitchButton);
};

}  // namespace VanillaStyle