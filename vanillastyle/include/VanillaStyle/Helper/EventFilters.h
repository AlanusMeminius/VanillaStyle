#pragma once
#include <QMenu>

namespace VanillaStyle
{

class MenuEventFilter : public QObject {
public:
    MenuEventFilter(QMenu* menu);

    bool eventFilter(QObject* watchedObject, QEvent* evt) override;

private:
    QMenu* _menu{ nullptr };
};

}  // namespace VanillaStyle
