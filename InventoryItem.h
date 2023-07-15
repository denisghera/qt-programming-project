#include "Headers.h"

class InventoryItem {
public:
    InventoryItem(int id, const QString& name, const QString& category,
                  const QString& state, double quantity, const QString& expiration_date)
        : id_(id), quantity_(quantity), expiration_date_(expiration_date) {
        name_.push_back(name);
        category_.push_back(category);
        state_.push_back(state);
    }

    int id() const { return id_; }
    const QString& name() const { return name_; }
    const QString& category() const { return category_; }
    const QString& state() const { return state_; }
    double quantity() const { return quantity_; }
    const QString& expiration_date() const { return expiration_date_; }

    void add_name(const QString& name) { name_.push_back(name); }
    void add_category(const QString& category) { category_.push_back(category); }
    void add_state(const QString& state) { state_.push_back(state); }
    void update_item(int id, const QString& name, const QString& category,
                     const QString& state, double quantity, const QString& expiration_date) {
        name_.clear();
        category_.clear();
        state_.clear();

        id_ = id;
        name_.push_back(name);
        category_.push_back(category);
        state_.push_back(state);
        quantity_ = quantity;
        expiration_date_ = expiration_date;
    }
    bool is_expired() const {
        QDate now = QDate::currentDate();
        QDate expiration = parse_date(expiration_date_);
        return expiration < now;
    }

private:
    int id_;
    QString name_;
    QString category_;
    QString state_;
    double quantity_;
    QString expiration_date_;
    QDate parse_date(const QString& date_str) const {
        QDate date = QDate::fromString(date_str, "dd/MM/yy");

        // Check if the parsed date has a valid year (between 2000 and 2099)
        if (date.isValid() && date.year() < 2000)
            date.setDate(date.year() + 100, date.month(), date.day());

        return date;
    }
};
