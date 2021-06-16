#include "mybutton.h"

myButton::myButton(QIcon icon,QString name){
    this->setIcon(QIcon(icon));
    this->setObjectName(name);
}
