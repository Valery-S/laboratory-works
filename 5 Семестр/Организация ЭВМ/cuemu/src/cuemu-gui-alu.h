#ifndef CUEMU_GUI_ALU_H
#define CUEMU_GUI_ALU_H

#include <owl/dialog.h>
#include <owl/groupbox.h>
#include <owl/button.h>
#include "cuemu.h"
#include "cuemu-controls.h"
#include "cuemu-exec.h"

// ����� �������� ��� �������� ����
class TCuemuALU: public TDialog {
public:
 TCuemuALU(TWindow *parent);
~TCuemuALU() {delete [] triggers;}
 void Update();         // ���������� ��� ����� ��������� ���������
protected:
// �������� ����������
 TRegister *rga, *rgb, *sum, *mem;              // ��������
 TRegisterValue *vrga, *vrgb, *vsum, *vmem;     // �������� ���������
 TGroupBox *group1, *group2, *group3, *group4;  // ������ ���������
 TButton *execute, *clear;                      // ������ ������� � �������
 TTrigger **triggers;                           // �������� �������������
 void CmChangeRGA();
 void CmChangeRGB();
 void CmChangeSUM();
 void CmChangeMEM();
 void CmClear();
 void CmExecute();
 void SetupWindow();
// ����� �������� �� ���� ������� ������� ������� ������ �������� ����
// TWindow::PreProcessMsg() ������������ ������ ������� ������� ������,
// ��������� true, � ��������� ������� ���������� false
// ���� ��� ������� �� ��������������, �� ��� ������� ����� ����������
// � ����������� TDialog � ���������� ����������
 bool PreProcessMsg(MSG &msg) {
  if (GetParentO()->TWindow::PreProcessMsg(msg)) return true;
  return TDialog::PreProcessMsg(msg);
 }
 DECLARE_RESPONSE_TABLE(TCuemuALU);
};

#endif