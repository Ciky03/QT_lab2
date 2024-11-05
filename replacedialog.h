#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = nullptr, QPlainTextEdit * textEdit = nullptr);
    ~ReplaceDialog();

private:
    Ui::ReplaceDialog *ui;

    QPlainTextEdit *textEdit;
};

#endif // REPLACEDIALOG_H
