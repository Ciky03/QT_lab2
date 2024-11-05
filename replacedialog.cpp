#include "replacedialog.h"
#include "ui_replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent, QPlainTextEdit *pTextEdit)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);

    textEdit = pTextEdit;
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}
