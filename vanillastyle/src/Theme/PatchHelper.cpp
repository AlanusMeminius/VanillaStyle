
#include <QWidget>

#include "VanillaStyle/Theme/PatchHelper.h"
#include "VanillaStyle/Helper/Common.h"
#include "VanillaStyle/Theme/Utils.h"
#include "VanillaStyle/Theme/Config.h"
#include "VanillaStyle/Theme/Theme.h"

namespace Vanilla
{
PatchHelper& PatchHelper::global()
{
    static PatchHelper instance;
    return instance;
}

void PatchHelper::init(const std::vector<PatchConfig>& patches)
{
    clear();
    if (patches.empty())
    {
        return;
    }
    std::vector<QString> widgetStrings;
    std::vector<QString> propertyStrings;

    for (const auto& item : patches)
    {
        if (item.enable)
        {
            widgetStrings.emplace_back(QString::fromStdString(item.widgetType));
            propertyStrings.emplace_back(QString::fromStdString(item.widgetType + ":" + item.propertyValue));
        }
    }

    widgets.insert(widgetStrings.begin(), widgetStrings.end());
    properties.insert(propertyStrings.begin(), propertyStrings.end());
}

void PatchHelper::patchTheme(const QString& propertyValue, const std::shared_ptr<Theme>& theme)
{
    if (m_patchThemes.contains(propertyValue))
    {
        return;
    }
    auto patch = std::make_shared<Theme>(*theme);
    patch->setPatchConfig(propertyValue.toStdString());
    m_patchThemes.emplace(propertyValue, patch);
}

const std::shared_ptr<Theme>& PatchHelper::getPatchTheme(const QString& propertyName)
{
    return m_patchThemes.contains(propertyName) ? m_patchThemes.at(propertyName) : defaultTheme;
}

const std::shared_ptr<Theme>& PatchHelper::getPatchTheme(const QWidget* widget, const std::shared_ptr<Theme>& originalTheme)
{
    const auto className = widget->metaObject()->className();
    if (!widgets.contains(QString(className)))
    {
        return originalTheme;
    }
    const auto propertyValue = getPatchProperty(widget);
    if (propertyValue.isEmpty())
    {
        return originalTheme;
    }
    if (properties.contains(QString(className) + ":" + propertyValue))
    {
        patchTheme(propertyValue, originalTheme);
        return getPatchTheme(propertyValue);
    }
    return originalTheme;
}

void PatchHelper::clear()
{
    widgets.clear();
    properties.clear();
    m_patchThemes.clear();
}

}  // namespace Vanilla