#pragma once
#include <QMenu>
#include <QToolButton>
#include "VanillaStyle/vglobal.h"

namespace Vanilla
{
class VanillaStyle;

class VANILLA_EXPORT MenuEventFilter : public QObject
{
public:
    explicit MenuEventFilter(QMenu* menu);

    bool eventFilter(QObject* watchedObject, QEvent* evt) override;

private:
    QMenu* _menu{nullptr};
};

class VANILLA_EXPORT LineEditButtonEventFilter : public QObject
{
public:
    explicit LineEditButtonEventFilter(QToolButton* button, VanillaStyle& style);
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    VanillaStyle& m_style;
    QToolButton* m_button{ nullptr };
};
}  // namespace VanillaStyle
