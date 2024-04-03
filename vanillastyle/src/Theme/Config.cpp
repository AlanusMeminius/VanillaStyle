#include <fstream>

#include "VanillaStyle/Theme/Config.h"

Vanilla::StyleConfig Vanilla::ConfigManager::getConfig(const std::string& path) const
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        errorHandler.handleError(ConfigErrorHanler::FileNotFound);
        return defaultConfig();
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
        return defaultConfig();
    }
}

Vanilla::StyleConfig Vanilla::ConfigManager::defaultConfig()
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
