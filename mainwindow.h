#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolButton>
#include <QMouseEvent>
#include <QLineEdit>
#include <QTabBar>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTabWidget *tab = new QTabWidget();
    QToolButton *plusbtn = new QToolButton();


public slots:
    void addTab();

signals:





private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


