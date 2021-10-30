#include <owl/framewin.h>
#include <owl/tabctrl.h>
#include <owl/opensave.h>
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "cuemu.h"
#include "cuemu-controls.h"
#include "cuemu-gui-alu.h"
#include "cuemu-gui-cu.h"
#include "cuemu-gui-conn.h"
#include "cuemu-gui-info.h"
#include "cuemu-gui-decoder.h"
#include "cuemu-exec.h"
#include "cuemu-rc.rh"

// Индексы страниц в TabControl'е главного окна
int index_alu_tab;               // АЛУ
int index_cu_tab;                // УУ
int index_connections_tab;       // Соединения
int index_info_tab;              // Информация
int index_decoder_tab;           // Декодер

TFrameWindow *main_window = NULL;

// Класс главного окна эмулятора.
class TCuemuWindow: public TFrameWindow {
public:
 TCuemuWindow();
protected:
 TTabControl *tabctl;         // Главный TabControl
 TCuemuALU *alu;              // Страница АЛУ
 TCuemuCU *cu;                // Страница УУ
 TCuemuConnections *conn;     // Страница соединений
 TCuemuInfo *info;            // Страница информации
 TCuemuDecoder *decoder;      // Страница декодера
 TMenu menu;                  // Меню окна
 TResult EvCommand(uint p1, THandle p2, uint p3) {Invalidate(); return TFrameWindow::EvCommand(p1, p2, p3);}
 void SetupWindow();
// Будет вызываться каждые 200 мс. Если поток hConsoleThread завершился,
// то закрываем окно и выходим из программы
 void EvTimer(uint) {
  if (terminated==true) {terminated = false; CloseWindow();}
 }
// При закрытии окна приходится завершать и hConsoleThread
// Это не самый чистый метод выхода...
 void EvClose() {TerminateConsoleThread(); CloseWindow();}
 void EvSize(uint, TSize &);
 void EvCommandEnable(TCommandEnabler &en) {en.Enable(true);}
// Эта функция вызывается, когда Windows запросит допустимые размеры окна
// Здесь размеры фиксированы
 void EvGetMinMaxInfo(MINMAXINFO &mm)
  {mm.ptMinTrackSize.x = mm.ptMaxTrackSize.x = 750;
   mm.ptMinTrackSize.y = mm.ptMaxTrackSize.y = 580;}
 void CmExit() {TerminateConsoleThread(); CloseWindow();}
 void CmExecuteFile();
 void CmSaveFile();
 void CmChangeTab(TNotify &);
 void CmInitialize();
 void CmExecute();
 void CmClear();
 void CmUnlinkAll();
 void CmTrace();
 void CmAuto();
 void CmNatural();
 void CmForced1();
 void CmForced2();
 void CmForced4();
 void CmHelpAll();
 void CmLs();
 void CmLsc();
 void CmShow();
 void CmSetRegs();
 void CmHideConsole();
 static void NotifyChanges(const char *, void *data);
 DECLARE_RESPONSE_TABLE(TCuemuWindow);
};

// Класс приложения эмулятора
class TCuemuApp: public TApplication {
public:
 TCuemuApp(): TApplication() {;}
// Инициализация главного окна. Создаем TCuemuWindow и делаем его главным окном
// Память будет автоматически освобождена в деструкторе TApplication
 void InitMainWindow() {SetMainWindow(new TCuemuWindow);}
 void Terminate() {BreakMessageLoop = true;}
};

// Обработчик различных событий консоли
// Позволяет, например, при нажатии Ctrl-C или закрытии консоли осуществить
// корректный выход из программы с полной очисткой
BOOL APIENTRY ConsoleEventHandler(DWORD reason)
{
// Это все описанные в Win32 Programmer's Reference события консоли (WinNT)
// Однако в последующих ОС могут быть добавлены новые
 if (reason==CTRL_C_EVENT ||
     reason==CTRL_BREAK_EVENT ||
     reason==CTRL_CLOSE_EVENT ||
     reason==CTRL_LOGOFF_EVENT ||
     reason==CTRL_SHUTDOWN_EVENT) {
  if (!main_window) exit(EXIT_FAILURE);
  TCuemuApp *app = static_cast<TCuemuApp *>(main_window->GetApplication());
  app->Terminate();
  main_window = NULL;
  return true;
 } else return false;
}

// Конструктор TCuemuWindow
// Меню указать обычным образом не получается (при завершении
// происходит ошибка общей защиты в деструкторе TFrameWindow.
// Это похоже на ошибку в OWL)
TCuemuWindow::TCuemuWindow():
 TFrameWindow(NULL, "cuemu-gui"),
 menu(GetModuleHandle(NULL), "MAINMENU")
{
// Создаем интерфейсные объекты для TabControl'а и страниц
 tabctl = new TTabControl(this, IDC_TABCONTROL, 0, 0, 100, 100);
 alu = new TCuemuALU(this);
 cu = new TCuemuCU(this);
 conn = new TCuemuConnections(this);
 info = new TCuemuInfo(this);
 decoder = new TCuemuDecoder(this);
// Используемая таблица горячих клавиш
 Attr.AccelTable = "MAINMENU";
// Attr.Menu = "MAINMENU";       // Должно бы быть... но не работает
}

// Обработчик изменения размера окна
void TCuemuWindow::EvSize(uint, TSize &)
{
 TRect rc = GetClientRect();
 tabctl->SetWindowPos(NULL, rc, SWP_DRAWFRAME | SWP_NOZORDER);
}

// Обработчик команды меню "Выполнить файл"
void TCuemuWindow::CmExecuteFile()
{
// Запросим имя файла
 TFileOpenDialog::TData
 data(OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
      "Все файлы (*.*)|*.*|", 0, "", "*");
 if (TFileOpenDialog(this, data).Execute() == IDOK) {
// Если в окне выбора файла пользователь нажал OK...
  PassCuemuCommandString("load %s", data.FileName);
 }
}

// Обработчик команды меню "Сохранить файл"
void TCuemuWindow::CmSaveFile()
{
 TFileSaveDialog::TData
 data(OFN_OVERWRITEPROMPT, "Все файлы (*.*)|*.*|", 0, "", "txt");
 if (TFileSaveDialog(this, data).Execute() == IDOK) {
  PassCuemuCommandString("save %s", data.FileName);
 }
}

// Обработчик команды меню "Инициализация"
void TCuemuWindow::CmInitialize()
{
 int i = MessageBox("Иницилизировать эмулятор?\nЭто сбросит регистры в начальные значения",
                    "Инициализация", MB_ICONQUESTION | MB_YESNO);
 if (i==IDYES) PassCuemuCommandString("init");
}

// Обработчик команды меню "Выполнить"
void TCuemuWindow::CmExecute()
{
 PassCuemuCommandString("exec");
}

// Обработчик команды меню "Очистить микропрограмму"
void TCuemuWindow::CmClear()
{
 int i = MessageBox("Очистить микропрограмму ?", "Удаление",
                    MB_ICONQUESTION | MB_YESNO);
 if (i==IDYES) PassCuemuCommandString("cl");
}

// Обработчик команды меню "Удалить соединения"
void TCuemuWindow::CmUnlinkAll()
{
 int i = MessageBox("Удалить все соединения и иницилизировать эмулятор ?", "Удаление",
                    MB_ICONQUESTION | MB_YESNO);
 if (i==IDYES) PassCuemuCommandString("clc\ninit");
}

// Обработчики команд меню выбора режима выполнения
void TCuemuWindow::CmTrace()
{
 PassCuemuCommandString("sm t");
}

void TCuemuWindow::CmAuto()
{
 PassCuemuCommandString("sm a");
}

// Обработчики команд выбора режима адресации
void TCuemuWindow::CmNatural()
{
 PassCuemuCommandString("am n");
}

void TCuemuWindow::CmForced1()
{
 PassCuemuCommandString("am f1");
}

void TCuemuWindow::CmForced2()
{
 PassCuemuCommandString("am f2");
}

void TCuemuWindow::CmForced4()
{
 PassCuemuCommandString("am fm");
}

// Обработчики команд подменю "Консоль"
void TCuemuWindow::CmHelpAll()
{
 PassCuemuCommandString("help all");
}

void TCuemuWindow::CmLs()
{
 PassCuemuCommandString("ls");
}

void TCuemuWindow::CmLsc()
{
 PassCuemuCommandString("lsc");
}

void TCuemuWindow::CmShow()
{
 PassCuemuCommandString("show");
}

// Обработка команды "Убрать консоль"
void TCuemuWindow::CmHideConsole()
{
// Попытаемся получить дескриптор окна консоли. Эта попытка может и провалиться,
// например, если другая программа изменила заголовок этой консоли...
 THandle handle = ::FindWindow("ConsoleWindowClass", "Консоль CUEMU");
 if (!handle) {
  MessageBox("Консоль не найдена!", "Dazed and confused", MB_ICONEXCLAMATION | MB_OK);
  return;
 }
// Состояние консоли можно определить по наличию метки у элемента меню
 if (menu.GetMenuState(IDM_HIDECONSOLE, MF_BYCOMMAND) & MF_CHECKED) {
  ::ShowWindow(handle, SW_SHOW);
  menu.CheckMenuItem(IDM_HIDECONSOLE, MF_UNCHECKED | MF_BYCOMMAND);
 } else {
  ::ShowWindow(handle, SW_HIDE);
  menu.CheckMenuItem(IDM_HIDECONSOLE, MF_CHECKED | MF_BYCOMMAND);
 }
}

// Вызывается при создании окна
void TCuemuWindow::SetupWindow() {
 TFrameWindow::SetupWindow();
// Таймер нужен для периодической проверки потока hConsoleThread (cuemu-exec.cpp)
// на завершение (по команде exit)
 SetTimer(0, 200);
 SetMenu(menu);
// Шрифт по умолчанию - почему-то System.
// Системный шрифт для диалогов обычно выглядит лучше
 tabctl->SetWindowFont((HFONT)::GetStockObject(ANSI_VAR_FONT), true);
// Создаем страницы
 index_alu_tab = tabctl->Add("АЛУ");
 index_cu_tab = tabctl->Add("УУ");
 index_connections_tab = tabctl->Add("Соединения");
 index_info_tab = tabctl->Add("Информация");
 index_decoder_tab = tabctl->Add("Декодер");
// Диалоги, в отличие от обычных окон, в SetupWindow() не создаются,
// поэтому нужно создать их вручную. Create() создает немодальный диалог
// В один момент должна быть отображена только одна из страниц
 alu->Create();
 alu->SetWindowPos(NULL, 10, 30, 650, 480, SWP_NOZORDER | SWP_DRAWFRAME);
 cu->Create();
 cu->SetWindowPos(NULL, 10, 30, 650, 480, SWP_NOZORDER | SWP_DRAWFRAME);
 cu->ShowWindow(SW_HIDE);
 conn->Create();
 conn->ShowWindow(SW_HIDE);
 info->Create();
 info->ShowWindow(SW_HIDE);
 decoder->Create();
 decoder->ShowWindow(SW_HIDE);
// Регистрируем функцию NotifyChanges в cuemu, чтобы она вызывалась при
// завершении каждой команды
 cuemu_notify_func = NotifyChanges;
 cuemu_notify_data = this;
 main_window = this;
// Регистрируем обработчик событий консоли
 SetConsoleCtrlHandler(ConsoleEventHandler, true);
}

// Эта функция должна вызываться при завершении каждой команды cuemu
// Первый параметр - имя команды (не используется)
// data - переданные при регистрации данные (здесь указатель на TCuemuWindow)
void TCuemuWindow::NotifyChanges(const char *, void *data)
{
 TCuemuWindow *This = (TCuemuWindow *)data;
// Обновим страницы главного окна
 This->alu->Update();
 This->conn->Update();
 This->cu->Update();
 This->decoder->Update();
// Только один из элементов меню выбора режима адресации должен быть отмечен
 switch(amode) {
  case natural:
   This->menu.CheckMenuItem(IDM_NATURAL, MF_BYCOMMAND | MF_CHECKED);
   This->menu.CheckMenuItem(IDM_FORCED1, MF_BYCOMMAND | MF_UNCHECKED);
   This->menu.CheckMenuItem(IDM_FORCED2, MF_BYCOMMAND | MF_UNCHECKED);
   This->menu.CheckMenuItem(IDM_FORCED4, MF_BYCOMMAND | MF_UNCHECKED);
  break;
  case forced1:
   This->menu.CheckMenuItem(IDM_NATURAL, MF_BYCOMMAND | MF_UNCHECKED);
   This->menu.CheckMenuItem(IDM_FORCED1, MF_BYCOMMAND | MF_CHECKED);
   This->menu.CheckMenuItem(IDM_FORCED2, MF_BYCOMMAND | MF_UNCHECKED);
   This->menu.CheckMenuItem(IDM_FORCED4, MF_BYCOMMAND | MF_UNCHECKED);
  break;
  case forced2:
   This->menu.CheckMenuItem(IDM_NATURAL, MF_BYCOMMAND | MF_UNCHECKED);
   This->menu.CheckMenuItem(IDM_FORCED1, MF_BYCOMMAND | MF_UNCHECKED);
   This->menu.CheckMenuItem(IDM_FORCED2, MF_BYCOMMAND | MF_CHECKED);
   This->menu.CheckMenuItem(IDM_FORCED4, MF_BYCOMMAND | MF_UNCHECKED);
  break;
  case forcedma:
   This->menu.CheckMenuItem(IDM_NATURAL, MF_BYCOMMAND | MF_UNCHECKED);
   This->menu.CheckMenuItem(IDM_FORCED1, MF_BYCOMMAND | MF_UNCHECKED);
   This->menu.CheckMenuItem(IDM_FORCED2, MF_BYCOMMAND | MF_UNCHECKED);
   This->menu.CheckMenuItem(IDM_FORCED4, MF_BYCOMMAND | MF_CHECKED);
  break;
 }
// Отметка элемента меню выбора режима выполнения
 switch(smode) {
  case trace:
   This->menu.CheckMenuItem(IDM_TRACE, MF_BYCOMMAND | MF_CHECKED);
   This->menu.CheckMenuItem(IDM_AUTOMODE, MF_BYCOMMAND | MF_UNCHECKED);
  break;
  case eauto:
   This->menu.CheckMenuItem(IDM_TRACE, MF_BYCOMMAND | MF_UNCHECKED);
   This->menu.CheckMenuItem(IDM_AUTOMODE, MF_BYCOMMAND | MF_CHECKED);
  break;
 }
}

// Эта функция вызывается при смене выделенной страницы
// Т.к. TabControl никак не может управлять связанными с ним страницами,
// то отображение нужной страницы приходится производить вручную
void TCuemuWindow::CmChangeTab(TNotify &)
{
 int i = tabctl->GetSel();
 if (i==index_alu_tab) {
  conn->ShowWindow(SW_HIDE);
  cu->ShowWindow(SW_HIDE);
  info->ShowWindow(SW_HIDE);
  decoder->ShowWindow(SW_HIDE);
  alu->ShowWindow(SW_SHOW);
 } else if (i==index_cu_tab) {
  alu->ShowWindow(SW_HIDE);
  conn->ShowWindow(SW_HIDE);
  info->ShowWindow(SW_HIDE);
  decoder->ShowWindow(SW_HIDE);
  cu->ShowWindow(SW_SHOW);
 } else if (i==index_connections_tab) {
  alu->ShowWindow(SW_HIDE);
  cu->ShowWindow(SW_HIDE);
  info->ShowWindow(SW_HIDE);
  decoder->ShowWindow(SW_HIDE);
  conn->ShowWindow(SW_SHOW);
 } else if (i==index_info_tab) {
  alu->ShowWindow(SW_HIDE);
  cu->ShowWindow(SW_HIDE);
  conn->ShowWindow(SW_HIDE);
  decoder->ShowWindow(SW_HIDE);
  info->ShowWindow(SW_SHOW);
 } else {
  alu->ShowWindow(SW_HIDE);
  cu->ShowWindow(SW_HIDE);
  conn->ShowWindow(SW_HIDE);
  info->ShowWindow(SW_HIDE);
  decoder->ShowWindow(SW_SHOW);
 }
}

// Таблица обработчиков событий TCuemuWindow
DEFINE_RESPONSE_TABLE1(TCuemuWindow, TFrameWindow)
 EV_WM_TIMER,
 EV_WM_SIZE,
 EV_WM_CLOSE,
 EV_WM_GETMINMAXINFO,
 EV_COMMAND(IDM_EXIT, CmExit),
 EV_COMMAND(IDM_EXECUTEFILE, CmExecuteFile),
 EV_COMMAND(IDM_SAVEFILE, CmSaveFile),
 EV_COMMAND(IDM_INITIALIZE, CmInitialize),
 EV_COMMAND(IDM_EXECUTE, CmExecute),
 EV_COMMAND(IDM_CLEAR, CmClear),
 EV_COMMAND(IDM_UNLINKALL, CmUnlinkAll),
 EV_COMMAND(IDM_NATURAL, CmNatural),
 EV_COMMAND(IDM_FORCED1, CmForced1),
 EV_COMMAND(IDM_FORCED2, CmForced2),
 EV_COMMAND(IDM_FORCED4, CmForced4),
 EV_COMMAND(IDM_TRACE, CmTrace),
 EV_COMMAND(IDM_AUTOMODE, CmAuto),
 EV_COMMAND(IDM_HELPALL, CmHelpAll),
 EV_COMMAND(IDM_LS, CmLs),
 EV_COMMAND(IDM_LSC, CmLsc),
 EV_COMMAND(IDM_SHOW, CmShow),
 EV_COMMAND(IDM_HIDECONSOLE, CmHideConsole),
 EV_TCN_SELCHANGE(IDC_TABCONTROL, CmChangeTab),
END_RESPONSE_TABLE;

// Заменитель main() для программ OWL
int OwlMain(int /*argc*/, char ** /*argv*/)
{
// Консоль приходится создать, т.к. программа имеет тип Win32 GUI
// (если Win32 Console, то не работает OWL...)
 AllocConsole();
 SetConsoleTitle(chartooem("Консоль CUEMU"));
// Текст будет ярко белым на черном фоне
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                         FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
                         | FOREGROUND_INTENSITY);
// Потоки cin и cout никак не связаны с новой консолью
// Вывод в них не дает никакого эффекта. Приходится создать новые потоки
// _open_osfhandle() - нестандартная функция, создающая дескриптор файла
// UNIX (целое число) для дескриптора файла Win32 (HANDLE)
 ifstream __cin(_open_osfhandle(long(GetStdHandle(STD_INPUT_HANDLE)), O_RDONLY));
 if (!__cin) return 1;
 ofstream __cout(_open_osfhandle(long(GetStdHandle(STD_OUTPUT_HANDLE)), 0));
 if (!__cout) return 2;
 set_stdout(__cout);
 __cout << "CUEMU-GUI" << endl;
 __cout << "Copyright (C) Vigura Anton (2006)" << endl;
// Создадим поток обработки команд консоли
 InitConsoleThread(&__cin);
// И запустим OWL GUI
 return TCuemuApp().Run();
}