#ifndef WIDGET_H
#define WIDGET_H
#include <QPushButton>
#include <QIcon>
#include <QTabWidget>
#include <QToolButton>
#include <QTabBar>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QMenu>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QContextMenuEvent>
#include <QUrl>
#include <QObject>

class myWebview;

class myButton:public QPushButton{
    public:
        myButton(QIcon icon,QString name);
};

class myTabBar: public QTabBar{

protected:
//    void mousePressEvent(QMouseEvent* e);
};

class myTab: public QTabWidget{
    Q_OBJECT
    public:
        myTab();
        myTabBar *tabBar = new myTabBar();
        QToolButton *plusbtn = new QToolButton();
        QPushButton *menuBtn;

    public slots:
        myWebview *newTab();

};


class myWebview:public QWebEngineView{
    Q_OBJECT
public:

protected:
    myWebview *createWindow(QWebEnginePage::WebWindowType type) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

signals:
    void createNewTab();
};

class myMenu: public QMenu{
    Q_OBJECT
public:
    QPushButton *btn;
    QAction *newTab;
    QAction *newWindow;
    QAction *history;
    QMenu *subHistory = new QMenu();
    QAction *download;
    QAction *exit;
    myMenu(QPushButton *btn = nullptr){
        this->btn = btn;
        newTab = addAction("new tab");
        newTab->setShortcut(QKeySequence::AddTab);
        newWindow = addAction("new window");
        newWindow->setShortcut(QKeySequence::New);
        addSeparator();
        history = addMenu(subHistory);
        subHistory->setTitle("History");
        subHistory->addAction("history");

        download = addAction("download");
        addSeparator();
        exit = addAction("Exit");
    };


protected:
    void showEvent(QShowEvent*);
signals:
    void newTabSignal();
};



#endif // WIDGET_H
