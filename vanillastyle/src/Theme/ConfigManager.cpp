#include <fstream>

#include <QTextStream>
#include <QFile>

#include "VanillaStyle/Theme/ConfigManager.h"

namespace Vanilla
{

StyleConfig ConfigManager::getConfig(const std::string& path, const Mode mode) const
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        errorHandler.handleError(ConfigErrorHanler::FileNotFound);
        return defaultConfig(mode);
    }
    nlohmann::json json;
    file >> json;
    try
    {
        errorHandler.handleError(ConfigErrorHanler::NoError);
        return json.get<StyleConfig>();
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
    } else
    {
        file.setFileName(":/VanillaStyle/styles/DarkVanillaStyle.json");
    }
    // QFile file(":/VanillaStyle/styles/LightVanillaStyle.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return {};
    }
    QTextStream in(&file);
    std::string jsonStr = in.readAll().toStdString();
    file.close();
    const nlohmann::json json = nlohmann::json::parse(jsonStr);
    return json.get<StyleConfig>();
}

}  // namespace Vanilla