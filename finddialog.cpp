#include "finddialog.h"
#include "ui_finddialog.h"
#include<QMessageBox>

FindDialog::FindDialog(QWidget *parent, QPlainTextEdit* textEdit)
    : QDialog(parent)
    , ui(new Ui::FindDialog)
{
    ui->setupUi(this);

    pTextEdit = textEdit;

    ui->rbDown->setChecked(true);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_btFindNext_clicked()
{
    // 获取输入的要查找的文本
    QString target = ui->searchText->text();

    // 文本框里所有的内容
    QString text = pTextEdit->toPlainText();

    // 获取当前光标
    QTextCursor c = pTextEdit->textCursor();

    int index = -1;

    if (ui->rbUp->isChecked()) {
        // 从当前文本开始,向前获取查找文本的下标
        index = text.lastIndexOf(target, c.position() - target.length() - 1,
                                 ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0) {
            // 修改光标位置
            c.setPosition(index + target.length());
            // 设置光标高亮范围
            c.setPosition(index, QTextCursor::KeepAnchor);
            // 设置文本框光标位置
            pTextEdit->setTextCursor(c);
        }
    } else {
        // 从当前文本开始,向后获取查找文本的下标
        index = text.indexOf(target, c.position(), ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0) {
            // 修改光标位置
            c.setPosition(index);
            // 设置光标高亮范围
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);
            // 设置文本框光标位置
            pTextEdit->setTextCursor(c);
        }
    }

    if (index < 0) {
        QMessageBox msg(this);
        msg.setWindowTitle(QString("查找"));
        msg.setText(QString("找不到") + target);
        msg.setWindowFlag(Qt::Drawer);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}


void FindDialog::on_btCancel_clicked()
{
    accept();
}

