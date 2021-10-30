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

// ������� ������� � TabControl'� �������� ����
int index_alu_tab;               // ���
int index_cu_tab;                // ��
int index_connections_tab;       // ����������
int index_info_tab;              // ����������
int index_decoder_tab;           // �������

TFrameWindow *main_window = NULL;

// ����� �������� ���� ���������.
class TCuemuWindow: public TFrameWindow {
public:
 TCuemuWindow();
protected:
 TTabControl *tabctl;         // ������� TabControl
 TCuemuALU *alu;              // �������� ���
 TCuemuCU *cu;                // �������� ��
 TCuemuConnections *conn;     // �������� ����������
 TCuemuInfo *info;            // �������� ����������
 TCuemuDecoder *decoder;      // �������� ��������
 TMenu menu;                  // ���� ����
 TResult EvCommand(uint p1, THandle p2, uint p3) {Invalidate(); return TFrameWindow::EvCommand(p1, p2, p3);}
 void SetupWindow();
// ����� ���������� ������ 200 ��. ���� ����� hConsoleThread ����������,
// �� ��������� ���� � ������� �� ���������
 void EvTimer(uint) {
  if (terminated==true) {terminated = false; CloseWindow();}
 }
// ��� �������� ���� ���������� ��������� � hConsoleThread
// ��� �� ����� ������ ����� ������...
 void EvClose() {TerminateConsoleThread(); CloseWindow();}
 void EvSize(uint, TSize &);
 void EvCommandEnable(TCommandEnabler &en) {en.Enable(true);}
// ��� ������� ����������, ����� Windows �������� ���������� ������� ����
// ����� ������� �����������
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

// ����� ���������� ���������
class TCuemuApp: public TApplication {
public:
 TCuemuApp(): TApplication() {;}
// ������������� �������� ����. ������� TCuemuWindow � ������ ��� ������� �����
// ������ ����� ������������� ����������� � ����������� TApplication
 void InitMainWindow() {SetMainWindow(new TCuemuWindow);}
 void Terminate() {BreakMessageLoop = true;}
};

// ���������� ��������� ������� �������
// ���������, ��������, ��� ������� Ctrl-C ��� �������� ������� �����������
// ���������� ����� �� ��������� � ������ ��������
BOOL APIENTRY ConsoleEventHandler(DWORD reason)
{
// ��� ��� ��������� � Win32 Programmer's Reference ������� ������� (WinNT)
// ������ � ����������� �� ����� ���� ��������� �����
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

// ����������� TCuemuWindow
// ���� ������� ������� ������� �� ���������� (��� ����������
// ���������� ������ ����� ������ � ����������� TFrameWindow.
// ��� ������ �� ������ � OWL)
TCuemuWindow::TCuemuWindow():
 TFrameWindow(NULL, "cuemu-gui"),
 menu(GetModuleHandle(NULL), "MAINMENU")
{
// ������� ������������ ������� ��� TabControl'� � �������
 tabctl = new TTabControl(this, IDC_TABCONTROL, 0, 0, 100, 100);
 alu = new TCuemuALU(this);
 cu = new TCuemuCU(this);
 conn = new TCuemuConnections(this);
 info = new TCuemuInfo(this);
 decoder = new TCuemuDecoder(this);
// ������������ ������� ������� ������
 Attr.AccelTable = "MAINMENU";
// Attr.Menu = "MAINMENU";       // ������ �� ����... �� �� ��������
}

// ���������� ��������� ������� ����
void TCuemuWindow::EvSize(uint, TSize &)
{
 TRect rc = GetClientRect();
 tabctl->SetWindowPos(NULL, rc, SWP_DRAWFRAME | SWP_NOZORDER);
}

// ���������� ������� ���� "��������� ����"
void TCuemuWindow::CmExecuteFile()
{
// �������� ��� �����
 TFileOpenDialog::TData
 data(OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
      "��� ����� (*.*)|*.*|", 0, "", "*");
 if (TFileOpenDialog(this, data).Execute() == IDOK) {
// ���� � ���� ������ ����� ������������ ����� OK...
  PassCuemuCommandString("load %s", data.FileName);
 }
}

// ���������� ������� ���� "��������� ����"
void TCuemuWindow::CmSaveFile()
{
 TFileSaveDialog::TData
 data(OFN_OVERWRITEPROMPT, "��� ����� (*.*)|*.*|", 0, "", "txt");
 if (TFileSaveDialog(this, data).Execute() == IDOK) {
  PassCuemuCommandString("save %s", data.FileName);
 }
}

// ���������� ������� ���� "�������������"
void TCuemuWindow::CmInitialize()
{
 int i = MessageBox("��������������� ��������?\n��� ������� �������� � ��������� ��������",
                    "�������������", MB_ICONQUESTION | MB_YESNO);
 if (i==IDYES) PassCuemuCommandString("init");
}

// ���������� ������� ���� "���������"
void TCuemuWindow::CmExecute()
{
 PassCuemuCommandString("exec");
}

// ���������� ������� ���� "�������� ��������������"
void TCuemuWindow::CmClear()
{
 int i = MessageBox("�������� �������������� ?", "��������",
                    MB_ICONQUESTION | MB_YESNO);
 if (i==IDYES) PassCuemuCommandString("cl");
}

// ���������� ������� ���� "������� ����������"
void TCuemuWindow::CmUnlinkAll()
{
 int i = MessageBox("������� ��� ���������� � ��������������� �������� ?", "��������",
                    MB_ICONQUESTION | MB_YESNO);
 if (i==IDYES) PassCuemuCommandString("clc\ninit");
}

// ����������� ������ ���� ������ ������ ����������
void TCuemuWindow::CmTrace()
{
 PassCuemuCommandString("sm t");
}

void TCuemuWindow::CmAuto()
{
 PassCuemuCommandString("sm a");
}

// ����������� ������ ������ ������ ���������
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

// ����������� ������ ������� "�������"
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

// ��������� ������� "������ �������"
void TCuemuWindow::CmHideConsole()
{
// ���������� �������� ���������� ���� �������. ��� ������� ����� � �����������,
// ��������, ���� ������ ��������� �������� ��������� ���� �������...
 THandle handle = ::FindWindow("ConsoleWindowClass", "������� CUEMU");
 if (!handle) {
  MessageBox("������� �� �������!", "Dazed and confused", MB_ICONEXCLAMATION | MB_OK);
  return;
 }
// ��������� ������� ����� ���������� �� ������� ����� � �������� ����
 if (menu.GetMenuState(IDM_HIDECONSOLE, MF_BYCOMMAND) & MF_CHECKED) {
  ::ShowWindow(handle, SW_SHOW);
  menu.CheckMenuItem(IDM_HIDECONSOLE, MF_UNCHECKED | MF_BYCOMMAND);
 } else {
  ::ShowWindow(handle, SW_HIDE);
  menu.CheckMenuItem(IDM_HIDECONSOLE, MF_CHECKED | MF_BYCOMMAND);
 }
}

// ���������� ��� �������� ����
void TCuemuWindow::SetupWindow() {
 TFrameWindow::SetupWindow();
// ������ ����� ��� ������������� �������� ������ hConsoleThread (cuemu-exec.cpp)
// �� ���������� (�� ������� exit)
 SetTimer(0, 200);
 SetMenu(menu);
// ����� �� ��������� - ������-�� System.
// ��������� ����� ��� �������� ������ �������� �����
 tabctl->SetWindowFont((HFONT)::GetStockObject(ANSI_VAR_FONT), true);
// ������� ��������
 index_alu_tab = tabctl->Add("���");
 index_cu_tab = tabctl->Add("��");
 index_connections_tab = tabctl->Add("����������");
 index_info_tab = tabctl->Add("����������");
 index_decoder_tab = tabctl->Add("�������");
// �������, � ������� �� ������� ����, � SetupWindow() �� ���������,
// ������� ����� ������� �� �������. Create() ������� ����������� ������
// � ���� ������ ������ ���� ���������� ������ ���� �� �������
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
// ������������ ������� NotifyChanges � cuemu, ����� ��� ���������� ���
// ���������� ������ �������
 cuemu_notify_func = NotifyChanges;
 cuemu_notify_data = this;
 main_window = this;
// ������������ ���������� ������� �������
 SetConsoleCtrlHandler(ConsoleEventHandler, true);
}

// ��� ������� ������ ���������� ��� ���������� ������ ������� cuemu
// ������ �������� - ��� ������� (�� ������������)
// data - ���������� ��� ����������� ������ (����� ��������� �� TCuemuWindow)
void TCuemuWindow::NotifyChanges(const char *, void *data)
{
 TCuemuWindow *This = (TCuemuWindow *)data;
// ������� �������� �������� ����
 This->alu->Update();
 This->conn->Update();
 This->cu->Update();
 This->decoder->Update();
// ������ ���� �� ��������� ���� ������ ������ ��������� ������ ���� �������
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
// ������� �������� ���� ������ ������ ����������
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

// ��� ������� ���������� ��� ����� ���������� ��������
// �.�. TabControl ����� �� ����� ��������� ���������� � ��� ����������,
// �� ����������� ������ �������� ���������� ����������� �������
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

// ������� ������������ ������� TCuemuWindow
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

// ���������� main() ��� �������� OWL
int OwlMain(int /*argc*/, char ** /*argv*/)
{
// ������� ���������� �������, �.�. ��������� ����� ��� Win32 GUI
// (���� Win32 Console, �� �� �������� OWL...)
 AllocConsole();
 SetConsoleTitle(chartooem("������� CUEMU"));
// ����� ����� ���� ����� �� ������ ����
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                         FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
                         | FOREGROUND_INTENSITY);
// ������ cin � cout ����� �� ������� � ����� ��������
// ����� � ��� �� ���� �������� �������. ���������� ������� ����� ������
// _open_osfhandle() - ������������� �������, ��������� ���������� �����
// UNIX (����� �����) ��� ����������� ����� Win32 (HANDLE)
 ifstream __cin(_open_osfhandle(long(GetStdHandle(STD_INPUT_HANDLE)), O_RDONLY));
 if (!__cin) return 1;
 ofstream __cout(_open_osfhandle(long(GetStdHandle(STD_OUTPUT_HANDLE)), 0));
 if (!__cout) return 2;
 set_stdout(__cout);
 __cout << "CUEMU-GUI" << endl;
 __cout << "Copyright (C) Vigura Anton (2006)" << endl;
// �������� ����� ��������� ������ �������
 InitConsoleThread(&__cin);
// � �������� OWL GUI
 return TCuemuApp().Run();
}