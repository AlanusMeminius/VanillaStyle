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
            QString colorString = QString::fromStdString(j.get<std::string>());
            if (colorString.startsWith("#"))
            {
                colorString.replace("#", "0x");
            }
            color = QColor(colorString.toUInt(nullptr, 16));
        }
        catch (const std::exception& e)
        {
            color = QColor(Qt::black);
        }
    }
};
}  // namespace nlohmann

namespace Vanilla
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
    QColor lineEditFocusOutline;
    QColor lineEditOutline;
    QColor iconLabelText;
    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Color, backgroundColor, textColor, pressedTextColor, hoverTextColor, primaryColorHovered, buttonForeground,
                                                buttonBackground, buttonHoveredForeground, buttonPressedForeground, buttonHoveredBackground,
                                                buttonPressedBackground, progressBarBackground, progressBarForeground, progressBarText, lineEditFocusOutline,
                                                lineEditOutline, iconLabelText);
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

class Icons : public Basic
{
public:
    std::string upArrow;
    std::string downArrow;
    std::string progressIndicator;
    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Icons, upArrow, downArrow, progressIndicator);
};

class StyleConfig : public Basic
{
public:
    std::string name;
    std::string author;
    std::string mode;
    Color color;
    Size size;
    Icons icons;

    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(StyleConfig, name, author, mode, color, size, icons);
};

class ConfigErrorHanler
{
public:
    enum ErrorCode
    {
        NoError,
        FileNotFound,
        ParseError
    };

    using ErrorCallback = std::function<void(const ErrorCode&)>;

    void handleError(const ErrorCode& errorType) const
    {
        if (errorCallback)
        {
            errorCallback(errorType);
        }
    }

    void setErrorCallback(const ErrorCallback& callback)
    {
        errorCallback = callback;
    }

private:
    ErrorCallback errorCallback;
};

class ConfigManager
{
public:
    explicit ConfigManager() = default;

    static StyleConfig defaultConfig();
    StyleConfig getConfig(const std::string& path) const;

public:
    ConfigErrorHanler errorHandler;
};
}  // namespace Vanilla
