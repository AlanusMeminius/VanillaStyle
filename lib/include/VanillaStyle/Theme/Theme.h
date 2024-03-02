#pragma once
#include "Config.h"
#include "Utils.h"
#include <QPalette>
#include <QStyleOption>
namespace VanillaStyle
{
class Theme
{
public:
    explicit Theme();
    void setConfig(const std::string &configPath);
    void init();

    QPalette palette;

    QBrush getBrush(const QStyleOption* option, const QBrush& brush, QPalette::ColorGroup group, QPalette::ColorRole role);
    QBrush getBrush(State state, const QStyleOption *option, const QBrush &brush, QPalette::ColorGroup group, QPalette::ColorRole role);
    void getColor();

private:
    std::shared_ptr<Config> m_config;
};
}