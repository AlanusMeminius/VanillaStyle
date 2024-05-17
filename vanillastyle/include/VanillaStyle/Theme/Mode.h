#pragma once

namespace Vanilla
{
enum Mode
{
    Light,
    Dark
};


enum ColorRole
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

    ToggleButtonBackground,
    ToggleButtonForeground,
    ToggleButtonBorderColor,
    ToggleButtonIndicatorColor,
    ToggleButtonIconColor,

    ItemViewEvenRowColor,
    ItemViewOddRowColor,
    ItemViewSelectedColor,

    ComboBoxDropDownBackground,
    ScrollBarSliderColor
};

enum TextSizeRole
{
    Default,
    H1,
    H2,
    H3,
    H4,
    H5,
    H6
};

enum SizeRole
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
    CheckBoxIndicatorMargin,
    CheckBoxSpacing,
    ProgressBarHeight,
    ProgressBarTextMargin,

    ScrollBarWidth,
    SmallRadius
};

enum IconRole
{
    UpArrow,
    DownArrow,
    ProgressIndicator,
};

enum ProgressMode
{
    ModeOne,
    ModeTwo
};

}
