#pragma once
#include "Config.h"
#include <functional>

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

class ConfigManager
{
public:
    explicit ConfigManager() = default;

    [[nodiscard]] StyleConfig getConfig(const std::string& path) const;
    static StyleConfig defaultConfig();

    void setErrorHandler(const ConfigErrorHanler::ErrorCallback& callback)
    {
        errorHandler.setErrorCallback(callback);
    }

private:
    ConfigErrorHanler errorHandler;
};
}  // namespace Vanilla
