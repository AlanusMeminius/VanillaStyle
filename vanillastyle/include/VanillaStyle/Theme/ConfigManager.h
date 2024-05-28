#pragma once
#include <functional>

#include <QFile>
#include <QTextStream>

#include "Config.h"
#include "Theme.h"
#include "VanillaStyle/vglobal.h"

namespace Vanilla
{

class VANILLA_EXPORT ConfigErrorHanler
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

template<typename C>
VANILLA_EXPORT nlohmann::json loadConfigJson(const QString& path, C callback, const ConfigErrorHanler& errorHandler, const Mode mode)
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
        return nlohmann::json::parse(jsonStr);
    }
    catch (nlohmann::json::parse_error& e)
    {
        errorHandler.handleError(ConfigErrorHanler::ParseError);
        return callback(mode);
    }
}

template<typename R, typename C>
VANILLA_EXPORT R loadConfig(const QString& path, C callback, const ConfigErrorHanler& errorHandler, const Mode mode)
{
    return loadConfigJson(path, callback, errorHandler, mode).template get<R>();
}

class VANILLA_EXPORT ConfigManager
{
public:
    explicit ConfigManager() = default;

    [[nodiscard]] StyleConfig getConfig(const QString& path, Mode mode = Light);
    StyleConfig defaultConfig(Mode mode = Light);
    nlohmann::json defaultConfigJson(Mode mode = Light);

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
