#pragma once
#include "Theme/Config.h"
namespace Vanilla
{
class Style
{
public:
    static void setStyle(const Mode mode);
    static void setStyleFromName(const QString& styleName, Mode mode = Light);
    static void setStyleFromPath(const QString& configPath, Mode mode = Light);

private:
    static void set(const QString& configPath, Mode mode);
};
}  // namespace Vanilla
