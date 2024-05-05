#include <QTextStream>

#include "VanillaStyle/Theme/ConfigManager.h"

namespace Vanilla
{
static QString LightStyleFilePath = ":/VanillaStyle/styles/LightVanillaStyle.json";
static QString DarkStyleFilePath = ":/VanillaStyle/styles/DarkVanillaStyle.json";

StyleConfig ConfigManager::getConfig(const QString& path, const Mode mode)
{
    auto returnDefaultConfig = [this](const Mode m) { return defaultConfig(m); };
    return loadConfig<StyleConfig>(path, returnDefaultConfig, errorHandler, mode);
}

StyleConfig ConfigManager::defaultConfig(const Mode mode)
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
    jsonData = nlohmann::json::parse(configJsonStr);
    return jsonData.get<StyleConfig>();
}

const nlohmann::json& ConfigManager::getJson()
{
    return jsonData;
}

}  // namespace Vanilla