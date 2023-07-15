#include "Headers.h"

class RecipeItem {
public:
    RecipeItem(int recipe_id, const QString& recipe_name,
               const QString& ingredient_name, double ingredient_quantity,
               const QString& ingredient_state)
        : recipe_id_(recipe_id), recipe_name_(recipe_name), ingredient_name_(ingredient_name),
        ingredient_quantity_(ingredient_quantity), ingredient_state_(ingredient_state) {}

    int recipe_id() const { return recipe_id_; }
    const QString& recipe_name() const { return recipe_name_; }
    const QString& ingredient_name() const { return ingredient_name_; }
    double ingredient_quantity() const { return ingredient_quantity_; }
    const QString& ingredient_state() const { return ingredient_state_; }

private:
    int recipe_id_;
    QString recipe_name_;
    QString ingredient_name_;
    double ingredient_quantity_;
    QString ingredient_state_;
};
