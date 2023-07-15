#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    setWindowTitle("Search");
    setFixedSize(400,150);

    connect(ui->pushButton, &QPushButton::clicked, this, &SearchDialog::search);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::search()
{
    QString key = ui->lineEdit->text();
    QString type = ui->comboBox->currentText();

    emit searchRequested(key, type);
}

void SearchDialog::clearInfo()
{
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
}
void SearchDialog::closeEvent(QCloseEvent *event)
{
    clearInfo();
    QDialog::closeEvent(event);
}
