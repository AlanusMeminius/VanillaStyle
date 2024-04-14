#pragma once
#include "VanillaStyle/Style/VanillaStyle.h"
#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle/Helper/ButtonStyle.h"
#include "VanillaStyle/Helper/CheckBoxStyle.h"
#include "VanillaStyle/Helper/ComboBoxStyle.h"
#include "VanillaStyle/Helper/Helper.h"
#include "VanillaStyle/Helper/ItemViewStyle.h"
#include "VanillaStyle/Helper/RadioButtonStyle.h"
#include "VanillaStyle/Helper/ProgressBarStyle.h"
#include "VanillaStyle/Helper/MenuStyle.h"
#include "VanillaStyle/Helper/SpinBoxStyle.h"
#include "VanillaStyle/Helper/LineEditStyle.h"

namespace Vanilla
{
class VanillaStylePrivate
{
public:
    explicit VanillaStylePrivate(VanillaStyle* q);
    void init();
    void updatePalette();
private:
    std::shared_ptr<Theme> theme;
    std::shared_ptr<Helper> helper;
    std::shared_ptr<CheckBoxStyle> checkBoxStyle;
    std::shared_ptr<RadioButtonStyle> radioButtonStyle;
     std::shared_ptr<ButtonStyle> buttonStyle;
    std::shared_ptr<ProgressBarStyle> progressBarStyle;
    std::shared_ptr<MenuStyle> menuStyle;
    std::shared_ptr<SpinBoxStyle> spinBoxStyle;
    std::shared_ptr<LineEditStyle> lineEditStyle;
    std::shared_ptr<ComboBoxStyle> comboBoxStyle;
    std::shared_ptr<ItemViewStyle> itemViewStyle;

private:
    VanillaStyle* const q_ptr;
    Q_DECLARE_PUBLIC(VanillaStyle);
};
}  // namespace VanillaStyle
