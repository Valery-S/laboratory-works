#include "cuemu-gui-cu.h"

#define IDC_MEMORYGRID 100
#define IDC_ADDR 101
#define IDC_ADDRVALUE 102
#define IDC_COUNTER 103
#define IDC_COUNTERVALUE 104
#define IDC_EXECUTE 105
#define IDC_CLEARMICROCODE 106
#define IDC_INITIALIZE 107

TMemoryGrid::THeader TCuemuCU::header[] = {
 {"Адрес2", 5},
 {"Адрес1", 5},
 {"Усл", 3},
 {"Микрооперации", 37}
};

TCuemuCU::TCuemuCU(TWindow *parent)
: TDialog(parent, "EMPTYDIALOG")
{
 commands = new TMemoryGrid(this, IDC_MEMORYGRID, 0, 0, 650, 400, MAX_ADDR,
                            50, 4, header);
 gaddr = new TGroupBox(this, 1000, "РАМК", 0, 405, 200, 70);
 gcounter = new TGroupBox(this, 1001, "Счетчик", 230, 405, 200, 70);
 addr = new TRegister(this, IDC_ADDR, 10, 425, 100, 20, 5);
 counter = new TRegister(this, IDC_COUNTER, 240, 425, 80, 20, 4);
 vaddr = new TRegisterValue(this, IDC_ADDRVALUE, "Значение", 10, 450,
                            180, 20, addr);
 vcounter = new TRegisterValue(this, IDC_ADDRVALUE, "Значение", 240, 450,
                               180, 20, counter, 0xF);
 execute = new TButton(this, IDC_EXECUTE, "Выполнить", 450, 410, 120, 20);
 clear = new TButton(this, IDC_CLEARMICROCODE, "Очистить", 450, 435, 120, 20);
 initialize = new TButton(this, IDC_INITIALIZE, "Инициализировать", 450, 460, 120, 20);
}

void TCuemuCU::SetupWindow()
{
 TDialog::SetupWindow();
 HFONT hfont = (HFONT)::GetStockObject(ANSI_VAR_FONT);
 gaddr->SetWindowFont(hfont, true);
 gcounter->SetWindowFont(hfont, true);
 execute->SetWindowFont(hfont, true);
 clear->SetWindowFont(hfont, true);
 initialize->SetWindowFont(hfont, true);
 Update(); 
}

void TCuemuCU::Update()
{
 for (int i=1; i<=MAX_ADDR; i++) commands->SetValue(i, 0);
 if (list) {
  microcommand *l = list;
  do {
   int addr = l->addr;
   if (addr>=1 && addr<=MAX_ADDR) commands->SetValue(addr, l->cmd);
   l = l->next;
  } while (l!=list);
 }
 addr->SetValue(::addr);
 counter->SetValue(::counter);
 Invalidate();
}

TResult TCuemuCU::EvCommand(uint id, THandle hwnd, uint notify)
{
 if (id==IDC_MEMORYGRID) {
  qword val = commands->GetValue(notify);
  if (val) {
   char buf[256];
   microcommand mc;
   mc.addr = notify;
   mc.cmd = val;
   deparse_line(&mc, buf);
   PassCuemuCommandString("cmd %s", buf);
  } else PassCuemuCommandString("rm %u", notify);
  return 0;
 } else return TDialog::EvCommand(id, hwnd, notify);
}

void TCuemuCU::CmChangeAddr()
{
 PassCuemuCommandString("setma %u", (dword)addr->GetValue());
}

void TCuemuCU::CmChangeCounter()
{
 char buf[33];
 ultoa((dword)counter->GetValue(), buf, 2);
 PassCuemuCommandString("setc %s", buf);
}

void TCuemuCU::CmExecute()
{
 PassCuemuCommandString("exec");
}

void TCuemuCU::CmClear()
{
 int i = MessageBox("Очистить микропрограмму ?", "Удаление",
                    MB_ICONQUESTION | MB_YESNO);
 if (i==IDYES) PassCuemuCommandString("cl");
}

void TCuemuCU::CmInitialize()
{
 int i = MessageBox("Иницилизировать эмулятор?\nЭто сбросит регистры в начальные значения",
                    "Инициализация", MB_ICONQUESTION | MB_YESNO);
 if (i==IDYES) PassCuemuCommandString("init");                   
}

DEFINE_RESPONSE_TABLE1(TCuemuCU, TDialog)
 EV_COMMAND(IDC_ADDR, CmChangeAddr),
 EV_COMMAND(IDC_COUNTER, CmChangeCounter),
 EV_COMMAND(IDC_EXECUTE, CmExecute),
 EV_COMMAND(IDC_CLEARMICROCODE, CmClear),
 EV_COMMAND(IDC_INITIALIZE, CmInitialize),
END_RESPONSE_TABLE;