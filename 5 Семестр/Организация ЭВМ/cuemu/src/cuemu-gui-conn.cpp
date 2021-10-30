#include "cuemu-gui-conn.h"
#include "cuemu-rc.rh"
#include "cuemu-exec.h"

TCuemuConnections::TCuemuConnections(TWindow *parent)
: TDialog(parent, "CONNECTIONS")
{
 connector1 = new TComboBox(this, IDC_CONNECTOR1);
 connector2 = new TComboBox(this, IDC_CONNECTOR2);
 list = new TListBox(this, IDC_CONNECTIONS);
}

void TCuemuConnections::SetupWindow()
{
 TDialog::SetupWindow();
 for (int i=0; i<C_NUMBER; i++) {
  char buf[256];     
  sprintf(buf, "%s, %s", connectors[i].name, connectors[i].descr);
  connector1->AddString(buf);
  connector2->AddString(buf);
 }
}

void TCuemuConnections::Update()
{
 list->ClearList();
 cable *l = connections;
 if (!l) return;
 do {
  char buf[1024];
  sprintf(buf, "%s, %s <--> %s, %s", l->first->name, l->first->descr,
          l->second->name, l->second->descr);
  int index = list->AddString(buf);
  list->SetItemData(index, (uint32)l);
  l = l->next;
 } while(l!=connections);
}

void TCuemuConnections::CmLink()
{
 int i1 = connector1->GetSelIndex(), i2;
 if (i1<0) goto warn;
 i2 = connector2->GetSelIndex();
 if (i2<0) goto warn;
 PassCuemuCommandString("link %s %s", connectors[i1].name, connectors[i2].name);
 return;
warn:
 MessageBox("Выберите сначала гнезда для соединения!", "Ничего не выбрано",
            MB_ICONEXCLAMATION | MB_OK);
}

void TCuemuConnections::CmUnlink()
{
 int i = list->GetSelIndex();
 if (i<0) {
  MessageBox("Выберите соединение для удаления!", "Ничего не выбрано",
             MB_ICONEXCLAMATION | MB_OK);
  return;           
 }
 cable *cb = (cable *)list->GetItemData(i);
 PassCuemuCommandString("unlink %s %s", cb->first->name, cb->second->name);
}

void TCuemuConnections::CmUnlinkAll()
{
 int i = MessageBox("Удалить все соединения и иницилизировать эмулятор ?", "Удаление",
                    MB_ICONQUESTION | MB_YESNO);
 if (i==IDYES) PassCuemuCommandString("clc\ninit");
}

DEFINE_RESPONSE_TABLE1(TCuemuConnections, TDialog)
 EV_COMMAND(IDC_LINK, CmLink),
 EV_COMMAND(IDC_UNLINK, CmUnlink),
 EV_COMMAND(IDC_UNLINKALL, CmUnlinkAll),
END_RESPONSE_TABLE;
