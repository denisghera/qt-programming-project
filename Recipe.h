#include "RecipeItem.h"
#include "Inventory.h"
#include "QVBoxLayout"

class Recipe {
public:
    void load_recipes_from_csv(const QString& filename);
    void visualize_recipes(QTabWidget* tabWidget);
    void check_sufficient_ingredients(int recipe_id, Inventory inventory) const;
private:
    QVector<RecipeItem> recipe_items_;
    QVector<QVBoxLayout*> layouts_;
};

