#pragma once
#include "VanillaStyle/Style/VanillaStyle.h"
#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle/Helper/ButtonStyle.h"
#include "VanillaStyle/Helper/CheckBoxStyle.h"
#include "VanillaStyle/Helper/ComboBoxStyle.h"
#include "VanillaStyle/Helper/RadioButtonStyle.h"
#include "VanillaStyle/Helper/ProgressBarStyle.h"
#include "VanillaStyle/Helper/MenuStyle.h"
#include "VanillaStyle/Helper/SpinBoxStyle.h"
#include "VanillaStyle/Helper/LineEditStyle.h"

namespace VanillaStyle {
class VanillaStylePrivate
{
public:
    explicit VanillaStylePrivate(VanillaStyle* q);

private:
    Theme* m_theme;
    std::shared_ptr<CheckBoxStyle> m_checkBoxStyle;
    std::shared_ptr<RadioButtonStyle> m_radioButtonStyle;
    std::shared_ptr<ButtonStyle> m_buttonStyle;
    std::shared_ptr<ProgressBarStyle> m_progressBarStyle;
    std::shared_ptr<MenuStyle> m_menuStyle;
    std::shared_ptr<SpinBoxStyle> m_spinBoxStyle;
    std::shared_ptr<LineEditStyle> m_lineEditStyle;
    std::shared_ptr<ComboBoxStyle> m_comboBoxStyle;
private:
    VanillaStyle* const q_ptr;
    Q_DECLARE_PUBLIC(VanillaStyle);
};
}
