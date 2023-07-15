#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::SearchDialog *ui;

private slots:
    void search();
    void clearInfo();

signals:
    void searchRequested(const QString& key, const QString& type);
};

#endif // SEARCHDIALOG_H
