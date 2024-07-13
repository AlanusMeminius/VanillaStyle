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
#include "VanillaStyle/Helper/ScrollBarStyle.h"
#include "VanillaStyle/Helper/ToolButtonStyle.h"
#include "VanillaStyle/Theme/Utils.h"


namespace Vanilla
{
class PatchHelper;
}
namespace Vanilla
{
class VanillaStylePrivate
{
public:
    explicit VanillaStylePrivate(VanillaStyle* q);
    explicit VanillaStylePrivate(VanillaStyle* q, Mode mode);
    void init() const;
    void updatePalette() const;
    void updateFont() const;
    void configNotifier(const QString& configPath);

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
    std::shared_ptr<ScrollBarStyle> scrollBarStyle;
    std::shared_ptr<ToolButtonStyle> toolButtonStyle;

    std::shared_ptr<PatchHelper> patchHelper;
    std::unique_ptr<ConfigChangeNotifier> configChangeNotifier = nullptr;

private:
    VanillaStyle* const q_ptr;
    Q_DECLARE_PUBLIC(VanillaStyle);
};
}  // namespace Vanilla
