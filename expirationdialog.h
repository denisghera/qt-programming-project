#ifndef EXPIRATIONDIALOG_H
#define EXPIRATIONDIALOG_H

#include "qlabel.h"
#include <QDialog>

namespace Ui {
class ExpirationDialog;
}

class ExpirationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpirationDialog(QWidget *parent = nullptr);
    ~ExpirationDialog();

    QLabel* getLabel() const;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::ExpirationDialog *ui;

private slots:
    void checkExpirationDate();
    void clearInfo();

signals:
    void expirationRequested(const QString &id);
};

#endif // EXPIRATIONDIALOG_H
