#include "mywebview.h"
#include "mainwindow.h"

myWebview::myWebview()
{

}

myWebview *myWebview::createWindow(QWebEnginePage::WebWindowType type){

    MainWindow *mainwindow = qobject_cast<MainWindow*>(window());
    if (
            type == QWebEnginePage::WebBrowserWindow
            || type == QWebEnginePage::WebBrowserTab
            || type == QWebEnginePage::WebBrowserBackgroundTab
            ){
        return mainwindow->tab->newTab();
    }
    qDebug() << type;
    return nullptr;

}

void myWebview::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = page()->createStandardContextMenu();
    const QList<QAction *> actions = menu->actions();
    QAction *inspect = actions[actions.count() - 1];
    connect(inspect,&QAction::triggered,this,[this](){
        emit setDevTool();
    });

    menu->popup(event->globalPos());
}
