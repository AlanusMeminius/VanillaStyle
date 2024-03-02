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
    QColor primaryColor;
    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Color, backgroundColor, textColor, primaryColor);
};

class Size : public Basic
{
public:
    int fontSize;
    int borderWidth;
    int iconSize;

    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Size, fontSize, borderWidth, iconSize);
};

class ThemeConfig : public Basic
{
public:
    std::string mode;
    Color color;
    Size size;

    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(ThemeConfig, mode, color, size);
};

class StyleConfig : public Basic
{
public:
    std::string name;
    std::string author;
    std::vector<ThemeConfig> themes;

    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(StyleConfig, name, author, themes);
};

class Config
{
public:
    enum ErrorCode {
        NoError,
        FileNotFound,
        ParseError
    };
    explicit Config();
    void setConfigPath(const std::string& path);
    static StyleConfig defaultConfig();
    ErrorCode readConfig(StyleConfig& config) const;
private:
    std::string m_configPath;
};
}  // namespace VanillaStyle
