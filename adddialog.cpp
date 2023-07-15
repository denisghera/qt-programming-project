#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    setWindowTitle("Add");
    setFixedSize(550,250);
    ui->dateEdit->setDate(QDate::currentDate());

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddDialog::addItem);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddDialog::close);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddDialog::clearInfo);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::addItem()
{
    QString id = ui->lineEdit->text();
    QString name = ui->lineEdit_2->text();
    QString category = ui->lineEdit_3->text();
    QString state = ui->comboBox->currentText();
    QString quantity = ui->lineEdit_5->text();
    QString expiration_date = ui->dateEdit->text();

    emit addRequested(id,name,category,state,quantity,expiration_date);

    clearInfo();
}

void AddDialog::clearInfo()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
}

void AddDialog::closeEvent(QCloseEvent *event)
{
    clearInfo();
    QDialog::closeEvent(event);
}
