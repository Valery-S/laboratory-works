#ifndef CUEMU_GUI_ALU_H
#define CUEMU_GUI_ALU_H

#include <owl/dialog.h>
#include <owl/groupbox.h>
#include <owl/button.h>
#include "cuemu.h"
#include "cuemu-controls.h"
#include "cuemu-exec.h"

// Класс страницы АЛУ главного окна
class TCuemuALU: public TDialog {
public:
 TCuemuALU(TWindow *parent);
~TCuemuALU() {delete [] triggers;}
 void Update();         // Вызывается при смене состояния эмулятора
protected:
// Элементы управления
 TRegister *rga, *rgb, *sum, *mem;              // Регистры
 TRegisterValue *vrga, *vrgb, *vsum, *vmem;     // Значения регистров
 TGroupBox *group1, *group2, *group3, *group4;  // Группы элементов
 TButton *execute, *clear;                      // Кнопки запуска и очистки
 TTrigger **triggers;                           // Триггеры микроопераций
 void CmChangeRGA();
 void CmChangeRGB();
 void CmChangeSUM();
 void CmChangeMEM();
 void CmClear();
 void CmExecute();
 void SetupWindow();
// Нужно отловить из всех событий нажатия горячих клавиш главного окна
// TWindow::PreProcessMsg() обрабатывает только нажатия горячих клавиш,
// возвращая true, в остальных случаях возвращает false
// Если эту функцию не переопределить, то эти нажатия будут обработаны
// в обработчике TDialog и фактически затеряются
 bool PreProcessMsg(MSG &msg) {
  if (GetParentO()->TWindow::PreProcessMsg(msg)) return true;
  return TDialog::PreProcessMsg(msg);
 }
 DECLARE_RESPONSE_TABLE(TCuemuALU);
};

#endif