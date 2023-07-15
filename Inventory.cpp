#include "Inventory.h"

void Inventory::remove_item(int id) {
    for (auto it = items_.begin(); it != items_.end(); ++it) {
        if (it->id() == id) {
            items_.erase(it);
            return;
        }
    }
}

void Inventory::reset() {
    items_.clear();
}

const QVector<InventoryItem*> Inventory::search_by_name(const QString& name) {
    QVector<InventoryItem*> matching_items;
    for (auto& item : items_) {
        if (item.name() == name) {
            matching_items.push_back(&item);
        }
    }
    return matching_items;
}

const QVector<InventoryItem*> Inventory::search_by_category(const QString& category) {
    QVector<InventoryItem*> matching_items;
    for (auto& item : items_) {
        if (item.category() == category) {
            matching_items.push_back(&item);
        }
    }
    return matching_items;
}

void Inventory::update_item(int initId, int id, const QString& name, const QString& category,
                            const QString& state, double quantity, const QString& expiration_date) {
    for (auto& item : items_) {
        if (item.id() == initId) {
            item.update_item(id, name, category, state, quantity, expiration_date);
            return;
        }
    }
}

bool Inventory::is_item_expired(int id) const {
    for (const auto& item : items_) {
        if (item.id() == id) {
            return item.is_expired();
        }
    }
    return false;  // Item not found in the inventory
}

void Inventory::load_inventory_from_csv(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filename;
        return;
    }

    QTextStream in(&file);

    QString header_line = in.readLine();

    do {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() >= 6) {
            int id = fields[0].toInt();
            QString name = fields[1];
            QString category = fields[2];
            QString state = fields[3];
            double quantity = fields[4].toDouble();
            QString expiration_date = fields[5];

            InventoryItem item(id, name, category, state, quantity, expiration_date);
            items_.emplace_back(item);
        }
    } while (!in.atEnd());

    file.close();
}
