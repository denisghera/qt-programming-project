#include "recipespage.h"
#include "ui_recipespage.h"

RecipesPage::RecipesPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RecipesPage)
{
    ui->setupUi(this);
    setWindowTitle("Recipes List");
    setFixedSize(310, 370);
    setWindowIcon(QIcon("C:\\Users\\denis\\OneDrive\\Desktop\\FMI\\Qt\\Programming_Project\\icon.png"));

    connect(ui->pushButton, &QPushButton::clicked, this, &RecipesPage::recipes);
}

RecipesPage::~RecipesPage()
{
    delete ui;
}

QTabWidget* RecipesPage::getTabWidget()
{
    return ui->tabWidget;
}

void RecipesPage::recipes()
{
    emit recipeRequested(ui->tabWidget->currentIndex());
}
