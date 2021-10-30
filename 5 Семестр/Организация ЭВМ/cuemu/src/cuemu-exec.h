#ifndef CUEMU_EXEC_H
#define CUEMU_EXEC_H
// ������� ������ � ����������� ��������� � cuemu-gui
#include <owl/pch.h>
#include "cuemu.h"

// ������������ ������ �������, ������������ ����� PassCuemuCommandString
#define COMMAND_BUFFER_SIZE 4096

// ���������� ������ ��������� ���������� ������
extern HANDLE hConsoleThread;
// ���� ����������. ���� true, �� ����� ��� �������� (��� ��� �� ���������...)
extern bool terminated;

void InitConsoleThread(istream *ifs);
void TerminateConsoleThread();
void SuspendConsoleThread();
void ResumeConsoleThread();

void PassCuemuCommandString(const char *format, ...);

#endif
