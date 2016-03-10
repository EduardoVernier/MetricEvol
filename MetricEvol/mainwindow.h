#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include "git2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void write_to_textbox(QString txt);

private slots:
    void on_openRepoMenuBar_triggered();
    void on_cloneRepoMenuBar_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
