#include "deletedialog.h"
#include "ui_deletedialog.h"

DeleteDialog::DeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);
    setWindowTitle("Delete");
    setFixedSize(400,150);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DeleteDialog::deleteItem);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &DeleteDialog::close);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &DeleteDialog::clearInfo);

}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}

void DeleteDialog::deleteItem()
{
    QString id = ui->lineEdit->text();

    emit deleteRequested(id);

    clearInfo();
}

void DeleteDialog::clearInfo()
{
    ui->lineEdit->clear();
}
void DeleteDialog::closeEvent(QCloseEvent *event)
{
    clearInfo();
    QDialog::closeEvent(event);
}


