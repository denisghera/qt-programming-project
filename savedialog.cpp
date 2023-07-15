#include "savedialog.h"
#include "ui_savedialog.h"

SaveDialog::SaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
    setWindowTitle("Save?");
    setFixedSize(400,150);
    setWindowIcon(QIcon("C:\\Users\\denis\\OneDrive\\Desktop\\FMI\\Qt\\Programming_Project\\icon.png"));

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SaveDialog::save);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SaveDialog::discard);
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

void SaveDialog::save()
{
    emit saveRequested();
}
void SaveDialog::discard()
{
    emit discardRequested();
}
