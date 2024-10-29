#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "finddialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化
    textChange = false;

    statusLabel.setMinimumWidth(150);
    statusLabel.setText("length:" + QString::number(0) + "       lines:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMinimumWidth(150);
    statusCursorLabel.setText("Ln:" + QString::number(0) + "       Col:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText("张创阳");
    ui->statusbar->addPermanentWidget(author);

    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionPaste->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionFind_triggered()
{
    FindDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionReplace_triggered()
{
    ReplaceDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionNew_triggered()
{
    // 新建文件前需确认是否保存文件
    if (!userEditConfirm())
        return;

    filePath = "";
    // 内容清空
    ui->textEdit->clear();
    // 设置title
    this->setWindowTitle("新建文本文件 - 编辑器");

    textChange = false;
}


void MainWindow::on_actionOpen_triggered()
{
    // 打开文件前需确认是否保存文件
    if (!userEditConfirm())
        return;

    // 打开文件
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", ".", tr("Text files(*.txt) ;; All (*.*)"));
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "打开文件失败");
        return;
    }

    filePath = fileName;

    // 读文件内容
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->insertPlainText(text);

    // 关闭文件
    file.close();

    // 设置title
    this->setWindowTitle(QFileInfo(fileName).absoluteFilePath());

    textChange = false;
}


void MainWindow::on_actionSave_triggered()
{
    // 判断是否打开了文件
    if (filePath.isEmpty()) {
        filePath = QFileDialog::getSaveFileName(this, "保存文件", ".", tr("Text files(*.txt)"));
        if (filePath.isEmpty()) {
            QMessageBox::warning(this, "保存失败", "未选择保存路径");
            return;
        }
    }

    QFile file(filePath);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "保存失败", "无法打开文件");
        return;
    }

    // 写入文件
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();

    // 设置title
    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
    textChange = false;
}


void MainWindow::on_actionSaveAs_triggered()
{
    // 提示用户选择另存为的文件路径和文件名
    QString fileName = QFileDialog::getSaveFileName(this, "另存为", "./untitled.txt", tr("Text files(*.txt)"));
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "保存失败", "未选择保存路径");
        return;
    }

    // 打开文件进行保存
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "保存失败", "无法打开文件");
        return;
    }

    // 将文本编辑器内容写入文件
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();

    // 更新当前文件路径和窗口标题
    filePath = fileName;
    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
}


void MainWindow::on_textEdit_textChanged()
{
    if (!textChange) {
        this->setWindowTitle("*" + this->windowTitle());
        textChange = true;
    }
}

bool MainWindow::userEditConfirm()
{
    QString path = (filePath != "") ? filePath : "无标题.txt";

    QMessageBox msg(this);
    msg.setIcon(QMessageBox::Question);
    msg.setWindowTitle("...");
    msg.setText(QString("是否将更改保存到\n") + "\"" + path + "\"?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );
    int r = msg.exec();
    switch (r) {
    case QMessageBox::Yes:
        on_actionSave_triggered();
        break;
    case QMessageBox::No:
        textChange = false;
        break;
    case QMessageBox::Cancel:
        return false;
    }
    return true;
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
    ui->actionPaste->setEnabled(true);
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
    ui->actionPaste->setEnabled(true);
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
}


void MainWindow::on_textEdit_undoAvailable(bool b)
{
    ui->actionUndo->setEnabled(b);
}


void MainWindow::on_textEdit_redoAvailable(bool b)
{
    ui->actionRedo->setEnabled(b);
}


void MainWindow::on_actionEditBackgroundColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择颜色");
    if (color.isValid()) {
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit {background-color: %1}").arg(color.name()));
    }
}


void MainWindow::on_actionFontBackgroundColor_triggered()
{

}
void MainWindow::on_actionFontColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择颜色");
    if (color.isValid()) {
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit {color: %1}").arg(color.name()));
    }

}


void MainWindow::on_actionWordWrap_triggered()
{

}













