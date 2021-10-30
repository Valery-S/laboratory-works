#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>

#include "cstorage.h"

// ��������� ������������ � ����������� ������ ����������� list (����� ���� NULL)
// � ���������� ��������� �� ��������� ���������
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

// ������� ������������, ���������� �� ��������� � ��������
microcommand *find_prev(microcommand *list)
{
 if (!list) return NULL;
 microcommand *ptr = list;
 while(ptr->next!=list) ptr = ptr->next;
 return ptr;
}

// ������� �������� ������������ �� ������������ ������
microcommand *remove(microcommand *list)
{
 if (!list) return NULL;
 if (list->next==list) {delete(list); return NULL;}
 microcommand *prev = find_prev(list);
 prev->next = list->next;
 delete(list);
 return prev;
}

// ��������� ���������� ������ �����������
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

// ���� � ������ list ������������ � ������� addr
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

// ������������ ������, ���������� ����� ������������ � ������ �������������
// � ����:
// ����� ���-��������1 ���-��������2 ...
// ��������� ���������� ������������ � ������ list, ������� ������������
// � ����� �� ������� (���� ��� ����)
microcommand *parse_line(microcommand *list, const char *line)
{
 microcommand *newp;
 char *ptr;
// �������� �� ������ ������ ����� - �����
 dword addr = strtoul(line, &ptr, 10);
// ������� ������ ��� ���������, ���� �����
 newp = list ? search_addr(list, addr) : NULL;
 if (!newp) {newp = add(list); newp->addr = addr;}
 newp->cmd = 0;
 while(true) {
// ��������������� ������ ����� �� ������, ������������
// ��������������� ���� � newp->cmd
  while(*ptr==' ' || *ptr=='\t' || *ptr=='\n' || *ptr=='\r') ptr++;
  if (!*ptr) break;
  char *np;
  dword op = strtoul(ptr, &np, 10);
  ptr = np;
  newp->cmd |= qword(1)<<(op-1);
 }
 return newp;
}

// ��� ������� ������ �������� ��������: ��������� ������
// �� ��������� ������������. ����� buf ������ ���� ���������� �������
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

// ��� ������� ��������� ������ str �� ��������� CP1251 � CP866
// ��� ������ �� �������. ������ �� ������ ���� �������, ��� CHARTOOEM_BUF_SIZE
// (1024 �������� ������ � ������� ������)
char *chartooem(const char *str)
{
 static __thread char buf[CHARTOOEM_BUF_SIZE];
 CharToOem(str, buf);
 return buf;
}
