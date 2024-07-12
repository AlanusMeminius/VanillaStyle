#pragma once
#include <QStyle>
#include <QFileSystemWatcher>

#include "VanillaStyle/Helper/Common.h"

namespace Vanilla
{
class VanillaStyle;

struct VANILLA_EXPORT ConfigChangeNotifier
{
    explicit ConfigChangeNotifier(VanillaStyle* style, const QString& configPath);
    ~ConfigChangeNotifier();

    QFileSystemWatcher watcher;
};

QString getPatchProperty(const QWidget* widget);

}  // namespace Vanilla
