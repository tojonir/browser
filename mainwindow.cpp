#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(tab);
    tab->setStyleSheet(""
       "QTabBar::tab{"
           "background-color:rgba(133, 171, 171,0.1);"
           "width:150px;"
           "height:35px;"
           "padding-left:10px;"
           "padding-right:20px;"
           "font-size:11px;"

       "}"
       "QTabBar::tab:selected {"
           "background: rgba(255,255,255,0.9);"

       "}"
       "QTabBar::tab:last{"
           "width: 10px;"
           "background-color: rgba(255,255,255,0);"
           "border:0px;"
       "}"
       );
    tab->setMovable(true);
    tab->setTabsClosable(true);
    int add = tab->addTab(new QWidget(),"");
    tab->setTabEnabled(add,false);
    tab->tabBar()->setTabButton(0,QTabBar::RightSide,plusbtn);
    plusbtn->setIcon(QIcon(":/images/plus.svg"));
    plusbtn->setIconSize(QSize(60,60));
    plusbtn->setStyleSheet("background-color:rgba(255,255,255,0.5); border:0px;border-radius:10px;");

    connect(plusbtn,&QToolButton::clicked,this,&MainWindow::addTab);
    connect(tab,&QTabWidget::tabCloseRequested,this,[this](int index){
        if(tab->count()>2){
            tab->removeTab(index);
            tab->setCurrentIndex(index-1);
        }else if (tab->count()==2) {
            qApp->quit();
    }

    });
    connect(tab->tabBar(),&QTabBar::tabMoved,this,[this](int from,int to){
       int nbTab = tab->count()-1;
       if(from == nbTab){
           tab->tabBar()->moveTab(to,nbTab);
       }
    });

    addTab();



}

void MainWindow::addTab(){
    QWidget *container = new QWidget();
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->setContentsMargins(0,0,0,0);
    container->setLayout(vbox);
    QWidget *header = new QWidget();
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->setContentsMargins(0,0,0,0);
    header->setLayout(hbox);
    header->setStyleSheet(""
          "#header_icon{"
            "background-color: rgba(225,225,225,0);"
            "padding:5px;"
            "border-radius:30px;} "
          "#header_icon:hover{"
            "background-color: rgba(225,225,225,0.5);}"
          );

    QPushButton *backBtn = new myButton(QIcon(":/images/back.svg"),"header_icon");
    QPushButton *reloadBtn = new myButton(QIcon(":/images/reload.svg"),"header_icon");
    QPushButton *forwardBtn = new myButton(QIcon(":/images/forward.svg"),"header_icon");

    hbox->addWidget(backBtn);
    hbox->addWidget(reloadBtn);
    hbox->addWidget(forwardBtn);

    QWidget *bar_container = new QWidget();
    bar_container->setStyleSheet("background-color:#dbd9d9; border-radius:12px;");
    QHBoxLayout *bar_layout = new QHBoxLayout();
    bar_layout->setContentsMargins(5,5,5,5);
    bar_layout->setSpacing(0);
    QPushButton *status = new myButton(QIcon(":/images/http.svg"),"status");
    QLineEdit *bar = new QLineEdit();
    bar_container->setLayout(bar_layout);
    bar_layout->addWidget(status);
    bar_layout->addWidget(bar);
    hbox->addWidget(bar_container);

    QPushButton *menu = new myButton(QIcon(":/images/humb.svg"),"header_icon");
    hbox->addWidget(menu);

    QWidget *web = new QWidget();
    web->setObjectName("web");
    web->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

    vbox->addWidget(header);
    vbox->addWidget(web);

    int index = tab->count() - 1;
    int insertedTab = tab->insertTab(index,container,"tab" + QString::number(tab->count()));
    tab->setCurrentIndex(insertedTab);

}



MainWindow::~MainWindow()
{
    delete ui;
}




