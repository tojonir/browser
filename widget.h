#ifndef WIDGET_H
#define WIDGET_H
#include <QPushButton>
#include <QIcon>

class myButton:public QPushButton{
public:
    myButton(QIcon icon,QString name);
};

#endif // WIDGET_H
