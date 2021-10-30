#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "connect.h"
#pragma hdrstop
#pragma option -w-inl -w-csu
#include <map>

typedef std::map<int, bool, std::less<int> > connector_buffer_t;

connector_buffer_t connector_buffer;

// ������������ ����������� ������� ������� out_connector()
// ��� ������������� ���������� ������� �� �������
int recursion_limit = 32;

connector connectors[] =
{
 {"G1",    "IN: RGA ������� ������"},
 {"G2",    "OUT: RGA ������� ������"},
 {"G9",    "OUT: RGB ������� ������"},
 {"G10",   "IN: RGB ������� ������"},
 {"G3",    "OUT: SUM ����� ������ ��������"},
 {"G4",    "OUT: SUM ������ ������ ��������"},
 {"G5",    "IN: ������ ������������"},
 {"G6",    "IN: �������� ������"},
 {"G7",    "IN: �������� ������ (�� ����������)"},
 {"G8",    "IN: ����������� � ��������� ������"},
 {"COUNT", "OUT: ����������� ������ �������� (1, ���� �������!=0)"},
 {"ONE",   "OUT: ���������� �������"},
 {"C1",    "IN: ������� 1"},
 {"C2",    "IN: ������� 2"},
 {"C3",    "IN: ������� 3"},
 {"C4",    "IN: ������� 4"},
 {"C5",    "IN: ������� 5"},
 {"C6",    "IN: ������� 6"},
 {NULL,    NULL}
};

// ��������� ����� ���������� (��������������������) � ������ ���������� list
// (list ����� ���� NULL)
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

// ������� ���������� ���������
cable *find_prev(cable *list)
{
 cable *ptr = list;
 while(ptr->next!=list) ptr = ptr->next;
 return ptr;
}

// ������� ���������� list �� ������
cable *remove(cable *list)
{
 if (list->next==list) {delete(list); return NULL;}
 cable *prev = find_prev(list);
 prev->next = list->next;
 delete(list);
 return prev;
}

// ���������� ������ list ���������
void clear(cable *list)
{
 cable *ptr = list;
 do {
  cable *cp = ptr;
  ptr = ptr->next;
  delete(cp);
 } while(ptr!=list);
}

// ��� ������� ���� � ������� ����� ������ � ������ name
// � ���������� ��� ����� (��� NULL, ���� ������ �� ������)
connector *find_connector(const char *name)
{
 connector *ptr;
 for(ptr=connectors; ptr->name; ptr++) if (!strcmp(ptr->name, name)) return ptr;
 return NULL;
}

// �������, ������������ ��� ������ �� ������� � ����
void init_connectors()
{
 connector *ptr;
 for(ptr=connectors; ptr->name; ptr++) ptr->value = 0;
}

// ���� � ������ ���������� list �� ����������, ������� ���������
// ������ � ��������� c1 � c2
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

// ���� � ������ ���������� list �� ����������, ������� ���������
// ������ � ������� c1 � c2
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

// ��������� � ������ list ����������, ����������� ������ c1 � c2
// � ���������� ��� ����� (��� NULL, ���� �����-�� �� ����� �� ����������)
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

// ��� ����������� ������� ������� � ������ � �������� c ������� val,
// �������� ������ ���� �����, ��������� � ���
// list - ����������� ������ ����������
// counter - ������ ���� ����� ��� ������������� ������� (������� �����������)
// c - ������������ ��� ������������� ������� (������, ������ "������" �������)
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
