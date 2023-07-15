#include "checkdialog.h"
#include "ui_checkdialog.h"

CheckDialog::CheckDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckDialog)
{
    ui->setupUi(this);
    setWindowTitle("Reset");
    setFixedSize(400,150);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CheckDialog::reset);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &CheckDialog::close);
}

CheckDialog::~CheckDialog()
{
    delete ui;
}

void CheckDialog::reset()
{
    emit resetRequested();
}
