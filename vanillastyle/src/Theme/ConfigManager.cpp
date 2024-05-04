#include <QTextStream>
#include <QFile>

#include "VanillaStyle/Theme/ConfigManager.h"

namespace Vanilla
{

StyleConfig ConfigManager::getConfig(const QString& path, const Mode mode)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        errorHandler.handleError(ConfigErrorHanler::FileNotFound);
        return defaultConfig(mode);
    }
    std::string jsonStr = file.readAll().toStdString();
    file.close();
    try
    {
        jsonData = nlohmann::json::parse(jsonStr);
        errorHandler.handleError(ConfigErrorHanler::NoError);
        return jsonData.get<StyleConfig>();
    }
    catch (nlohmann::json::parse_error& e)
    {
        errorHandler.handleError(ConfigErrorHanler::ParseError);
        return defaultConfig(mode);
    }
}

StyleConfig ConfigManager::defaultConfig(const Mode mode)
{
    QFile file;
    if (mode == Light)
    {
        file.setFileName(":/VanillaStyle/styles/LightVanillaStyle.json");
    }
    else
    {
        file.setFileName(":/VanillaStyle/styles/DarkVanillaStyle.json");
    }
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

nlohmann::json ConfigManager::getJson()
{
    return jsonData;
}

}  // namespace Vanilla