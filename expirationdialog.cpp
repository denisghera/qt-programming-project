#include "expirationdialog.h"
#include "ui_expirationdialog.h"

ExpirationDialog::ExpirationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpirationDialog)
{
    ui->setupUi(this);
    setWindowTitle("Expiration Date");
    setFixedSize(400,150);

    connect(ui->pushButton, &QPushButton::clicked, this, &ExpirationDialog::checkExpirationDate);
}

ExpirationDialog::~ExpirationDialog()
{
    delete ui;
}

QLabel* ExpirationDialog::getLabel() const
{
    return ui->label_2;
}

void ExpirationDialog::checkExpirationDate()
{
    QString id = ui->lineEdit->text();

    emit expirationRequested(id);
}

void ExpirationDialog::clearInfo()
{
    ui->lineEdit->clear();
    ui->label_2->clear();
}
void ExpirationDialog::closeEvent(QCloseEvent *event)
{
    clearInfo();
    QDialog::closeEvent(event);
}
