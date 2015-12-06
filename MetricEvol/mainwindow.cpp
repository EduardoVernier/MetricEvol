#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_OpenRepoMenuBar_triggered()
{
    QString fileName = QFileDialog::getExistingDirectory(this,
        tr("Find repository folder"),"../test-repo/", QFileDialog::ShowDirsOnly);

    fileName = fileName + "/.git";
    char path[256];
    strcpy(path, fileName.toStdString().c_str());

    Repository repository(path);
}
