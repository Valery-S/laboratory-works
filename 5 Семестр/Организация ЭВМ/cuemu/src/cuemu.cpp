#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include "cuemu.h"

// Классы iostream находятся в namespace std (ANSI C++)
// Однако в BC++5 это не так (std даже не объявляется в iostream.h)
namespace std {;}
using namespace std;

// Указатель на поток стандартного вывода
// Указывает на cout по умолчанию, но может быть переопределен
// (если консоль создана с помощью AllocConsole(), то cout не работает)
ostream *__sout = &cout;

// Этот класс нужен только для переопределения операторов <<
class TAutoConvertingCout {
public:
 void flush() {__sout->flush();}
} __cout;

// Строки выводятся с преобразованием в cp1251->cp866
TAutoConvertingCout &operator<<(TAutoConvertingCout &c, const char *str)
{
 (*__sout) << chartooem(str);
 return c;
}

// Остальные объекты выводятся как обычно
template <class T> TAutoConvertingCout &operator<<(TAutoConvertingCout &c, const T &x)
{
 (*__sout) << x;
 return c;
}

#define cout __cout        // Правильный поток стандартного вывода

microcommand *list = NULL;    // Циклический список микрокоманд
cable *connections = NULL;    // Циклический список соединений
// Функция, вызываемая после выполнения очередной команды (может быть NULL,
// если ничего вызывать не надо)
cuemu_notify_func_pointer cuemu_notify_func;
// Параметр, передаваемый этой функции
void *cuemu_notify_data;

void process_stream(istream &in, bool is_stdin);

// Обработка команды whatis
void process_whatis(istream &in)
{
 char buf[256];
// Один параметр - номер команды или имя гнезда
 in >> buf;
 cmdinfo *c = find_command(uint8(atoi(buf)));
 if (!c) {
// Если параметр - не число...
  connector *ct = find_connector(strupr(buf));
  if (!ct) cout << "Неизвестная команда или гнездо " << buf << endl;
  else {
   cout << "Гнездо " << buf << endl << ct->descr << endl
        << "Значение: " << int(ct->value) << endl;
  }
 } else {
  cout << "Команда: " << int(c->opcode) << ": " << c->name << endl;
  uint8 *p = c->noncompat;
  if (p) {
   cout << "Не может быть выполнена вместе с:\n";
   while(*p) {
    cmdinfo *nc = find_command(*p);
    cout << "\t" << int(nc->opcode) << ": " << nc->name << endl;
    p++;
   }
  }
 }
}

// Обработка команд set*
void process_seta(istream &in)
{
 char buf[128];
 int shift;
 in >> buf >> shift;
 set_rga(strtoul(buf, NULL, 2)<<shift);
 recalculate_connections(connections);
}

void process_setb(istream &in)
{
 char buf[128];
 int shift;
 in >> buf >> shift;
 set_rgb(strtoul(buf, NULL, 2)<<shift);
 recalculate_connections(connections);
}

void process_setc(istream &in)
{
 char buf[128];
 in >> buf;
 set_counter(strtoul(buf, NULL, 2));
 recalculate_connections(connections);
}

void process_sets(istream &in)
{
 char buf[128];
 int shift;
 in >> buf >> shift;
 set_sum(strtoul(buf, NULL, 2)<<shift);
 recalculate_connections(connections);
}

void process_setma(istream &in)
{
 char buf[128];
 in >> buf;
 set_addr(strtoul(buf, NULL, 10));
}

void process_setm(istream &in)
{
 char buf[128];
 in >> buf;
 set_mem(strtoul(buf, NULL, 2));
}

// Команда show - вывод состояния эмулятора
void process_show()
{
 char buf[128];
 itoa(rga, buf, 2);
 cout << "\nRGA     = " << buf << " (dec: " << rga << ")";
 itoa(rgb, buf, 2);
 cout << "\nRGB     = " << buf << " (dec: " << rgb << ")";
 itoa(sum, buf, 2);
 cout << "\nSUM     = " << buf << " (dec: " << sum << ")";
 itoa(mem, buf, 2);
 cout << "\nПАМЯТЬ  = " << buf << " (dec: " << mem << ")";
 itoa(counter, buf, 2);
 cout << "\nСЧЕТЧИК = " << buf << " (dec: " << counter << ")";
 itoa(addr, buf, 2);
 cout << "\nРАМК    = " << buf << " (dec: " << addr << ")";
 cout << "\nАдресация: ";
 switch(amode) {
  case natural:  cout << "естественная"; break;
  case forced1:  cout << "принудительная с одним адресом"; break;
  case forced2:  cout << "принудительная с двумя адресами"; break;
  case forcedma: cout << "принудительная с ветвлением по нескольким направлениям"; break;
 }
 cout << "\nРежим выполнения: ";
 switch(smode) {
  case trace: cout << "пошаговый\n"; break;
  case eauto: cout << "автоматический\n"; break;
 }
}

// Функция, загружающая 
char *load_help(const char *name)
{
 char buf[512];
 strcpy(buf, "help\\"); strcat(buf, name);
 FILE *fp = fopen(buf, "rb");
 if (!fp) return NULL;
 fseek(fp, 0, SEEK_END);
 int size = ftell(fp);
 fseek(fp, 0, SEEK_SET);
 char *buffer;
 try {
  buffer = new char[size+1];
 }
 catch(bad_alloc) {
  fclose(fp);
  return NULL;
 }
 fread(buffer, 1, size, fp);
 buffer[size] = '\0';
 fclose(fp);
 return buffer;
}

void process_help(istream &in)
{
 char buf[256];
 in >> buf;
 char *ptr = (char*)(load_help(buf));
 if (!ptr) {
  cout << "Невозможно вывести страницу помощи для " << buf << "!" << endl;
 } else cout << ptr << endl;
 delete(ptr);
}

void process_cmd(istream &in)
{
 char buf[255];
 in.getline(buf, 255);
 microcommand *mp = parse_line(list ? find_prev(list) : NULL, buf);
 try {
  check_command(mp->cmd);
  if (!list) list = mp;
  cout << "Команда добавлена" << endl;
 }
 catch(compat_exception ex) {
  list = remove(mp);
  cout << "Команды " << (int)ex.code1 << " и " << (int)ex.code2 << " не могут быть выполнены вместе!" << endl;
 }
}

void process_list()
{
 if (!list) cout << "Микропрограмма пуста!\n";
 else {
  microcommand *ptr = list;
  do {
   char buf[512];
   deparse_line(ptr, buf);
   cout << buf << endl;
   ptr = ptr->next;
  } while(ptr!=list);
 }
}

void process_cl()
{
 if (list) {
  clear(list);
  list = NULL;
  cout << "Микропрограмма очищена\n";
 }
}

void process_clc()
{
 if (connections) {
  clear(connections);
  connections = NULL;
  cout << "Все соединения удалены\n";
 }
}

void process_listc()
{
 if (!connections) {cout << "Соединений не обнаружено!\n"; return;}
 cable *ptr = connections;
 do {
  cout << ptr->first->name << " <--> " <<  ptr->second->name << endl;
  ptr = ptr->next;
 } while(ptr!=connections);
}

void process_link(istream &in)
{
 char buf[64], buf2[64];
 in >> buf >> buf2;
 cable *nc = add_connection(connections, strupr(buf), strupr(buf2));
 if (!nc) {
  cout << "Невозможно соединить!\n";
  return;
 }
 if (!connections) connections = nc;
 cout << "Соединение добавлено\n";
}

void process_unlink(istream &in)
{
 char buf[64], buf2[64];
 in >> buf >> buf2;
 cable *nc = find_connection(connections, strupr(buf), strupr(buf2));
 if (!nc) {cout << "Нечего удалять!\n"; return;}
 connections = remove(nc);
}

void process_rm(istream &in)
{
 dword addr;
 in >> addr;
 if (!list) return;
 microcommand *mc = search_addr(list, addr);
 if (!mc) {cout << "Нечего удалять: адрес " << addr << " отсутствует\n"; return;}
 microcommand *prev = remove(mc);
 if (mc==list) list = prev;
 cout << "Команда удалена\n";
}

void process_load(istream &in)
{
 char buf[256];
 char *ptr;
 in.getline(buf, 256);
 ptr = buf; while(isspace(*ptr) && *ptr) ptr++;
 ifstream ifs(ptr, ios::in);
 if (!ifs) {cout << "Невозможно открыть файл " << ptr << "!\n"; return;}
 cuemu_notify_func_pointer fp = cuemu_notify_func;
 cuemu_notify_func = NULL;
 process_stream(ifs, false);
 cuemu_notify_func = fp;
}

void process_save(istream &in)
{
 char buf[512], *ptr;
 in.getline(buf, 512);
 ptr = buf; while(isspace(*ptr) && *ptr) ptr++;
 ofstream ofs(ptr, ios::out);
 if (!ofs) {cout << "Невозможно создать файл " << ptr << " !\n"; return;}
 ofs << "cl\nclc\n";
 switch(amode) {
  case natural:  ofs << "am n\n"; break;
  case forced1:  ofs << "am f1\n"; break;
  case forced2:  ofs << "am f2\n"; break;
  case forcedma: ofs << "am fm\n"; break;
 }
 switch(smode) {
  case trace:    ofs << "sm t\n"; break;
  case eauto:    ofs << "sm a\n"; break;
 }
 if (list) {
  microcommand *ptr = list;
  do {
   deparse_line(ptr, buf);
   ofs << "cmd " << buf << endl;
   ptr = ptr->next;
  } while(ptr!=list);
 }
 if (connections) {
  cable *ptr = connections;
  do {
   ofs << "link " << ptr->first->name << ' ' << ptr->second->name << endl;
   ptr = ptr->next;
  } while(ptr!=connections);
 }
 ultoa(rga, buf, 2);
 ofs << "seta " << buf << " 0\n";
 ultoa(rgb, buf, 2);
 ofs << "setb " << buf << " 0\n";
 ultoa(sum, buf, 2);
 ofs << "sets " << buf << " 0\n";
 ultoa(mem, buf, 2);
 ofs << "setm " << buf << '\n';
 ofs << "setma " << addr << '\n';
 ofs << "setc " << counter << '\n';
}

void process_init()
{
 init_registers();
 init_connectors();
 out_connector(connections, C_ONE, true);
}

void process_am(istream &in)
{
 char buf[256];
 in >> buf;
 if (!strcmp(buf, "n")) amode = natural;
 else if (!strcmp(buf, "f1")) amode = forced1;
 else if (!strcmp(buf, "f2")) amode = forced2;
 else if (!strcmp(buf, "fm")) amode = forcedma;
 else cout << "Некорректный параметр!\n";
}

void process_sm(istream &in)
{
 char buf[256];
 in >> buf;
 if (!strcmp(buf, "t")) smode = trace;
 else if (!strcmp(buf, "a")) smode = eauto;
 else cout << "Некорректный параметр!\n";
}

void process_exec()
{
 execute(list, connections);
 cout << "Теперь РАМК = " << addr << endl;
}

TCriticalSection cuemu_mutex;
bool should_terminate = false;

void process_stream(istream &in, bool is_stdin)
{
 char buf[256];
 if (is_stdin) {
  cout << "\nТочность эмуляции не гарантируется :)";
  cout << "\nВведите \"help all\" для получения списка команд";
 }
 while(true) {
  if (is_stdin) {cout << "\nКоманда $ "; cout.flush(); in.clear();}
  in >> buf;
  TCriticalSection::TLock lock(cuemu_mutex);
  if (!is_stdin && in.eof()) break;
  if (!strcmp(buf, "whatis"))        process_whatis(in);
  else if (!strcmp(buf, "am"))       process_am(in);
  else if (!strcmp(buf, "cmd"))      process_cmd(in);
  else if (!strcmp(buf, "ls"))       process_list();
  else if (!strcmp(buf, "lsc"))      process_listc();
  else if (!strcmp(buf, "load"))     process_load(in);
  else if (!strcmp(buf, "sm"))       process_sm(in);
  else if (!strcmp(buf, "cl"))       process_cl();
  else if (!strcmp(buf, "clc"))      process_clc();
  else if (!strcmp(buf, "exec"))     process_exec();
  else if (!strcmp(buf, "init"))     process_init();
  else if (!strcmp(buf, "link"))     process_link(in);
  else if (!strcmp(buf, "unlink"))   process_unlink(in);
  else if (!strcmp(buf, "rm"))       process_rm(in);
  else if (!strcmp(buf, "seta"))     process_seta(in);
  else if (!strcmp(buf, "setb"))     process_setb(in);
  else if (!strcmp(buf, "setc"))     process_setc(in);
  else if (!strcmp(buf, "setm"))     process_setm(in);
  else if (!strcmp(buf, "setma"))    process_setma(in);
  else if (!strcmp(buf, "sets"))     process_sets(in);
  else if (!strcmp(buf, "save"))     process_save(in);
  else if (!strcmp(buf, "show"))     process_show();
  else if (!strcmp(buf, "help"))     process_help(in);
  else if (!strcmp(buf, "exit"))     break;
  else cout << "Неизвестная команда!\nВведите \"help all\" для получения списка команд";
  if (cuemu_notify_func) cuemu_notify_func(buf, cuemu_notify_data);  
 }
}

void set_stdout(ostream &ofs)
{
 __sout = &ofs;
}

ostream &get_stdout() {return *__sout;}
