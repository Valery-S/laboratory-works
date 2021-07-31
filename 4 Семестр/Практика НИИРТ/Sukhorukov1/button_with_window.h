#ifndef BUTTON_TO_SHOW_WINDOW_H
#define BUTTON_TO_SHOW_WINDOW_H

#include <QCheckBox>
#include <QWidget>

/* Класс кнопки, при нажатии на которую открывается новое окно.
 * Родительский класс - кнопка-флаг (кнопка с проверкой нажатия) .*/
class Button_with_window : public QCheckBox{
public:
    //Конструктор без параметров
    Button_with_window();
    //Конструктор с параметрами
    Button_with_window(QString,QWidget*,QWidget*);

    //Функция для отображения окна
    void show_window();

    //Указатель на виджет - окно
    QWidget* window;

};

#endif // BUTTON_TO_SHOW_WINDOW_H
