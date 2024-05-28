#include <QTextStream>

#include "VanillaStyle/Theme/ConfigManager.h"

namespace Vanilla
{
static QString LightStyleFilePath = ":/VanillaStyle/styles/LightVanillaStyle.json";
static QString DarkStyleFilePath = ":/VanillaStyle/styles/DarkVanillaStyle.json";

StyleConfig ConfigManager::getConfig(const QString& path, const Mode mode)
{
    auto returnDefaultConfigJson = [this](const Mode m) {
        return defaultConfigJson(m);
    };
    auto defaultJson = defaultConfigJson(mode);
    const auto configJson = loadConfigJson(path, returnDefaultConfigJson, errorHandler, mode);
    defaultJson.merge_patch(configJson);
    return defaultJson.get<StyleConfig>();
}

StyleConfig ConfigManager::defaultConfig(const Mode mode)
{
    return defaultConfigJson(mode).get<StyleConfig>();
}

nlohmann::json ConfigManager::defaultConfigJson(Mode mode)
{
    QFile file;
    file.setFileName(mode == Light ? LightStyleFilePath : DarkStyleFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return {};
    }
    QTextStream in(&file);
    configJsonStr = in.readAll().toStdString();
    file.close();
    return nlohmann::json::parse(configJsonStr);
}

const nlohmann::json& ConfigManager::getJson()
{
    return jsonData;
}

}  // namespace Vanilla