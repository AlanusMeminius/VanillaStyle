#include "VanillaStyle/Theme/Config.h"
#include "fstream"

void VanillaStyle::ConfigManager::setConfigPath(const std::string& path)
{
    m_configPath = path;
}
VanillaStyle::ConfigManager::ConfigManager() = default;

VanillaStyle::ConfigManager::ErrorCode VanillaStyle::ConfigManager::readConfig(StyleConfig& config) const
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
    "backgroundColor": "#FEFBF6",
    "textColor": "#0x1890",
    "pressedTextColor": "#344955",
    "hoverTextColor": "#50727B",
    "primaryColorHovered": "#0x2C9D",
    "buttonForeground": "#9F95A3",
    "buttonBackground": "#B4B4B8",
    "buttonHoveredForeground": "#53949F",
    "buttonHoveredBackground": "#53949F",
    "buttonPressedForeground": "#322D35",
    "buttonPressedBackground": "#F8F7F8",
    "progressBarBackground": "#EADFB4",
    "progressBarForeground": "#76ABAE",
    "progressBarText": "#C6D27E",
    "lineEditFocusOutline": "#B5C0D0",
    "lineEditOutline": "#B784B7",
    "iconLabelText": "#50727B"
  },
  "size": {
    "fontSize": 12,
    "borderWidth": 1,
    "iconSize": 16,
    "normalRadius": 4,
    "buttonRadius": 4,
    "menuItemRadius": 4
  },
  "icons": {
    "upArrow": ":/VanillaStyle/icons/UpArrow.svg",
    "downArrow": ":/VanillaStyle/icons/DownArrow.svg",
    "progressIndicator": ":/VanillaStyle/icons/Airplane.svg"
  }
}
)"_json;
    return config.get<StyleConfig>();
}
