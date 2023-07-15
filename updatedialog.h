#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include "QTableWidget"

namespace Ui {
class UpdateDialog;
}

class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateDialog(QWidget *parent = nullptr);
    ~UpdateDialog();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::UpdateDialog *ui;

private slots:
    void updateItem();
    void clearInfo();

signals:
    void updateRequested(const QString& initId, const QString& id, const QString& name, const QString& category, const QString& state, const QString& quantity, const QString& expirationDate);
};

#endif // UPDATEDIALOG_H
