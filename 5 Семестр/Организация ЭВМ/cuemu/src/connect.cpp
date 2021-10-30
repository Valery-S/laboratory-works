#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "connect.h"
#pragma hdrstop
#pragma option -w-inl -w-csu
#include <map>

typedef std::map<int, bool, std::less<int> > connector_buffer_t;

connector_buffer_t connector_buffer;

// Максимальная вложенность вызовов функции out_connector()
// при распределении логических уровней по гнездам
int recursion_limit = 32;

connector connectors[] =
{
 {"G1",    "IN: RGA старший разряд"},
 {"G2",    "OUT: RGA младший разряд"},
 {"G9",    "OUT: RGB старший разряд"},
 {"G10",   "IN: RGB младший разряд"},
 {"G3",    "OUT: SUM левый разряд переноса"},
 {"G4",    "OUT: SUM правый разряд переноса"},
 {"G5",    "IN: Разряд переполнения"},
 {"G6",    "IN: Знаковый разряд"},
 {"G7",    "IN: Знаковый разряд (не реализован)"},
 {"G8",    "IN: Добавляемый к сумматору разряд"},
 {"COUNT", "OUT: Контрольный сигнал счетчика (1, если СЧЕТЧИК!=0)"},
 {"ONE",   "OUT: Логическая единица"},
 {"C1",    "IN: Условие 1"},
 {"C2",    "IN: Условие 2"},
 {"C3",    "IN: Условие 3"},
 {"C4",    "IN: Условие 4"},
 {"C5",    "IN: Условие 5"},
 {"C6",    "IN: Условие 6"},
 {NULL,    NULL}
};

// Добавляет новое соединение (неинициализированное) в список соединений list
// (list может быть NULL)
cable *add(cable *list)
{
 cable *ptr = new cable;
 if (list) {
  ptr->next = list->next;
  list->next = ptr;
 } else {
  ptr->next = ptr;
 }
 return ptr;
}

// Находит предыдущую структуру
cable *find_prev(cable *list)
{
 cable *ptr = list;
 while(ptr->next!=list) ptr = ptr->next;
 return ptr;
}

// Удаляет соединение list из списка
cable *remove(cable *list)
{
 if (list->next==list) {delete(list); return NULL;}
 cable *prev = find_prev(list);
 prev->next = list->next;
 delete(list);
 return prev;
}

// Уничтожает список list полностью
void clear(cable *list)
{
 cable *ptr = list;
 do {
  cable *cp = ptr;
  ptr = ptr->next;
  delete(cp);
 } while(ptr!=list);
}

// Эта функция ищет в массиве гнезд гнездо с именем name
// и возвращает его адрес (или NULL, если ничего не найдет)
connector *find_connector(const char *name)
{
 connector *ptr;
 for(ptr=connectors; ptr->name; ptr++) if (!strcmp(ptr->name, name)) return ptr;
 return NULL;
}

// Функция, сбрасывающая все уровни на гнездах в нуль
void init_connectors()
{
 connector *ptr;
 for(ptr=connectors; ptr->name; ptr++) ptr->value = 0;
}

// Ищет в списке соединений list то соединение, которое соединяет
// гнезда с индексами c1 и c2
cable *find_connection(cable *list, int c1, int c2)
{
 if (!list) return NULL;
 cable *ptr = list;
 do {
  int ic1 = ptr->first - connectors;
  int ic2 = ptr->second - connectors;
  if ((c1==ic1 && c2==ic2) || (c1==ic2 && c2==ic1)) return ptr;
  ptr = ptr->next;
 } while(ptr!=list);
 return NULL;
}

// Ищет в списке соединений list то соединение, которое соединяет
// гнезда с именами c1 и c2
cable *find_connection(cable *list, const char *c1, const char *c2)
{
 connector *ct1, *ct2;
 ct1 = find_connector(c1);
 if (!ct1) return NULL;
 ct2 = find_connector(c2);
 if (!ct2) return NULL;
 if (ct1==ct2) return NULL;
 return find_connection(list, ct1-connectors, ct2-connectors);
}

// Добавляет в список list соединение, связывающее гнезда c1 и c2
// и возвращает его адрес (или NULL, если какое-то из гнезд не существует)
cable *add_connection(cable *list, const char *c1, const char *c2)
{
 connector *ct1, *ct2;
 ct1 = find_connector(c1);
 if (!ct1) return NULL;
 ct2 = find_connector(c2);
 if (!ct2) return NULL;
 if (ct1==ct2) return NULL;
 cable *res = find_connection(list, ct1-connectors, ct2-connectors);
 if (res) return res;
 res = add(list);
 res->first = ct1;
 res->second = ct2;
 return res;
}

// Эта рекурсивная функция выводит в гнездо с индексом c уровень val,
// обновляя уровни всех гнезд, связанных с ним
// list - циклический список соединений
// counter - должен быть нулем при нерекурсивных вызовах (уровень вложенности)
// c - игнорируется при нерекурсивных вызовах (гнездо, откуда "пришел" уровень)
void out_connector(cable *list, int c, bool val, int counter, int incoming)
{
// SET_C(c, val);
 connector_buffer.insert(connector_buffer_t::value_type(c, val));
 if (!list) return;
 if (counter>=recursion_limit) return;
 int i;
 for (i=0; i<C_NUMBER; i++) {
  if (i==incoming) continue;
  cable *cb = find_connection(list, c, i);
  if (!cb) continue;
  out_connector(list, i, val, counter+1, c);
 }
}

void flush_connectors()
{
 for (connector_buffer_t::const_iterator i=connector_buffer.begin();
      i!=connector_buffer.end(); i++) {
  SET_C((*i).first, (*i).second);    
 }
 connector_buffer.erase(connector_buffer.begin(), connector_buffer.end());
}
