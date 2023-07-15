#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Home Page");
    setWindowIcon(QIcon("C:\\Users\\denis\\OneDrive\\Desktop\\FMI\\Qt\\Programming_Project\\icon.png"));
    setFixedSize(650,650);

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::displayAddDialog);
    connect(ui->displayButton, &QPushButton::clicked, this, &MainWindow::displayInventory);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::displayDeleteDialog);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::displayUpdateDialog);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::displaySearchDialog);
    connect(ui->expirationButton, &QPushButton::clicked, this, &MainWindow::displayExpirationDialog);
    connect(ui->recipesButton, &QPushButton::clicked, this, &MainWindow::displayRecipes);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::displayResetDialog);

    addDialog = new AddDialog(this);
    connect(addDialog, &AddDialog::addRequested, this, &MainWindow::addItem);

    deleteDialog = new DeleteDialog(this);
    connect(deleteDialog, &DeleteDialog::deleteRequested, this, &MainWindow::deleteItem);

    updateDialog = new UpdateDialog(this);
    connect(updateDialog, &UpdateDialog::updateRequested, this, &MainWindow::updateItem);

    checkDialog = new CheckDialog(this);
    connect(checkDialog, &CheckDialog::resetRequested, this, &MainWindow::resetInventory);

    expirationDialog = new ExpirationDialog(this);
    connect(expirationDialog, &ExpirationDialog::expirationRequested, this, &MainWindow::expirationDate);

    searchDialog = new SearchDialog(this);
    connect(searchDialog, &SearchDialog::searchRequested, this, &MainWindow::search);

    recipesPage = new RecipesPage();
    connect(recipesPage, &RecipesPage::recipeRequested, this, &MainWindow::checkForRecipe);

    saveDialog = new SaveDialog();
    connect(saveDialog, &SaveDialog::saveRequested, this, &MainWindow::save);
    connect(saveDialog, &SaveDialog::discardRequested, this, &MainWindow::closeWithoutSaving);

    // Load recipes and inventory from CSV files
    recipe_list.load_recipes_from_csv("C:/Users/denis/OneDrive/Desktop/FMI/Qt/Programming_Project/recipes.csv");
    inventory.load_inventory_from_csv("C:/Users/denis/OneDrive/Desktop/FMI/Qt/Programming_Project/inventory.csv");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayInventory()
{
    InventoryPage* inventoryPage = new InventoryPage(this);

    for (int row = 0; row < inventory.size(); row++) {
        const InventoryItem& item = inventory[row];
        inventoryPage->addRow(QString::number(item.id()), item.name(), item.category(), item.state(), QString::number(item.quantity()), item.expiration_date());
    }

    inventoryPage->show();
}

void MainWindow::displayAddDialog()
{
    addDialog->show();
}
void MainWindow::addItem(const QString& id, const QString& name, const QString& category, const QString& state, const QString& quantity, const QString& expirationDate)
{
    const InventoryItem& item = InventoryItem(id.toInt(),name,category,state,quantity.toDouble(),expirationDate);
    inventory.add_item(item);
}

void MainWindow::displayDeleteDialog()
{
    deleteDialog->show();
}
void MainWindow::deleteItem(const QString& id)
{
    inventory.remove_item(id.toInt());
}

void MainWindow::displayUpdateDialog()
{
    updateDialog->show();
}
void MainWindow::updateItem(const QString& initId, const QString& id, const QString& name, const QString& category, const QString& state, const QString& quantity, const QString& expirationDate)
{
    inventory.update_item(initId.toInt(), id.toInt(), name, category, state, quantity.toDouble(), expirationDate);
}

void MainWindow::displaySearchDialog()
{
    searchDialog->show();
}
void MainWindow::search(const QString& key, const QString& type)
{
    InventoryPage* inventoryPage = new InventoryPage(this);

    for (int row = 0; row < inventory.size(); row++) {
        const InventoryItem& item = inventory[row];
        if(type == "Name" && item.name() == key) inventoryPage->addRow(QString::number(item.id()), item.name(), item.category(), item.state(), QString::number(item.quantity()), item.expiration_date());
        else if(type == "Category" && item.category() == key) inventoryPage->addRow(QString::number(item.id()), item.name(), item.category(), item.state(), QString::number(item.quantity()), item.expiration_date());
    }

    inventoryPage->show();
}

void MainWindow::displayExpirationDialog()
{
    expirationDialog->show();
}
void MainWindow::expirationDate(const QString& id)
{
    QLabel* label = expirationDialog->getLabel();
    QPalette palette = label->palette();

    bool item_found = false;
    for (int i = 0; i < inventory.size(); ++i) {
        const InventoryItem& item = inventory[i];
        if (item.id() == id.toInt()) {
            item_found = true;
            break;
        }
    }
    if(item_found)
    {
        if(inventory.is_item_expired(id.toInt()))
        {
            label->setText("Expired!");
            palette.setColor(QPalette::WindowText, Qt::red);
        }
        else
        {
            label->setText("Not expired!");
            palette.setColor(QPalette::WindowText, Qt::darkGreen);
        }
    }
    else
    {
        label->setText("Item not found!");
        palette.setColor(QPalette::WindowText, Qt::darkYellow);
    }
    label->setPalette(palette);
}

void MainWindow::displayRecipes()
{
    recipesPage->show();
    QTabWidget* tabWidget = recipesPage->getTabWidget();
    recipe_list.visualize_recipes(tabWidget);
}
void MainWindow::checkForRecipe(int recipeID)
{
    recipe_list.check_sufficient_ingredients(recipeID + 1, inventory);
}

void MainWindow::displayResetDialog()
{
    checkDialog->show();
}
void MainWindow::resetInventory()
{
    inventory.reset();
}

void MainWindow::closeWithoutSaving()
{
    saveDialog->close();
    close();
}
void MainWindow::save()
{
    QFile file("C:\\Users\\denis\\OneDrive\\Desktop\\FMI\\Qt\\Programming_Project\\inventory.csv");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "ID,Name,Category,State,Quantity,Exp Date\n";
        for (int i = 0; i < inventory.size(); ++i) {
            const InventoryItem& item = inventory[i];
            out << item.id() << ',' << item.name() << ',' << item.category()
                << ',' << item.state() << ',' << item.quantity() << ','
                << item.expiration_date() << '\n';
        }

        file.close();

        close();
    } else {
        // Handle the case when the file cannot be opened
        // Display an error message or take appropriate action
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!saveDialogShown) {
        event->ignore();
        saveDialogShown = true;
        saveDialog->show();
    } else {
        event->accept();
    }
}
