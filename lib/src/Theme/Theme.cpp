#include <utility>

#include "VanillaStyle/Theme/Theme.h"
namespace VanillaStyle
{
Theme::Theme()
    : m_config(std::make_shared<Config>())
{
}
void Theme::setConfig(const std::string& configPath)
{
    m_config->setConfigPath(configPath);
}
QBrush Theme::getBrush(const QStyleOption* option, const QBrush& brush, QPalette::ColorGroup group, QPalette::ColorRole role)
{
    getBrush(stateAdapter(option), option, brush, group, role);
}
QBrush getBrush(State state, const QStyleOption* option, const QBrush& brush, QPalette::ColorGroup group, QPalette::ColorRole role)
{
    QColor color = brush.color();
    if (color.isValid())
    {
        return brush;
    }
}

void Theme::getColor()
{
}
QBrush Theme::getBrush(State state, const QStyleOption* option, const QBrush& brush, QPalette::ColorGroup group, QPalette::ColorRole role)
{
    return QBrush();
}

}  // namespace VanillaStyle