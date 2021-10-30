#ifndef CUEMU_EXEC_H
#define CUEMU_EXEC_H
// Функции работы с консольными командами в cuemu-gui
#include <owl/pch.h>
#include "cuemu.h"

// Максимальный размер команды, передаваемой через PassCuemuCommandString
#define COMMAND_BUFFER_SIZE 4096

// Дескриптор потока обработки консольных команд
extern HANDLE hConsoleThread;
// Флаг завершения. Если true, то поток был завершен (или еще не стартовал...)
extern bool terminated;

void InitConsoleThread(istream *ifs);
void TerminateConsoleThread();
void SuspendConsoleThread();
void ResumeConsoleThread();

void PassCuemuCommandString(const char *format, ...);

#endif
