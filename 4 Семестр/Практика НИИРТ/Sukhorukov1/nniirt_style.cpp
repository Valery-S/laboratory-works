#include "nniirt_style.h"
#include "button_with_window.h"

/*-----------------------------------------------------Constructor--------------------------------------------------------*/
NNIIRT_Style::NNIIRT_Style() :
    QCommonStyle(){}



/*----------------------------------------------------drawControl-------------------------------------------------------*/
/* Функция отрисовки простого элемента управления приложением
 * Параметры функции:
 *  1)Константа для определения типа элемента.
 *  2)Указатель на стилевые параметры элемента.
 *  3)Указатель на "художника", ответсвенного за отрисовку элементов.
 *  4)Указатель на виджет - элемент, который необходимо отрисовать.
 * Результат работы функции - элемент, нарисованный в окне приложения.
*/
void NNIIRT_Style::drawControl(QStyle::ControlElement element, const QStyleOption *opt, QPainter *p, const QWidget *w) const{
    switch( element ){
        //Секция отрисовки "нажимной" кнопки
        case CE_PushButton:{
             QPushButton * button=(QPushButton*)w;

             //Отрисовка кнопки прямоугольной формы
             p->fillRect(0,0,button->width(),button->height(),QColor( 220, 220, 220 ));

             //Отрисовка левой и верхней частей рамки кнопки
             p->setPen( QPen( QColor( 255, 255, 255)));
             for(int i=0;i<3;i++){
                p->drawLine(QPoint(i,0),QPoint(i,button->height()-1));
                p->drawLine(QPoint(0,i),QPoint(button->width()-1,i));
             }

             //Отрисовка правой и нижней частей рамки кнопки
             p->setPen( QPen( QColor( 0, 0, 0)));
             for(int i=0;i<3;i++){
                 p->drawLine(QPoint(0+i,button->height()-i-1),QPoint(button->width()-1,button->height()-i-1));
                 p->drawLine(QPoint(button->width()-i-1,i),QPoint(button->width()-i-1,button->height()-1));
             }

             //Вывод текста кноки
             QStyleOptionButton* opt_but=(QStyleOptionButton*)opt;
             int x=(opt_but->rect.width()-(opt_but->text.size())*8)/2;
             int y=(opt_but->rect.height()-8)/2;
             QRect textRect (QPoint(x,y),QPoint(opt_but->rect.width(),opt_but->rect.height()));
             p->setPen( QPen( QColor( 0, 0, 0 )));
             p->setFont(QFont("times new roman"));
             p->drawText(textRect,opt_but->text);

             //Если кнопка обладает свойством фиксации состояния нажатия,
             //то в случае нажатия отрисовывается пунктирная рамка
             if(button->isCheckable()){
                 if(button->isChecked()){
                     p->setPen( QPen( QColor( 0, 0, 255)));
                     //Отрисовка правой и левой частей рамки
                     for(int i=7;i<button->height()-5;i=i+10){
                         p->drawLine(QPoint(5,i),QPoint(5,i+5));
                         p->drawLine(QPoint(button->width()-5,i),QPoint(button->width()-5,i+5));
                      }
                     //Отрисовка верхней и нижней частей рамки
                     for(int i=7;i<button->width()-5;i=i+10){
                         p->drawLine(QPoint(i,5),QPoint(i+5,5));
                         p->drawLine(QPoint(i,button->height()-5),QPoint(i+5,button->height()-5));
                      }
                 }
             }
        }
        break;
        // Конец секции отрисовки "нажимной" кнопки

        //Секция отрисовки кнопки, при нажатии на которую открывается новое окно
        case CE_CheckBox:{
                Button_with_window* check_but=(Button_with_window*)w;

                //Отрисовка кнопки прямоугольной формы
                p->fillRect(0,0,check_but->width(),check_but->height(),QColor( 220, 220, 220 ));

                //Отрисовка левой и верхней частей рамки кнопки
                p->setPen( QPen( QColor( 255, 255, 255)));
                for(int i=0;i<3;i++){
                   p->drawLine(QPoint(i,0),QPoint(i,check_but->height()-1));
                   p->drawLine(QPoint(0,i),QPoint(check_but->width()-1,i));
                }

                //Отрисовка правой и нижней частей рамки кнопки
                p->setPen( QPen( QColor( 0, 0, 0)));
                for(int i=0;i<3;i++){
                    p->drawLine(QPoint(0+i,check_but->height()-i-1),QPoint(check_but->width()-1,check_but->height()-i-1));
                    p->drawLine(QPoint(check_but->width()-i-1,i),QPoint(check_but->width()-i-1,check_but->height()-1));
                }

                //Отрисовка треугольника в правом нижнем углу
                for(int i=0;i<10;i++){
                    p->drawLine(check_but->width()-5,check_but->height()-5-i,check_but->width()-15+i,check_but->height()-5-i);

                }

                //Вывод текста кноки
                QStyleOptionButton* opt_but=(QStyleOptionButton*)opt;
                int x=(opt_but->rect.width()-(opt_but->text.size())*8)/2;
                int y=(opt_but->rect.height()-8)/2;
                QRect textRect (QPoint(x,y),QPoint(opt_but->rect.width(),opt_but->rect.height()));
                p->setPen( QPen( QColor( 0, 0, 0 )));
                p->setFont(QFont("times new roman"));
                p->drawText(textRect,opt_but->text);

                //Если кнопка нажата, то отображается новое окно
                if(check_but->isChecked()){
                   //Отображение дочернего окна
                   check_but->show_window();
                   //Перевод кнопки в состояние "отжата"
                   check_but->setChecked(false);
                   //Изменение цвета заднего фона нового окна
                   QColor background( 190, 190, 190 );
                   check_but->window->setAutoFillBackground(true);
                   check_but->window->setPalette(background);
               }

        }
        break;
        // Конец секции отрисовки кнопки, при нажатии на которую открывается новое окно

        //Для отображения непереопределённых элементов, вызывается функции
        //родительского класса - стандартного стиля
        default:
            QCommonStyle::drawControl(element, opt, p, w);
        break;
    }
}


/*------------------------------------------------drawComplexControl----------------------------------------------------*/
/* Функция отрисовки сложного элемента управления приложением
 * Параметры функции:
 *  1)Константа для определения типа элемента.
 *  2)Указатель на стилевые параметры элемента.
 *  3)Указатель на "художника", ответсвенного за отрисовку элементов.
 *  4)Указатель на виджет - элемент, который необходимо отрисовать.
 * Результат работы функции - элемент, нарисованный в окне приложения.
*/
void NNIIRT_Style::drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *w ) const{
    switch(cc){
        //Секция отображения группы кнопок
        case CC_GroupBox:{
            QGroupBox * group=(QGroupBox*)w;
            //Изменение цвета пера
            p->setPen( QPen( QColor( 0, 0, 255 )));

            //Отрисовка левой границы, толщиной 2 пикселя
            p->drawLine(0,5,0,group->height()-1);
            p->drawLine(1,5,1,group->height()-1);

            //Отрисовка нижней границы, толщиной 2 пикселя
            p->drawLine(0,group->height()-1,group->width()-1,group->height()-1);
            p->drawLine(0,group->height()-2,group->width()-1,group->height()-2);

            //Отрисовка правой границы, толщиной 2 пикселя
            p->drawLine(group->width()-1,5,group->width()-1,group->height()-1);
            p->drawLine(group->width()-2,5,group->width()-2,group->height()-1);

            QStyleOptionGroupBox *opt_group=(QStyleOptionGroupBox*)opt;

            //Определение ширины текств
            int text_width=opt_group->text.size()*9;

            //Отрисовка левой части верхней границы
            p->drawLine(0,5,(group->width()-text_width)/2-10,5);
            p->drawLine(0,6,(group->width()-text_width)/2-10,6);

            //Отрисовка правой части верхней границы
            p->drawLine(group->width()-1,5,(group->width()+text_width)/2+10,5);
            p->drawLine(group->width()-1,6,(group->width()+text_width)/2+10,6);

            //Вывод названия группы кнопок
            QRect textRect ((group->width()-text_width)/2,0,text_width,20);
            p->setPen( QPen( QColor( 0, 0, 255 )));
            p->setFont(QFont("times new roman"));
            p->drawText(textRect,opt_group->text);
        }
        break;
        //Конец секции отображения группы кнопок

        //Для отображения непереопределённых элементов, вызывается функции
        //родительского класса - стандартного стиля
        default:
            QCommonStyle::drawComplexControl(cc,opt,p,w );
        break;
    }
}
