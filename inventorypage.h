#ifndef INVENTORYPAGE_H
#define INVENTORYPAGE_H

#include <QMainWindow>
#include <QTableWidget>

namespace Ui {
class InventoryPage;
}

class InventoryPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit InventoryPage(QWidget *parent = nullptr);
    ~InventoryPage();
    void addRow(const QString&, const QString& name, const QString& category, const QString& state, const QString&, const QString& expirationDate);

private:
    Ui::InventoryPage *ui;
    QTableWidget* tableWidget;
};

#endif // INVENTORYPAGE_H
