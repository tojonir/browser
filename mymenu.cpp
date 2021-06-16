#include "mymenu.h"

void myMenu::showEvent(QShowEvent *){
    QPoint pos = btn->mapToGlobal(btn->rect().bottomRight());
    this->move(pos - this->rect().topRight());
}
