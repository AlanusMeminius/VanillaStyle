#pragma once
#include <QMenu>

namespace Vanilla
{

class VANILLA_EXPORT MenuEventFilter : public QObject {
public:
    explicit MenuEventFilter(QMenu* menu);

    bool eventFilter(QObject* watchedObject, QEvent* evt) override;

private:
    QMenu* _menu{ nullptr };
};

}  // namespace VanillaStyle
