#include "inventorypage.h"
#include "ui_inventorypage.h"

InventoryPage::InventoryPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InventoryPage)
{
    ui->setupUi(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderLabels({"ID", "Name", "Category", "State", "Quantity", "Expiration Date"});

    setWindowTitle("Inventory");
    tableWidget->setFixedSize(650, 350);
    setFixedSize(tableWidget->size());
}

InventoryPage::~InventoryPage()
{
    delete ui;
}

void InventoryPage::addRow(const QString& id, const QString& name, const QString& category, const QString& state, const QString& quantity, const QString& expirationDate)
{
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    tableWidget->setItem(row, 0, new QTableWidgetItem(id));
    tableWidget->setItem(row, 1, new QTableWidgetItem(name));
    tableWidget->setItem(row, 2, new QTableWidgetItem(category));
    tableWidget->setItem(row, 3, new QTableWidgetItem(state));
    tableWidget->setItem(row, 4, new QTableWidgetItem(quantity));
    tableWidget->setItem(row, 5, new QTableWidgetItem(expirationDate));

    // Set item flags to make them read-only
    for (int col = 0; col < tableWidget->columnCount(); ++col) {
        QTableWidgetItem* item = tableWidget->item(row, col);
        if (item) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }
}
