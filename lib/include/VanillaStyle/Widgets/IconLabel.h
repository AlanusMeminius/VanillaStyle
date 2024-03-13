#pragma once
#include <QWidget>
#include <QString>
namespace VanillaStyle
{

class IconLabelPrivate;
class IconLabel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
    Q_PROPERTY(Qt::LayoutDirection dirction READ dirction WRITE setDirction NOTIFY dirctionChanged)
public:
    explicit IconLabel(QWidget* parent = nullptr);
    explicit IconLabel(const QIcon& icon, QWidget* parent = nullptr);
    explicit IconLabel(const QString& label, QWidget* parent = nullptr);
    explicit IconLabel(const QIcon& icon, const QString& label, QWidget* parent = nullptr);

    [[nodiscard]] QSize sizeHint() const override;

    [[nodiscard]] const QString& label() const;
    void setLabel(const QString& label);
    Q_SIGNAL void labelChanged();

    [[nodiscard]] const QIcon& icon() const;
    void setIcon(const QIcon& icon);
    Q_SIGNAL void iconChanged();

    [[nodiscard]] const QSize& iconSize() const;
    void setIconSize(const QSize& iconSize);
    Q_SIGNAL void iconSizeChanged();

    [[nodiscard]] const Qt::LayoutDirection& dirction() const;
    void setDirction(const Qt::LayoutDirection& dirction);
    Q_SIGNAL void dirctionChanged();

protected:
    void paintEvent(QPaintEvent* event) override;

    IconLabelPrivate* d_ptr;

private:
    Q_DECLARE_PRIVATE(IconLabel);
};

}  // namespace VanillaStyle
