#pragma once
#include <QMenu>

namespace Vanilla
{

class MenuEventFilter : public QObject {
public:
    explicit MenuEventFilter(QMenu* menu);

    bool eventFilter(QObject* watchedObject, QEvent* evt) override;

private:
    QMenu* _menu{ nullptr };
};

}  // namespace VanillaStyle
