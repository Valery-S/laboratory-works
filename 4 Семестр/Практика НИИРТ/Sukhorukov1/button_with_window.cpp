#include "button_with_window.h"

/*-----------------------------------------------------Constructor--------------------------------------------------------*/
Button_with_window::Button_with_window() :
    QCheckBox(){}

/*-----------------------------------------------------Constructor--------------------------------------------------------*/
Button_with_window::Button_with_window(QString s,QWidget *w,QWidget*p) {
   this->window=w;
   this->setText(s);
   this->setParent(p);
   this->setMouseTracking(true);
}


/*-----------------------------------------------------show_window----------------------------------------------------*/
/* Функция отображения окна
 * Результат работы функции - отображение дочернего окна
*/
void Button_with_window::show_window(){
        this->window->show();
}


