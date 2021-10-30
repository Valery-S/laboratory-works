#ifndef CUEMU_GUI_CU_H
#define CUEMU_GUI_CU_H

#include <owl/dialog.h>
#include <owl/static.h>
#include <owl/button.h>
#include <owl/groupbox.h>
#include "cuemu-controls.h"
#include "cuemu-exec.h"
#include "cuemu.h"

// Класс страницы УУ главного окна
class TCuemuCU: public TDialog {
public:
 TCuemuCU(TWindow *parent);
 void Update();
protected:
 TMemoryGrid *commands;                   // Матрица памяти команд
 TRegister *addr, *counter;               // Регистры РАМК и счетчика
 TRegisterValue *vaddr, *vcounter;        // Их значения
 TGroupBox *gaddr, *gcounter;             // И рамки
 TButton *execute, *clear, *initialize;   // Три кнопки справа
 static TMemoryGrid::THeader header[];    // Массив заголовков
 void SetupWindow();
 void CmChangeAddr();
 void CmChangeCounter();
 void CmExecute();
 void CmInitialize();
 void CmClear();
 bool PreProcessMsg(MSG &msg) {
  if (GetParentO()->TWindow::PreProcessMsg(msg)) return true;
  return TDialog::PreProcessMsg(msg);
 }
 TResult EvCommand(uint id, THandle hwnd, uint notify);
 DECLARE_RESPONSE_TABLE(TCuemuCU);
};

#endif