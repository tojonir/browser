#include "tabbar.h"

TabBar::TabBar()
{

}

void TabBar::mousePressEvent(QMouseEvent *e){
    if (e->button()==2){
           QMenu *menu = new QMenu();
           menu->addAction("new Tab");
           menu->addSeparator();
           QAction *reload = menu->addAction("reload");
           menu->addAction("Pin");
           menu->addSeparator();
           menu->addAction("close");
           menu->addAction("close other tabs");
           menu->addAction("close tabs to the right");
           menu->exec(e->globalPos());
    }
    QTabBar::mousePressEvent(e);
}
