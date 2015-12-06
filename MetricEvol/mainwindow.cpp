#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "repository.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // char *path = "../test-repo/t3_sisop2/.git";
    char *path = "../test-repo/pengo-fcg/.git";
    Repository repository(path);
}

MainWindow::~MainWindow()
{
    delete ui;
}
