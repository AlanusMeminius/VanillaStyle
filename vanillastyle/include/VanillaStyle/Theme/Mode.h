#pragma once

namespace Vanilla
{
enum Mode
{
    Light,
    Dark
};

enum class ColorRole
{
    PrimaryText,
    LabelText,

    LabelBackground,
    LabelBorderColor,

    IconColor,
    IndicatorColor,

    ButtonForeground,
    ButtonBackground,
    ButtonBorderColor,

    CheckBoxForeground,
    CheckBoxBackground,
    CheckBoxBorderColor,

    RadioButtonForeground,
    RadioButtonBackground,
    RadioButtonBorderColor,

    ProgressBarForeground,
    ProgressBarBackground,
    ProgressBarText,

    LineEditOutline,
    LineEditBackground,

    ToggleButtonBackground,
    ToggleButtonForeground,
    ToggleButtonBorderColor,
    ToggleButtonIndicatorColor,
    ToggleButtonIconColor,

    ItemViewEvenRowColor,
    ItemViewOddRowColor,
    ItemViewSelectedColor,

    ComboBoxDropDownBackground,
    ScrollBarSliderColor,
    MenuBackground,
    MenuSeparatorColor,
    MenuShortCutsBackground,
};

enum class TextSizeRole
{
    Default,
    H1,
    H2,
    H3,
    H4,
    H5,
    H6
};

enum class SizeRole
{
    NormalRadius,
    NormalBorder,
    NormalPadding,
    IconSize,

    ButtonTextMargin,
    ButtonBorder,
    CheckBoxBorder,

    ButtonRadius,
    ItemViewRadius,

    MenuItemPadding,
    MenuBorder,
    CheckBoxIndicatorMargin,
    CheckBoxPadding,
    ProgressBarHeight,
    ProgressBarTextMargin,

    ScrollBarWidth,
    SmallRadius,
};

enum class IconRole
{
    UpArrow,
    DownArrow,
    LeftArrow,
    RightArrow,
    ProgressIndicator,
};

enum class ProgressMode
{
    ModeOne,
    ModeTwo
};

}  // namespace Vanilla
