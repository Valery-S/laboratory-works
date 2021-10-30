#ifndef CUEMU_GUI_CONN_H
#define CUEMU_GUI_CONN_H

#include <owl/dialog.h>
#include <owl/combobox.h>
#include <owl/button.h>

#include "cuemu-exec.h"

class TCuemuConnections: public TDialog {
public:
 TCuemuConnections(TWindow *parent);
 void Update(); 
protected:
 TComboBox *connector1, *connector2;
 TListBox *list;
 void CmLink();
 void CmUnlink();
 void CmUnlinkAll();
 void SetupWindow();
 bool PreProcessMsg(MSG &msg) {
  if (GetParentO()->TWindow::PreProcessMsg(msg)) return true;
  return TDialog::PreProcessMsg(msg);
 }
 DECLARE_RESPONSE_TABLE(TCuemuConnections);
};

#endif