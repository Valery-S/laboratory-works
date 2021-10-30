#ifndef CUEMU_GUI_DECODER_H
#define CUEMU_GUI_DECODER_H

#include <owl/dialog.h>
#include <owl/treewind.h>

#include "cuemu-exec.h"

class TCuemuDecoder: public TDialog {
public:
 TCuemuDecoder(TWindow *parent);
 void Update();
protected:
 bool PreProcessMsg(MSG &msg) {
  if (GetParentO()->TWindow::PreProcessMsg(msg)) return true;
  return TDialog::PreProcessMsg(msg);
 }
 TTreeWindow *tree;
};

#endif