#pragma once
namespace VanillaStyle
{
class Style
{
public:
    static void setStyle();
    static void setStyleFromName(const QString& styleName);
    static void setStyleFromPath(const QString& configPath);

private:
    static void set(const QString& configPath);
};
}  // namespace VanillaStyle
