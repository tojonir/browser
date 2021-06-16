#ifndef MYTAB_H
#define MYTAB_H

#include <QApplication>
#include <QTabWidget>
#include <QToolButton>
#include <QPushButton>
#include <QLineEdit>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>


#include "tabbar.h"
#include "mywebview.h"
#include "mybutton.h"
#include "mymenu.h"


class myTab : public QTabWidget
{
    Q_OBJECT
public:
    myTab();
    TabBar *tabBar = new TabBar();
    QToolButton *plusbtn = new QToolButton();
    QPushButton *menuBtn;

public slots:
    myWebview *newTab();
};

#endif // MYTAB_H
