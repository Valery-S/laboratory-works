#include "cuemu-exec.h"
#include <process.h>
#include <cstdarg>
#include <strstrea.h>

bool terminated = true;

HANDLE hConsoleThread;

// ������� ������. ����� ����������� �� ��� ���, ���� ������������ �� ������
// ������� exit � �������
void _USERENTRY ThreadProc(void *arg)
{
 istream *ifs = (istream *)arg;
 process_stream(*ifs, true);
 terminated = true;
}

// �������� �����, �������� ������� �� *ifs
void InitConsoleThread(istream *ifs)
{
 terminated = false;
 hConsoleThread = (HANDLE)_beginthread(ThreadProc, 65536, ifs);
}

// ��������� ����� ��������� ���������� ������.
void TerminateConsoleThread()
{
 if (!terminated) {
// ������� �������: TerminateThread() �� ������ ������� �������, � ������
// ��������� ���������� ������. ��������� ����� ��� ����� ����� ��� �����
// ������� �� ���������
// ������ ����� ����� ������, �.�. ����� hConsoleThread ������� �����
// ������� "����", ������ ����� ������� � istream::operator>>
  TerminateThread(hConsoleThread, 0);
 }
}

// �������� ���������������� ����� hConsoleThread
void SuspendConsoleThread()
{
// ������ cuemu_mutex ���������� �� ����� ����, ������� ������������ �������
// (�� �� ������ ��). ����� �� �������� ����� �� ��������� ������, ���� ��
// ������ ����� ������������ �����
 TCriticalSection::TLock lock(cuemu_mutex);
 SuspendThread(hConsoleThread);
}

// ������������ ���������� ������ hConsoleThread
void ResumeConsoleThread()
{
 ResumeThread(hConsoleThread);
}

// ��� ������� �������� ������� ���������. ��������� ������ � ��������� ���������
// ������������� ����������� ������� printf()
void PassCuemuCommandString(const char *format, ...)
{
 va_list vl;
 va_start(vl, format);
 char buf[COMMAND_BUFFER_SIZE];
 vsprintf(buf, format, vl);         // ��������� ������ �������
 va_end(vl);
 SuspendConsoleThread();            // ������������ ����� ��������� ������
 get_stdout() << buf << endl;
 strcat(buf, "\n");
 istrstream iss(buf);               // �������� ���������� �������
 process_stream(iss, false);
 get_stdout() << endl << chartooem("������� $ ");
 get_stdout().flush();
 ResumeConsoleThread();             // ���������� ����� ��������� ������
}


