#pragma once

#include <QStyleOption>
#include <QPalette>
#include <QFont>
#include <unordered_set>

#include "Config.h"
#include "Mode.h"
#include "VanillaStyle/vglobal.h"

namespace Vanilla
{
class PatchHelper;
}
namespace Vanilla
{
class ConfigManager;

class VANILLA_EXPORT Theme
{
public:
    enum State
    {
        Normal = 0x00000000,
        Hover = 0x00000001,
        Press = 0x00000002,
        Disabled = 0x00000003,
        StateBase = 0x000000f0,

        Flag = 0x000000ff,
        Selected = 0x00000100,
        Focus = 0x00000200,
        Checked = 0x00000400,
        FlagBase = 0xf00000,
    };
    Q_DECLARE_FLAGS(StateFlags, State)

    static State state(const QStyleOption* option);
    static StateFlags flags(const QStyleOption* option);

    explicit Theme();
    void setConfig(const QString& configPath);
    void setPatchHelper(const std::shared_ptr<PatchHelper>& helper);
    void setMode(Mode mode);

    void update();
    [[nodiscard]] bool isEnableHotReload() const;

    void updatePalette();
    void initFont();
    [[nodiscard]] QPalette standardPalette() const;

    QFont getFont(TextSizeRole sizeRole);

    [[nodiscard]] int getSize(SizeRole sizeRole) const;

    QColor getColor(const QStyleOption* option, ColorRole role) const;
    QColor createColor(State state, const QStyleOption* option, ColorRole role) const;
    QColor createColor(StateFlags flags, const QStyleOption* option, ColorRole role) const;
    [[nodiscard]] QColor customColor(ColorRole role) const;

    [[nodiscard]] static QString checkIconFile(const std::string& path);
    [[nodiscard]] QString getIconPath(IconRole role) const;
    QString getCachedIcon(const QString&, QColor color);
    [[nodiscard]] bool getIconsColorizeMode() const;
    [[nodiscard]] ProgressMode getProgressMode() const;

    void setPatchConfig(const std::string& propertyValue);
    [[nodiscard]] std::string getPatchKey() const;

private:
    QPalette palette;

    QFont fontRegular;
    QFont fontFixed;
    QFont fontBold;

    QFont fontH1;
    QFont fontH2;
    QFont fontH3;
    QFont fontH4;
    QFont fontH5;
    QFont fontH6;

    std::shared_ptr<ConfigManager> configManager;
    std::shared_ptr<PatchHelper> patchHelper;
    StyleConfig styleConfig;

    std::unordered_map<QString, QString> iconData;
};
}  // namespace Vanilla