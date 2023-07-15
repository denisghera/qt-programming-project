#ifndef RECIPESPAGE_H
#define RECIPESPAGE_H

#include <QMainWindow>

namespace Ui {
class RecipesPage;
}

class RecipesPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit RecipesPage(QWidget *parent = nullptr);
    ~RecipesPage();
    QTabWidget* getTabWidget();

private:
    Ui::RecipesPage *ui;

private slots:
    void recipes();

signals:
    void recipeRequested(int recipe_id);
};

#endif // RECIPESPAGE_H
