#include "VanillaStyle/Theme/Config.h"
#include "fstream"

void VanillaStyle::ConfigManager::setConfigPath(const std::string& path)
{
    m_configPath = path;
}
VanillaStyle::ConfigManager::ConfigManager() = default;

VanillaStyle::ConfigManager::ErrorCode VanillaStyle::ConfigManager::readConfig(VanillaStyle::StyleConfig& config) const
{
    std::ifstream file(m_configPath);
    if (!file.is_open())
    {
        config = defaultConfig();
        return FileNotFound;
    }
    nlohmann::json json;
    file >> json;
    try
    {
        config = json.get<StyleConfig>();
        return NoError;
    }
    catch (nlohmann::json::parse_error& e)
    {
        config = defaultConfig();
        return ParseError;
    }
}
VanillaStyle::StyleConfig VanillaStyle::ConfigManager::defaultConfig()
{
    const auto config = R"(
{
    "name": "Crescent",
    "author": "Alanus",
    "mode": "light",
    "color": {
        "backgroundColor": "#0xFFFFFF",
        "textColor": "#0x1890FF",
        "primaryColorHovered": "#0x2C9DFF",
        "buttonHoveredColor": "#0x2C9DFF"
    },
    "size": {
        "fontSize": 12,
        "borderWidth": 1,
        "iconSize": 16,
        "buttonRadius": 4
    }
}
)"_json;
    return config.get<StyleConfig>();
}
