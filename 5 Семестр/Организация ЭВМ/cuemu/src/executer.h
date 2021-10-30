#ifndef CUEMU_EXECUTER_H
#define CUEMU_EXECUTER_H

#include "cstorage.h"
#include "connect.h"

// В BC++ 5 new генерирует не bad_alloc (ANSI C++), а xalloc
#if defined(__BORLANDC__) && __BORLANDC__<=0x520
#define bad_alloc xalloc
#include <except.h>
#endif

// Коды микроопераций
#define OP_CL_RGA_SIGN 1
#define OP_RD_RGA_SIGN 2
#define OP_INV_RGA_SIGN 3
#define OP_GET_RGA_SIGN 4
#define OP_CL_RGA_DIG 6
#define OP_RD_RGA_DIG 7
#define OP_SET_RGA_MSB 8
#define OP_SHR_RGA 9
#define OP_GET_RGA_INV 5
#define OP_GET_RGA 10

#define OP_CL_RGB_SIGN 25
#define OP_RD_RGB_SIGN 26
#define OP_INV_RGB_SIGN 27
#define OP_GET_RGB_SIGN 28
#define OP_GET_RGB_INV 29
#define OP_CL_RGB_DIG 30
#define OP_RD_RGB_DIG 31
#define OP_SET_RGB_LSB 32
#define OP_SHL_RGB 33
#define OP_GET_RGB 34

#define OP_CL_SUM_SIGN 11
#define OP_RD_SUM_SIGN 12
#define OP_INV_SUM_SIGN 13
#define OP_GET_SUM_SIGN 14
#define OP_MK_SUM_INV 15
#define OP_GET_SUM 16
#define OP_GET_SUM_INV 17
#define OP_CL_SUM_DIG 18
#define OP_RD_SUM_DIG 19
#define OP_SET_SUM_LSB 20
#define OP_SET_SUM_MSB 21
#define OP_INV_SUM_DIG 22
#define OP_CARRY_RIGHT 23
#define OP_CARRY_LEFT 24

#define OP_GET_MEM 35
#define OP_STOP 36
#define OP_DEC_COUNTER 37

// Типы адресации
enum addressing {
 natural, forced2, forced1, forcedma
};

// Режимы выполнения
enum stepping {
 trace, eauto
};

// Маски для вычислений
#define REG_MASK      0x3FF
#define SUM_MASK      0x7FF
#define SIGNUM_MASK   0x200
#define OVERFLOW_MASK 0x400
#define DIGITS_MASK   0x1FF
#define COUNTER_MASK  0xF

#define MIN_ADDR      0
#define MAX_ADDR      30

#define MSB_MASK      (SIGNUM_MASK>>1)
#define LSB_MASK      1

// Структура информации о микрооперации
struct cmdinfo {
 uint8 opcode;          // Код
 const char *name;      // Описание микрооперации
 uint8 *noncompat;      // Указатель на массив микроопераций, не совместимых
                        // с этой (массив завершается нулем)
};

// Это исключение генерируется при попытке добавить две несовместимые инструкции
struct compat_exception {
 uint8 code1;
 uint8 code2;
};

// Массив описателей команд
extern cmdinfo commands[];

// Регистры
extern dword rga, rgb, sum, mem, counter, addr;

// Временная область для хранения данных "шины"
extern dword temp_area;

extern addressing amode;      // Режим адресации
extern stepping smode;        // Режим выполнения

extern int max_sum_iters;     // Максимальное число циклических переносов

// Функции установки регистров
inline void set_rga(dword dw)
{
 rga = dw & REG_MASK;
}

inline void set_rgb(dword dw)
{
 rgb = dw & REG_MASK;
}

inline void set_mem(dword dw)
{
 mem = dw & REG_MASK;
}

inline void set_sum(dword dw)
{
 sum = dw & SUM_MASK;
}

inline void set_counter(dword dw)
{
 counter = dw & COUNTER_MASK;
}

void set_addr(dword dw);
cmdinfo *find_command(uint8 cmd);
bool is_compatible(uint8 code1, uint8 code2);
void check_command(qword cmd);
void init_registers();
bool do_execute(qword cmd, cable *c);
void execute(microcommand *list, cable *connect);

inline void recalculate_connections(cable *c)
{
 do_execute(0, c);
}


#endif