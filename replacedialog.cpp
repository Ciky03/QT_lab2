#include "replacedialog.h"
#include "ui_replacedialog.h"
#include<QMessageBox>

ReplaceDialog::ReplaceDialog(QWidget *parent, QPlainTextEdit *textEdit)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);

    pTextEdit = textEdit;

    ui->rbDown->setChecked(true);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_btFindNext_clicked()
{
    // 获取输入的要查找的文本
    QString target = ui->replaceTargetEdit->text();
    if (target == "" || pTextEdit == nullptr)
        return;

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


void ReplaceDialog::on_btReplace_clicked()
{
    // 获取输入的要查找的文本
    QString target = ui->replaceTargetEdit->text();
    // 获取输入的替代文本
    QString to = ui->replaceEdit->text();

    if ((pTextEdit != nullptr) && (target != "") && (to != "")) {
        QString selText = pTextEdit->textCursor().selectedText();

        //检查区分大小写
        Qt::CaseSensitivity caseSensitive = ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

        // 根据大小写敏感性来判断替换
        if (selText.compare(target, caseSensitive) == 0) {
            // 替换选中的文本
            pTextEdit->insertPlainText(to);
        }
    }

    on_btFindNext_clicked();
}


void ReplaceDialog::on_btReplaceAll_clicked()
{
    // 获取输入的要查找的文本
    QString target = ui->replaceTargetEdit->text();
    // 获取输入的替代文本
    QString to = ui->replaceEdit->text();

    if ((pTextEdit != nullptr) && (target != "") && (to != "")) {
        QString text = pTextEdit->toPlainText();

        text.replace(target, to, ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

        pTextEdit->clear();

        pTextEdit->insertPlainText(text);
    }

}


void ReplaceDialog::on_btCancel_clicked()
{
    accept();
}

