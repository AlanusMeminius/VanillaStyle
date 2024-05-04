#pragma once
#include "Theme/Config.h"

#define VANILLA_PATCH_PROPERTY "_vanillaStyle_Patch"

namespace Vanilla
{
class VanillaStyle;
class Style
{
public:
    static void setDefaultTheme(Mode mode);
    static void setStyleFromAppDir(const QString& styleName);
    static void setStyleFromPath(const QString& configPath);

private:
    static VanillaStyle* getStyle();
};
}  // namespace Vanilla
