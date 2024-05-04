#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle/Theme/Utils.h"
#include "VanillaStyle/Style/VanillaStyle.h"

namespace Vanilla
{

ConfigChangeNotifier::ConfigChangeNotifier(VanillaStyle* style, const QString& configPath)
{
    watcher.addPath(configPath);
    QFileSystemWatcher::connect(&watcher, &QFileSystemWatcher::fileChanged, [style](const QString& path) {
        style->setConfigPath(path);
    });
}

ConfigChangeNotifier::~ConfigChangeNotifier()
{
    QFileSystemWatcher::disconnect(&watcher, &QFileSystemWatcher::fileChanged, nullptr, nullptr);
}

QString getPatchProperty(const QWidget* widget)
{
    if (const auto p = widget->property("vanillaStylePatch"); p.isValid())
    {
        return p.toString();
    }
    return {};
}

}  // namespace Vanilla