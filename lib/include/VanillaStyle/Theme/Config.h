#pragma once
#include <QApplication>
#include <QSettings>
#include <QColor>
#include <nlohmann/json.hpp>

namespace nlohmann
{
template <>
struct adl_serializer<QColor>
{
    static void to_json(nlohmann::json& j, const QColor& color)
    {
        try
        {
            j = color.name(QColor::HexArgb).toStdString();
        }
        catch (const std::exception& e)
        {
            j = "Error: Unable to convert QColor to hex string";
        }
    }

    static void from_json(const nlohmann::json& j, QColor& color)
    {
        try
        {
            color = QColor::fromString(QString::fromStdString(j.get<std::string>()));
        }
        catch (const std::exception& e)
        {
            color = QColor(Qt::black);
        }
    }
};
}  // namespace nlohmann

namespace VanillaStyle
{

class Basic
{
public:
    Basic() = default;
    virtual ~Basic() = default;
    virtual std::string toString() = 0;
};

class Color : public Basic
{
public:
    QColor backgroundColor;
    QColor textColor;
    QColor pressedTextColor;
    QColor hoverTextColor;
    QColor primaryColorHovered;
    QColor buttonForeground;
    QColor buttonBackground;
    QColor buttonHoveredForeground;
    QColor buttonHoveredBackground;
    QColor buttonPressedForeground;
    QColor buttonPressedBackground;
    QColor progressBarBackground;
    QColor progressBarForeground;
    QColor progressBarText;
    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Color, backgroundColor, textColor, pressedTextColor, hoverTextColor, primaryColorHovered, buttonForeground,
                                                buttonBackground, buttonHoveredForeground, buttonPressedForeground, buttonHoveredBackground,
                                                buttonPressedBackground, progressBarBackground, progressBarForeground, progressBarText);
};

class Size : public Basic
{
public:
    int fontSize{};
    int borderWidth{};
    int iconSize{};
    int normalRadius{};
    int buttonRadius{};
    int menuItemRadius{};
    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Size, fontSize, borderWidth, iconSize, normalRadius, buttonRadius);
};

class StyleConfig : public Basic
{
public:
    std::string name;
    std::string author;
    std::string mode;
    Color color;
    Size size;

    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(StyleConfig, name, author, mode, color, size);
};

class ConfigManager
{
public:
    enum ErrorCode
    {
        NoError,
        FileNotFound,
        ParseError
    };
    explicit ConfigManager();
    void setConfigPath(const std::string& path);
    static StyleConfig defaultConfig();
    ErrorCode readConfig(StyleConfig& config) const;

private:
    std::string m_configPath;
};
}  // namespace VanillaStyle
