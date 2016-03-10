#ifndef CLONEDIALOG_H
#define CLONEDIALOG_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class CloneDialog;
}

class CloneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CloneDialog(QWidget *parent = 0);
    ~CloneDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CloneDialog *ui;
};

#endif // CLONEDIALOG_H
