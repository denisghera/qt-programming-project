#include "InventoryItem.h"

class Inventory {
public:
    Inventory() { items_.clear(); }
    void load_inventory_from_csv(const QString& filename);
    void add_item(const InventoryItem& item) { items_.emplace_back(item); }
    void remove_item(int id);
    void reset();
    void update_item(int initId, int id, const QString& name, const QString& category,
                     const QString& state, double quantity, const QString& expiration_date);

    const QVector<InventoryItem*> search_by_name(const QString& name);
    const QVector<InventoryItem*> search_by_category(const QString& name);

    int size() const { return items_.size(); }
    const InventoryItem& operator[](int index) const { return items_[index]; }
    bool is_item_expired(int id) const;

private:
    QVector<InventoryItem> items_;
};
