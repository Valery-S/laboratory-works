#include "cuemu-exec.h"
#include <process.h>
#include <cstdarg>
#include <strstrea.h>

bool terminated = true;

HANDLE hConsoleThread;

// Функция потока. Поток выполняется до тех пор, пока пользователь не введет
// команду exit в консоли
void _USERENTRY ThreadProc(void *arg)
{
 istream *ifs = (istream *)arg;
 process_stream(*ifs, true);
 terminated = true;
}

// Начинает поток, читающий команды из *ifs
void InitConsoleThread(istream *ifs)
{
 terminated = false;
 hConsoleThread = (HANDLE)_beginthread(ThreadProc, 65536, ifs);
}

// Завершает поток обработки консольных команд.
void TerminateConsoleThread()
{
 if (!terminated) {
// Опасный вариант: TerminateThread() не делает никакой очистки, а просто
// прерывает выполнение потока. Завершать поток ТАК можно разве что перед
// выходом из программы
// Другим путем пойти нельзя, т.к. поток hConsoleThread большую часть
// времени "спит", ожидая ввода команды в istream::operator>>
  TerminateThread(hConsoleThread, 0);
 }
}

// Временно приостанавливает поток hConsoleThread
void SuspendConsoleThread()
{
// Мутекс cuemu_mutex прикрывает ту часть кода, которая обрабатывает команды
// (но не читает их). Чтобы не прервать поток на обработке команд, этот же
// мутекс нужно использовать здесь
 TCriticalSection::TLock lock(cuemu_mutex);
 SuspendThread(hConsoleThread);
}

// Возобновляет выполнение потока hConsoleThread
void ResumeConsoleThread()
{
 ResumeThread(hConsoleThread);
}

// Эта функция передает команду эмулятору. Форматная строка и остальные параметры
// соответствуют соглашениям функции printf()
void PassCuemuCommandString(const char *format, ...)
{
 va_list vl;
 va_start(vl, format);
 char buf[COMMAND_BUFFER_SIZE];
 vsprintf(buf, format, vl);         // Формируем строку команды
 va_end(vl);
 SuspendConsoleThread();            // Приостановим поток обработки команд
 get_stdout() << buf << endl;
 strcat(buf, "\n");
 istrstream iss(buf);               // Выполним переданную команду
 process_stream(iss, false);
 get_stdout() << endl << chartooem("Команда $ ");
 get_stdout().flush();
 ResumeConsoleThread();             // Возобновим поток обработки команд
}


