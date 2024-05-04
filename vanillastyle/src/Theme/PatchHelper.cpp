
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
    for (const auto& item : patches)
    {
        if (item.enable)
        {
            widgets.emplace(QString::fromStdString(item.widgetType));
            properties.emplace(QString::fromStdString(item.widgetType + ":" + item.propertyValue));
        }
    }
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
    if (m_patchThemes.contains(propertyName))
    {
        return m_patchThemes.at(propertyName);
    }
    static std::shared_ptr<Theme> defaultTheme;
    return defaultTheme;
}

const std::shared_ptr<Theme>& PatchHelper::getPatchTheme(const QWidget* widget, const std::shared_ptr<Theme>& theme)
{
    const auto className = widget->metaObject()->className();
    if (!widgets.contains(QString(className)))
    {
        return theme;
    }
    const auto propertyValue = getPatchProperty(widget);
    if (propertyValue.isEmpty())
    {
        return theme;
    }
    if (properties.contains(QString(className) + ":" + propertyValue))
    {
        patchTheme(propertyValue, theme);
        return getPatchTheme(propertyValue);
    }
    return theme;
}


}