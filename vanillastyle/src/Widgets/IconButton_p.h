#pragma once
#include <QSize>
#include <QColor>

#include "VanillaStyle/Widgets/IconButton.h"

namespace Vanilla {

class IconButtonPrivate
{
public:
    explicit IconButtonPrivate(IconButton* q);
    void init();

private:
    [[nodiscard]] QSize sizeHint() const;
    void paint(QPainter* painter);
    void setUpStyle();

private:
    int padding = 6;
    int totalWidth{};
    int textWidth{};
    QColor iconColor;
    QColor textColor;
    QColor buttonBorderColor;
    QFont textFont;
    Theme::TextSizeRole textSizeRole = Theme::TextSizeRole::H6;

    bool isIconFirst = false;
    bool isCustomIconColor = false;
    bool isCustomTextColor = false;
    bool isCustomFont = false;
    bool isCutomBorderColor = false;

    IconButton* const q_ptr;
    Q_DECLARE_PUBLIC(IconButton);
};


} // VanillaStyle
