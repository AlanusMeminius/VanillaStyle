#pragma once
#include "Config.h"
#include <QPalette>

class ThemeRepository {

public:
    explicit ThemeRepository();

    void init();

    QPalette palette;

    static QColor windowBackground();
    static QColor baseBackground();

private:
};
