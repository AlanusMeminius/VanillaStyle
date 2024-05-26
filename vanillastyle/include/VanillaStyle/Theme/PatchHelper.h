#pragma once
#include "ConfigManager.h"

#include <vector>
#include <unordered_set>

#include <QString>

class QWidget;
namespace Vanilla
{
class Theme;
class PatchConfig;
class VANILLA_EXPORT PatchHelper
{
public:
    void init(const std::vector<PatchConfig> & patches);
    void appendPatch(const std::vector<PatchConfig> & patches);
    void appendPatch(const QString& patchPath);

    void patchTheme(const QString& propertyValue, const std::shared_ptr<Theme>& theme);
    const std::shared_ptr<Theme>& getPatchTheme(const QString& propertyName);
    const std::shared_ptr<Theme>& getPatchTheme(const QWidget* widget, const std::shared_ptr<Theme>& originalTheme);

    void clear();

private:
    std::unordered_map<QString, std::shared_ptr<Theme>> m_patchThemes;
    std::unordered_set<QString> widgets;
    std::unordered_set<QString> properties;
    std::shared_ptr<Theme> defaultTheme = nullptr;

    ConfigErrorHanler errorHandler;

};
}

