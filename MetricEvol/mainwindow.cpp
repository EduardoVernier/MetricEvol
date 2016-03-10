#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clonedialog.h"
#include "repository.h"
#include "QFileDialog"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->setNativeMenuBar(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openRepoMenuBar_triggered()
{
    QString fileName = QFileDialog::getExistingDirectory(this,
        tr("Find repository folder"),"../test-repo/", QFileDialog::ShowDirsOnly);

    fileName = fileName + "/.git";
    char path[256];
    strcpy(path, fileName.toStdString().c_str());

    Repository repository(path, this);
}

void MainWindow::on_cloneRepoMenuBar_triggered()
{
    CloneDialog cloneDialog;
    cloneDialog.setModal(true);
    cloneDialog.exec();
}

void MainWindow::write_to_textbox(QString txt)
{
    ui->textbox->append(txt);
}
