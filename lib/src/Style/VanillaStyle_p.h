#pragma once
#include "VanillaStyle/Style/VanillaStyle.h"
#include "VanillaStyle/Theme/Config.h"
#include "VanillaStyle/Helper/ButtonStyle.h"
#include "VanillaStyle/Helper/CheckBoxStyle.h"
#include "VanillaStyle/Theme/Theme.h"

namespace VanillaStyle {
class VanillaStylePrivate
{
public:
    explicit VanillaStylePrivate(VanillaStyle* q);

private:
    std::shared_ptr<Theme> m_theme;
    std::shared_ptr<CheckBoxStyle> m_checkBoxStyle;
    std::shared_ptr<ButtonStyle> m_buttonStyle;
private:
    VanillaStyle* const q_ptr;
    Q_DECLARE_PUBLIC(VanillaStyle);
};
}
