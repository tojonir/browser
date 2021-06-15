#include "widget.h"
#include "mainwindow.h"

myButton::myButton(QIcon icon,QString name){
    this->setIcon(QIcon(icon));
    this->setObjectName(name);
}

myTab::myTab(){
    this->setStyleSheet(""
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
    tabBar->setMovable(true);
    tabBar->setTabsClosable(true);
    this->setTabBar(tabBar);

    int add = this->addTab(new QWidget(),"");
    tabBar->setTabEnabled(add,false);
    tabBar->setTabButton(0,QTabBar::RightSide,plusbtn);
    plusbtn->setIcon(QIcon(":/images/plus.svg"));
    plusbtn->setIconSize(QSize(60,60));
    plusbtn->setStyleSheet("background-color:rgba(255,255,255,0.5); border:0px;border-radius:10px;");

    connect(this,&QTabWidget::tabCloseRequested,this,[this](int index){
        if(this->count()>2){
            this->removeTab(index);
            this->setCurrentIndex(index-1);
        }else if (this->count()==2) {
            qApp->quit();
    }

    });
    connect(tabBar,&QTabBar::tabMoved,this,[this](int from,int to){
       int nbTab = this->count()-1;
       if(from == nbTab){
           tabBar->moveTab(to,nbTab);
       }
    });

    connect(plusbtn,&QToolButton::clicked,this,&myTab::newTab);

    newTab();
}

//void myTabBar::mousePressEvent(QMouseEvent *e){
//    qDebug("bar");
//}


myWebview *myTab::newTab(){

    QWidget *container = new QWidget();
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->setContentsMargins(0,0,0,0);
    container->setLayout(vbox);

    QWidget *header = new QWidget();
    header->setStyleSheet(""
        "#header_icon{"
          "background-color: rgba(225,225,225,0);"
          "padding:5px;"
          "border-radius:30px;} "
        "#header_icon:hover{"
          "background-color: rgba(225,225,225,0.5);}"
        "QPushButton::menu-indicator {"
            "image: none;"
        "}"
     );
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->setContentsMargins(0,0,0,0);
    header->setLayout(hbox);
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


    QPushButton *menuBtn = new myButton(QIcon(":/images/humb.svg"),"header_icon");
    myMenu *menu = new myMenu(menuBtn);
    connect(menu->newTab,&QAction::triggered,this,[this](){this->newTab();});
    menuBtn->setMenu(menu);
    hbox->addWidget(menuBtn);



    QWidget *webContainer = new QWidget();
    webContainer->setParent(this);
    webContainer->setObjectName("web");
    webContainer->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    QHBoxLayout *webLayout = new QHBoxLayout();
    webLayout->setContentsMargins(0,0,0,0);
    webContainer->setLayout(webLayout);

    myWebview *webview = new myWebview;
    webview->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    int index = this->count() - 1;
    webview->load(QUrl("https://google.com"));

    webLayout->addWidget(webview);

    vbox->addWidget(header);
    vbox->addWidget(webContainer);

    int moved;
    int insertedTab = insertTab(index,container,"loading...");
    setCurrentIndex(insertedTab);

    connect(backBtn,&QPushButton::clicked,this,[webview](){
        webview->back();
    });

    connect(reloadBtn,&QPushButton::clicked,this,[webview](){
        webview->reload();
    });

    connect(forwardBtn,&QPushButton::clicked,this,[webview](){
        webview->forward();
    });

    connect(webview,&QWebEngineView::urlChanged,this,[webview,bar](const QUrl &url){
        webview->load(url);
        bar->setText(url.toString());
        qDebug() << url;
    });

    connect(webview,&QWebEngineView::loadStarted,this,[this,insertedTab,moved](){
        QIcon icon(":/images/loading.png");
        int index;
        if (this->currentIndex() != insertedTab){
            index = this->currentIndex();
        }else{
            index = insertedTab;
        }
        tabBar->setTabIcon(index,icon);
        tabBar->setTabText(index,"loading...");
        qDebug() << moved;
    });

    connect(webview,&QWebEngineView::loadFinished,this,[this,webview,insertedTab](){
        tabBar->setTabText(insertedTab,webview->page()->title());
        qDebug() << "finished";
    });

    connect(webview,&QWebEngineView::iconChanged,this,[this,insertedTab](const QIcon &icon){
        tabBar->setTabIcon(insertedTab,icon);
        qDebug() << "finished";
    });

    connect(tabBar,&QTabBar::tabMoved,this,[moved](int from,int to) mutable->int{
        moved = from;
        return from;
    });


    return webview;



}


void myMenu::showEvent(QShowEvent *){
    QPoint pos = btn->mapToGlobal(btn->rect().bottomRight());
    this->move(pos - this->rect().topRight());
}

myWebview *myWebview::createWindow(QWebEnginePage::WebWindowType type){
    MainWindow *mainwindow = qobject_cast<MainWindow*>(window());
    return mainwindow->tab->newTab();
}

void myWebview::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = page()->createStandardContextMenu();
    const QList<QAction *> actions = menu->actions();

    menu->popup(event->globalPos());
}


