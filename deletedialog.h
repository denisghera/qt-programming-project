#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr);
    ~DeleteDialog();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::DeleteDialog *ui;

private slots:
    void deleteItem();
    void clearInfo();

signals:
    void deleteRequested(const QString& id);
};

#endif // DELETEDIALOG_H
