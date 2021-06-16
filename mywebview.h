#ifndef MYWEBVIEW_H
#define MYWEBVIEW_H

#include <QWebEngineView>

class myWebview : public QWebEngineView
{
    Q_OBJECT
public:
    myWebview();
protected:
    myWebview *createWindow(QWebEnginePage::WebWindowType type) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

signals:
    void createNewTab();
    void setDevTool();
};

#endif // MYWEBVIEW_H
