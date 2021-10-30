#include "cuemu-gui-info.h"
#include "cuemu-rc.rh"
#include "cuemu.h"

TCuemuInfo::TCuemuInfo(TWindow *parent)
: TDialog(parent, "INFO")
{
 mop = new TComboBox(this, IDC_SELECTMOP);
 info = new TStatic(this, IDC_MOPINFO);
}

void TCuemuInfo::SetupWindow()
{
 TDialog::SetupWindow();
 for (int i=1; i<38; i++) {
  char buf[256];
  cmdinfo *inf = find_command((uint8)i);
  sprintf(buf, "%d: %s", i, inf->name);
  mop->AddString(buf);
 }
}

void TCuemuInfo::CmSelChange()
{
 int i = mop->GetSelIndex();
 if (i<0) return;
 cmdinfo *inf = find_command((uint8)(i+1));
 if (!inf) return;
 if (inf->noncompat) {
  ostrstream oss;
  for (int n=0; inf->noncompat[n]; n++) {
   cmdinfo *current = find_command(inf->noncompat[n]);
   if (!current) continue;
   oss << (int)inf->noncompat[n] << ": " << current->name << endl;
  }
  oss.put('\0');
  char *buf = oss.str();
  info->SetCaption(buf);
  delete [] buf;
 } else info->SetCaption("");
}

DEFINE_RESPONSE_TABLE1(TCuemuInfo, TDialog)
 EV_CBN_SELCHANGE(IDC_SELECTMOP, CmSelChange),
END_RESPONSE_TABLE;