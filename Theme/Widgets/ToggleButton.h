#pragma once
#include <QWidget>

class ToggleButtonPrivate;
class ToggleButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset)
    Q_PROPERTY(int columnWidth READ columnWidth WRITE setColumnWidth)
    Q_PROPERTY(int rowHeight READ rowHeight WRITE setRowHeight)

public:
    explicit ToggleButton(QWidget* parent = nullptr);
    explicit ToggleButton(const QStringList& list, QWidget* parent = nullptr);

    [[nodiscard]] QSize sizeHint() const override;

    void setItemList(const QStringList& list);
    [[nodiscard]] const QStringList& itemList() const;

    bool useIcon();
    void setUseIcon(bool isIcon);

    [[nodiscard]] int offset() const;
    void setOffset(int pos);

    [[nodiscard]] int columnWidth() const;
    void setColumnWidth(int width);

    [[nodiscard]] int rowHeight() const;
    void setRowHeight(int height);

signals:
    void currentItemChanged(int index);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    ToggleButtonPrivate* d_ptr;

private:
    Q_DECLARE_PRIVATE(ToggleButton);

};
