#include "Recipe.h"
#include "QLabel"
#include "QListWidget"
#include <QRegularExpression>


void Recipe::load_recipes_from_csv(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filename;
        return;
    }

    QTextStream in(&file);

    // Skip the first line
    in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() == 5) {
            int recipe_id = fields[0].toInt();
            QString recipe_name = fields[1];
            QString ingredient_name = fields[2];
            double quantity = fields[3].toDouble();
            QString state = fields[4];

            recipe_items_.emplace_back(recipe_id, recipe_name, ingredient_name, quantity, state);
        }
    }

    file.close();
}


void Recipe::visualize_recipes(QTabWidget* tabWidget) {
    // Clear existing tabs
    tabWidget->clear();

    // Create a map to store recipes by ID
    QMap<int, QList<RecipeItem>> recipesById;

    // Group recipe items by ID
    for (const auto& recipeItem : recipe_items_) {
        recipesById[recipeItem.recipe_id()].append(recipeItem);
    }

    layouts_.resize(recipesById.size());

    // Iterate over the recipes
    for (const auto& recipeId : recipesById.keys()) {
        // Create a new tab for each recipe
        QWidget* recipeTab = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(recipeTab);
        layouts_[recipeId - 1] = layout;

        // Get the recipe items for the current ID
        const QList<RecipeItem>& recipeItems = recipesById[recipeId];

        // Create a list widget for ingredients
        QListWidget* ingredientList = new QListWidget();
        layout->addWidget(ingredientList);

        // Customize the font size for ingredient items
        QFont ingredientFont("Arial", 16);
        ingredientList->setFont(ingredientFont);

        // Populate the ingredient list
        for (const auto& recipeItem : recipeItems) {
            QString ingredientText = QString("%1 - %2 %3")
                                         .arg(recipeItem.ingredient_name())
                                         .arg(recipeItem.ingredient_quantity())
                                         .arg(recipeItem.ingredient_state());
            ingredientList->addItem(ingredientText);
        }

        // Get the recipe name from the first recipe item
        const QString& originalRecipeName = recipeItems.first().recipe_name();

        // Transform the recipe name using regular expressions
        QRegularExpression underscoreRegex("_");
        QString formattedRecipeName = originalRecipeName;
        formattedRecipeName.replace(underscoreRegex, " ");
        formattedRecipeName = formattedRecipeName.toLower();
        formattedRecipeName[0] = formattedRecipeName[0].toUpper();

        // Add the recipe tab to the tab widget
        tabWidget->addTab(recipeTab, "");
        tabWidget->setTabText(tabWidget->count() - 1, formattedRecipeName);
    }
}


void Recipe::check_sufficient_ingredients(int recipe_id, Inventory inventory) const {
    // Find the recipe items matching the given recipe ID
    QVector<const RecipeItem*> items;
    for (const auto& item : recipe_items_) {
        if (item.recipe_id() == recipe_id) {
            items.push_back(&item);
        }
    }

    bool insufficient = false;

    // Create a string to store the list of items needed
    QString itemsNeeded;

    // Check if there are enough ingredients in the inventory
    for (const auto& item : items) {
        const QString& ingredient_name = item->ingredient_name();
        const QString& ingredient_state = item->ingredient_state();
        double ingredient_quantity = item->ingredient_quantity();

        // Search for matching items in the inventory by name
        const QVector<InventoryItem*> matching_items = inventory.search_by_name(ingredient_name);

        double total_quantity = 0.0;
        for (const auto& matching_item : matching_items) {
            if (!matching_item->is_expired()) {
                total_quantity += matching_item->quantity();
            }
        }

        // Check if the total quantity is sufficient
        if (total_quantity < ingredient_quantity) {
            insufficient = true;
            double additional_quantity_needed = ingredient_quantity - total_quantity;

            // Append the item and quantity to the string
            itemsNeeded += QString("%1 - %2 %3\n")
                               .arg(ingredient_name)
                               .arg(additional_quantity_needed)
                               .arg(ingredient_state);
        }
    }

    QVBoxLayout* layout = layouts_[recipe_id - 1];
    QLabel* lastLabel = nullptr;

    // Find the last added label in the QVBoxLayout
    for (int i = layout->count() - 1; i >= 0; i--) {
        if (QLabel* label = qobject_cast<QLabel*>(layout->itemAt(i)->widget())) {
            lastLabel = label;
            break;
        }
    }

    // Remove the last added label from the QVBoxLayout
    if (lastLabel) {
        layout->removeWidget(lastLabel);
        delete lastLabel;
    }

    if(insufficient) {
        QLabel* itemsNeededLabel = new QLabel();
        QFont labelFont("Arial", 12, QFont::Bold);  // Customize the font size and weight
        itemsNeededLabel->setFont(labelFont);
        itemsNeededLabel->setStyleSheet("color: red;");  // Set the text color to red
        itemsNeededLabel->setText("You still need:\n" + itemsNeeded);

        // Add the label to the QVBoxLayout
        layouts_[recipe_id-1]->addWidget(itemsNeededLabel);
    }
    else {
        QLabel* sufficientLabel = new QLabel();
        QFont labelFont("Arial", 13, QFont::Bold);  // Customize the font size and weight
        sufficientLabel->setFont(labelFont);
        sufficientLabel->setStyleSheet("color: darkGreen;");
        sufficientLabel->setText("There are enough ingredients :)");
        layouts_[recipe_id-1]->addWidget(sufficientLabel);
    }
}

