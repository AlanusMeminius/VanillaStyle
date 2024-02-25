#include "VanillaStyle/Config/Config.h"
#include "fstream"

void VanillaStyle::Config::setConfigPath(const std::string& path)
{
    m_configPath = path;
}
VanillaStyle::Config::Config()
= default;

VanillaStyle::Config::ErrorCode VanillaStyle::Config::readConfig(VanillaStyle::StyleConfig& config) const
{
    std::ifstream file(m_configPath);
    if (!file.is_open())
    {
        config = defaultConfig();
        return VanillaStyle::Config::FileNotFound;
    }
    nlohmann::json json;
    file >> json;
    try
    {
        config = json.get<StyleConfig>();
        return VanillaStyle::Config::NoError;
    }
    catch (nlohmann::json::parse_error& e)
    {
        config = defaultConfig();
        return VanillaStyle::Config::ParseError;
    }
}
VanillaStyle::StyleConfig VanillaStyle::Config::defaultConfig() const
{
    auto config = R"(
{
    "name": "Crescent",
    "author": "Alanus",
    "themes": [
        {
            "mode": "light",
            "color": {
                "backgroundColor": "#0xFFFFFF",
                "textColor": "#0x1890FF",
                "primaryColorHovered": "#0x2C9DFF"
            },
            "size": {
                "fontSize": 12,
                "borderWidth": 1,
                "iconSize": 16
            }
        },
        {}
    ]
}
)"_json;
    return config.get<StyleConfig>();
}
