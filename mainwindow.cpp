#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "finddialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusLabel.setMinimumWidth(150);
    statusLabel.setText("length:" + QString::number(0) + "       lines:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMinimumWidth(150);
    statusCursorLabel.setText("Ln:" + QString::number(0) + "       Col:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText("张创阳");
    ui->statusbar->addPermanentWidget(author);

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
    // 内容清空
    ui->textEdit->clear();
    // 设置title
    this->setWindowTitle("新建文本文件 - 编辑器");
}


void MainWindow::on_actionOpen_triggered()
{
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

}

