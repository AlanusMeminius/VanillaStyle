#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle/Theme/Utils.h"
#include "VanillaStyle/Style/VanillaStyle.h"

namespace Vanilla
{

ConfigChangeNotifier::ConfigChangeNotifier(VanillaStyle* style, const std::string& configPath)
{
    watcher.addPath(QString::fromStdString(configPath));
    QFileSystemWatcher::connect(&watcher, &QFileSystemWatcher::fileChanged, [style](const QString& path) {
        style->setConfigPath(path.toStdString());
    });
}

ConfigChangeNotifier::~ConfigChangeNotifier()
{
    QFileSystemWatcher::disconnect(&watcher, &QFileSystemWatcher::fileChanged, nullptr, nullptr);
}

}  // namespace Vanilla