#pragma once
#include <QStyle>
#include <QFileSystemWatcher>

#include "VanillaStyle/Helper/Common.h"


namespace Vanilla
{
class VanillaStyle;

struct ConfigChangeNotifier
{
    explicit ConfigChangeNotifier(VanillaStyle* style, const std::string& configPath);
    ~ConfigChangeNotifier();

    QFileSystemWatcher watcher;
};


}

