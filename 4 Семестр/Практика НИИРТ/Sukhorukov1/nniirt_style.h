#ifndef NNIIRT_STYLE_H
#define NNIIRT_STYLE_H

#include <QtGui>
#include <QCommonStyle>
#include <QStyleOption>
#include<QPushButton>
#include <QBoxLayout>
#include <QGroupBox>

/* Класс стиля приложения. Родительский класс- Стандартный стиль.*/
class NNIIRT_Style : public QCommonStyle{
    Q_OBJECT
public:
    //Конструктор без параметров
    NNIIRT_Style();

    //Функция отрисовки простого элемента управления приложением
    void drawControl(QStyle::ControlElement element, const QStyleOption *opt, QPainter *p, const QWidget *w) const;
    //Функция отрисовки сложного элемента управления приложением
    void drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *w ) const;
};

#endif // NNIIRT_STYLE_H
