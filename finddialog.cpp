#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent, QPlainTextEdit* textEdit)
    : QDialog(parent)
    , ui(new Ui::FindDialog)
{
    ui->setupUi(this);

    pTextEdit = textEdit;
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_btFindNext_clicked()
{

}


void FindDialog::on_btCancel_clicked()
{
    accept();
}

