#ifndef CUEMU_GUI_INFO_H
#define CUEMU_GUI_INFO_H

#include <owl/dialog.h>
#include <owl/combobox.h>
#include <owl/static.h>

#include "cuemu-exec.h"

class TCuemuInfo: public TDialog {
public:
 TCuemuInfo(TWindow *parent);
protected:
 TComboBox *mop;
 TStatic *info;
 void CmSelChange();
 void SetupWindow();
 bool PreProcessMsg(MSG &msg) {
  if (GetParentO()->TWindow::PreProcessMsg(msg)) return true;
  return TDialog::PreProcessMsg(msg);
 }
 DECLARE_RESPONSE_TABLE(TCuemuInfo);
};

#endif