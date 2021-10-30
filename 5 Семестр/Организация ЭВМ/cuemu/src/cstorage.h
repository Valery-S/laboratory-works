// Типы и функции, использующиеся для хранения и поиска микрокоманд
#ifndef CUEMU_STORAGE_H
#define CUEMU_STORAGE_H

// Различные типы целых
typedef unsigned __int32 dword;  // двойное слово
typedef unsigned __int64 qword;  // учетверенное слово
typedef unsigned __int8 uint8;   // байт

// Элемент односвязного циклического списка микрокоманд
struct microcommand {
 dword addr;            // адрес
 qword cmd;             // битовое поле микроопераций
 microcommand *next;    // указатель на следующий элемент
};

// Макросы извлечения различной информации из битового поля микроопераций

// Извлекает собственно битовое поле микроопераций
#define GET_CMD(cmd) ((cmd) & 0x1FFFFFFFFF)
// Извлекает поле указателя проверяемого условия
#define GET_CONDITION(cmd) (dword(((cmd) >> 37) & 0x7))
// Извлекает адрес перехода №1 (разряды 41-45)
#define GET_ADDR1(cmd) (dword(((cmd) >> 40) & 0x1F))
// Извлекает адрес перехода №2 (разряды 46-50)
#define GET_ADDR2(cmd) (dword(((cmd) >> 45) & 0x1F))
// Извлекает поле указателя проверяемой группы
#define GET_GROUP(cmd) (dword(((cmd) >> 43) & 0x3))

// Формирует число с одним установленным битом, соответствующим микрооперации
// cmd_index
#define MK_OP(cmd_index) (qword(1) << (cmd_index-1))
// Формирует группу из двух разрядов: младшего low и старшего high
#define MK_GROUP(low,high) ((dword(high)<<1) | dword(low))

// Проверяет, присутствует ли микрооперация mc в битовом поле операций cmd
#define IS_PRESENT(cmd,mc) ((cmd) & MK_OP(mc))

// Прототипы функций
microcommand *add(microcommand *list);
microcommand *find_prev(microcommand *list);
microcommand *remove(microcommand *list);
void clear(microcommand *list);
microcommand *search_addr(microcommand *list, dword addr);
microcommand *parse_line(microcommand *list, const char *line);
void deparse_line(microcommand *list, char *buf);

#define CHARTOOEM_BUF_SIZE 1024
char *chartooem(const char *str);

#endif