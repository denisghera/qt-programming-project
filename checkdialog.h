#ifndef CHECKDIALOG_H
#define CHECKDIALOG_H

#include <QDialog>

namespace Ui {
class CheckDialog;
}

class CheckDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckDialog(QWidget *parent = nullptr);
    ~CheckDialog();

private:
    Ui::CheckDialog *ui;

private slots:
    void reset();

signals:
    void resetRequested();
};

#endif // CHECKDIALOG_H
