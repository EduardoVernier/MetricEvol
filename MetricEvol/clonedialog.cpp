#include "clonedialog.h"
#include "ui_clonedialog.h"
#include "repository.h"
CloneDialog::CloneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CloneDialog)
{
    ui->setupUi(this);
}

CloneDialog::~CloneDialog()
{
    delete ui;
}

void CloneDialog::on_buttonBox_accepted()
{
    QString repo_path = ui->lineEdit->text();
    char path_str[256];
    strcpy(path_str, repo_path.toStdString().c_str());

    Repository repository(path_str);
}
