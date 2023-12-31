#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = nullptr);
    ~SaveDialog();

private:
    Ui::SaveDialog *ui;

private slots:
    void save();
    void discard();

signals:
    void saveRequested();
    void discardRequested();
};

#endif // SAVEDIALOG_H
