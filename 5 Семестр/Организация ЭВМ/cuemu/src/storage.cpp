#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>

#include "cstorage.h"

// ƒобавл€ет микрокоманду в циклический список микрокоманд list (может быть NULL)
// и возвращает указатель на созданную структуру
microcommand *add(microcommand *list)
{
 microcommand *mc = new microcommand;
 if (list) {
  mc->next = list->next;
  list->next = mc;
 } else {
  mc->next = mc;
 }
 return mc;
}

// Ќаходит микрокоманду, предыдущую по отношению к заданной
microcommand *find_prev(microcommand *list)
{
 if (!list) return NULL;
 microcommand *ptr = list;
 while(ptr->next!=list) ptr = ptr->next;
 return ptr;
}

// ”дал€ет заданную микрокоманду из циклического списка
microcommand *remove(microcommand *list)
{
 if (!list) return NULL;
 if (list->next==list) {delete(list); return NULL;}
 microcommand *prev = find_prev(list);
 prev->next = list->next;
 delete(list);
 return prev;
}

// ѕолностью уничтожает список микрокоманд
void clear(microcommand *list)
{
 if (!list) return;
 microcommand *ptr = list;
 do {
  microcommand *cp = ptr;
  ptr = ptr->next;
  delete(cp);
 } while(ptr!=list);
}

// »щет в списке list микрокоманду с адресом addr
microcommand *search_addr(microcommand *list, dword addr)
{
 if (!list) return NULL;
 microcommand *ptr = list;
 do {
  if (ptr->addr==addr) return ptr;
  ptr = ptr->next;
 } while(ptr!=list);
 return NULL;
}

// ќбрабатывает строку, содержащую адрес микрокоманды и список микроопераций
// в виде:
// адрес код-операции1 код-операции2 ...
// ƒобавл€ет полученную микрокоманду в список list, замен€€ микрокоманду
// с таким же адресом (если она есть)
microcommand *parse_line(microcommand *list, const char *line)
{
 microcommand *newp;
 char *ptr;
// »звлечем из строки первое число - адрес
 dword addr = strtoul(line, &ptr, 10);
// ¬ыделим пам€ть под структуру, если нужно
 newp = list ? search_addr(list, addr) : NULL;
 if (!newp) {newp = add(list); newp->addr = addr;}
 newp->cmd = 0;
 while(true) {
// ѕоследовательно читаем числа из строки, устанавлива€
// соответствующие биты в newp->cmd
  while(*ptr==' ' || *ptr=='\t' || *ptr=='\n' || *ptr=='\r') ptr++;
  if (!*ptr) break;
  char *np;
  dword op = strtoul(ptr, &np, 10);
  ptr = np;
  newp->cmd |= qword(1)<<(op-1);
 }
 return newp;
}

// Ёта функци€ делает обратное действие: формирует строку
// по структуре микрокоманды. Ѕуфер buf должен быть достаточно большим
void deparse_line(microcommand *list, char *buf)
{
 uint8 i;
 ultoa(list->addr, buf, 10);
 for (i=1; i<=64; i++) {
  if (list->cmd & (qword(1)<<(i-1))) {
   char *ptr = buf + strlen(buf);
   *ptr++ = ' ';
   itoa(i, ptr, 10);
  }
 }
}

// Ёта функци€ переводит строку str из кодировки CP1251 в CP866
// дл€ вывода на консоль. —трока не должна быть длиннее, чем CHARTOOEM_BUF_SIZE
// (1024 символов вместе с нулевым байтом)
char *chartooem(const char *str)
{
 static __thread char buf[CHARTOOEM_BUF_SIZE];
 CharToOem(str, buf);
 return buf;
}
