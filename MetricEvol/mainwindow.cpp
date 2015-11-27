#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "repository.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Repository repo;


}

MainWindow::~MainWindow()
{
    delete ui;
}
