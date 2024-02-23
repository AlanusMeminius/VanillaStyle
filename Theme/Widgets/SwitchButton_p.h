#pragma once
#include "SwitchButton.h"
#include "Style/Animation.h"

class SwitchButtonPrivate
{
public:
    explicit SwitchButtonPrivate(SwitchButton* q);
    void init();
    void setChecked(bool checked);
    [[nodiscard]] bool isChecked() const;
    void toggle();


    QSize sizeHint() const;

private:
    bool m_checked = false;
    bool m_mouseDown = false;
    int m_handlePosition = 0;
    const int height = 26;
    const int margin = 4;
    int handleSize = height - margin * 2;
    int width = handleSize * 2 + margin * 2;

private:
    SwitchButton* const q_ptr;
    std::shared_ptr<Theme::Animation> mAnimation;
    Q_DECLARE_PUBLIC(SwitchButton);

};
