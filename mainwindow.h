#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "inventorypage.h"
#include "deletedialog.h"
#include "adddialog.h"
#include "updatedialog.h"
#include "checkdialog.h"
#include "expirationdialog.h"
#include "searchdialog.h"
#include "recipespage.h"
#include "savedialog.h"
#include "Recipe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Inventory inventory;
    Recipe recipe_list;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    DeleteDialog *deleteDialog;
    AddDialog *addDialog;
    UpdateDialog *updateDialog;
    CheckDialog *checkDialog;
    ExpirationDialog *expirationDialog;
    SearchDialog *searchDialog;
    RecipesPage *recipesPage;
    SaveDialog *saveDialog;
    bool saveDialogShown = false;

private slots:
    void displayInventory();
    void displayAddDialog();
    void addItem(const QString& id, const QString& name, const QString& category, const QString& state, const QString& quantity, const QString& expirationDate);
    void displayDeleteDialog();
    void deleteItem(const QString& id);
    void displayUpdateDialog();
    void updateItem(const QString& initId, const QString& id, const QString& name, const QString& category, const QString& state, const QString& quantity, const QString& expirationDate);
    void displaySearchDialog();
    void search(const QString& key, const QString& type);
    void displayExpirationDialog();
    void expirationDate(const QString& id);
    void displayRecipes();
    void checkForRecipe(int recipe_id);
    void displayResetDialog();
    void resetInventory();
    void save();
    void closeWithoutSaving();
};
#endif // MAINWINDOW_H
