#ifndef MYMENU_H
#define MYMENU_H
#include <QMenu>
#include <QPushButton>


class myMenu : public QMenu
{
    Q_OBJECT
public:
    QPushButton *btn;
    QAction *newTab;
    QAction *newWindow;
    QAction *zoomin;
    QAction *zoomout;
    QAction *zoomfit;
    QAction *history;
    QMenu *subHistory = new QMenu();
    QAction *download;
    QAction *exit;
    myMenu(QPushButton *btn = nullptr){
        this->btn = btn;
        newTab = addAction("new tab");
        newTab->setShortcut(QKeySequence::AddTab);
        newWindow = addAction("new window");
        addSeparator();
        zoomin = addAction("zoomin");
        zoomin->setShortcut(QKeySequence::ZoomIn);
        zoomout = addAction("zoomout");
        zoomout->setShortcut(QKeySequence::ZoomOut);
        zoomfit = addAction("zoomfit");
        zoomfit->setShortcut(QKeySequence("Ctrl+1"));
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

#endif // MYMENU_H
