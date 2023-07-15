#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::AddDialog *ui;

private slots:
    void addItem();
    void clearInfo();

signals:
    void addRequested(const QString& id, const QString& name, const QString& category, const QString& state, const QString& quantity, const QString& expirationDate);
};

#endif // ADDDIALOG_H
