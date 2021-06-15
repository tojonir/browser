#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tab = new myTab();
    ui->horizontalLayout->addWidget(tab);


}

MainWindow::~MainWindow()
{
    delete ui;
}




