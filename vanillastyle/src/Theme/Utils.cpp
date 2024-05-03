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

}  // namespace Vanilla