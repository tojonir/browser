#ifndef TABBAR_H
#define TABBAR_H
#include <QTabBar>
#include <QMenu>
#include <QMouseEvent>

class TabBar : public QTabBar
{
public:
    TabBar();
protected:
    void mousePressEvent(QMouseEvent* e);
};

#endif // TABBAR_H
