#include "updatedialog.h"
#include "ui_updatedialog.h"

UpdateDialog::UpdateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);
    setWindowTitle("Update");
    ui->dateEdit->setDate(QDate::currentDate());
    setFixedSize(550,250);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &UpdateDialog::updateItem);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &UpdateDialog::close);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &UpdateDialog::clearInfo);
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}

void UpdateDialog::updateItem()
{
    QString init_id = ui->lineEdit_4->text();
    QString id = ui->lineEdit->text();
    QString name = ui->lineEdit_2->text();
    QString category = ui->lineEdit_3->text();
    QString state = ui->comboBox->currentText();
    QString quantity = ui->lineEdit_5->text();
    QString expiration_date = ui->dateEdit->text();

    emit updateRequested(init_id,id,name,category,state,quantity,expiration_date);

    close();
}

void UpdateDialog::clearInfo()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
}

void UpdateDialog::closeEvent(QCloseEvent *event)
{
    clearInfo();
    QDialog::closeEvent(event);
}
