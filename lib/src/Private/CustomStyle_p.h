#pragma once
#include "VanillaStyle/Style/CustomStyle.h"
#include "VanillaStyle/Config/Config.h"
#include "VanillaStyle/StyleHelper/CheckBoxStyle.h"
#include "VanillaStyle/StyleHelper/ButtonStyle.h"

namespace VanillaStyle {
class CustomStylePrivate
{
public:
    explicit CustomStylePrivate(CustomStyle* q);

private:
    std::shared_ptr<Config> m_config;
    StyleConfig m_styleConfig;
    std::shared_ptr<CheckBoxStyle> m_checkBoxStyle;
    std::shared_ptr<ButtonStyle> m_buttonStyle;
private:
    CustomStyle* const q_ptr;
    Q_DECLARE_PUBLIC(CustomStyle);
};
}
