// Функции и типы для работы с соединениями
#ifndef CUEMU_CONNECT_H
#define CUEMU_CONNECT_H

#include "cstorage.h"

// Структура, задающая гнездо на "макете"
struct connector {
 const char *name;      // Имя гнезда
 const char *descr;     // Описание
 bool value;            // Логический уровень на гнезде в данный момент
};

// Структура, задающая соединение (точнее, элемент циклического списка)
struct cable {
 connector *first, *second;      // Соединенные гнезда
 cable *next;                    // Следюущий элемент
};

// Индексы гнезд в массиве connectors
#define C_G1 0
#define C_G2 1
#define C_G9 2
#define C_G10 3
#define C_G3 4
#define C_G4 5
#define C_G5 6
#define C_G6 7
#define C_G7 8
#define C_G8 9
#define C_COUNT 10
#define C_ONE 11
#define C_C1 12
#define C_C2 13
#define C_C3 14
#define C_C4 15
#define C_C5 16
#define C_C6 17

// Число гнезд
#define C_NUMBER 18

#define GET_C(i) (connectors[i].value ? 1 : 0)
#define SET_C(i,v) ((void)(connectors[i].value = v))
#define GET_C_ADDR(i) (connectors + i)

extern int recursion_limit;
extern connector connectors[];

// Прототипы
cable *add(cable *list);
cable *find_prev(cable *list);
cable *remove(cable *list);
void clear(cable *list);
connector *find_connector(const char *name);
void init_connectors();
cable *find_connection(cable *list, int c1, int c2);
cable *find_connection(cable *list, const char *c1, const char *c2);
cable *add_connection(cable *list, const char *c1, const char *c2);
void out_connector(cable *list, int c, bool val, int counter=0,
                   int incoming=C_NUMBER);
void flush_connectors();

#endif