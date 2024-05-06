#pragma once
#include <functional>

#include <QFile>
#include <QTextStream>

#include "Config.h"


namespace Vanilla
{

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

template<typename R, typename C>
R loadConfig(const QString& path, C callback, const ConfigErrorHanler& errorHandler, const Mode mode)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        errorHandler.handleError(ConfigErrorHanler::FileNotFound);
        return callback(mode);
    }
    QTextStream in(&file);
    std::string jsonStr = in.readAll().toStdString();
    file.close();
    try
    {
        return nlohmann::json::parse(jsonStr).get<R>();
    }
    catch (nlohmann::json::parse_error& e)
    {
        errorHandler.handleError(ConfigErrorHanler::ParseError);
        return callback(mode);
    }
}

class ConfigManager
{
public:
    explicit ConfigManager() = default;

    [[nodiscard]] StyleConfig getConfig(const QString& path, Mode mode = Light);
    StyleConfig defaultConfig(Mode mode = Light);

    void setErrorHandler(const ConfigErrorHanler::ErrorCallback& callback)
    {
        errorHandler.setErrorCallback(callback);
    }

    const nlohmann::json& getJson();

private:
    ConfigErrorHanler errorHandler;
    std::string configJsonStr;
    nlohmann::json jsonData;
};
}  // namespace Vanilla
