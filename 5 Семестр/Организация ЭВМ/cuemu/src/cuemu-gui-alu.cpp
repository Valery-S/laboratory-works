#include "cuemu-gui-alu.h"

#define IDC_RGA 100              // �������������� ��������� ����������
#define IDC_RGB 101
#define IDC_SUM 102
#define IDC_MEM 103
#define IDC_RGAVALUE 104
#define IDC_RGBVALUE 105
#define IDC_SUMVALUE 106
#define IDC_MEMVALUE 107
#define IDC_EXECUTE 108
#define IDC_CLEAR 109
#define IDC_TRIGGER_BASE 3000

// ������� ��������������, �������� ������� ����� � ����� ������� �� ����
int column1[] = {
 OP_CL_RGA_SIGN,
 OP_RD_RGA_SIGN,
 OP_INV_RGA_SIGN,
 OP_GET_RGA_SIGN,
 OP_CL_RGA_DIG,
 OP_CL_SUM_SIGN,
 OP_RD_SUM_SIGN,
 OP_INV_SUM_SIGN,
 OP_GET_SUM_SIGN,
 OP_MK_SUM_INV,
 OP_GET_SUM,
 OP_CL_SUM_DIG,
 OP_CL_RGB_SIGN,
 OP_RD_RGB_SIGN,
 OP_INV_RGB_SIGN,
 OP_GET_RGB_SIGN,
 OP_GET_RGB_INV,
 -1
};

int column2[] = {
 OP_RD_RGA_DIG,
 OP_SET_RGA_MSB,
 OP_SHR_RGA,
 OP_GET_RGA_INV,
 OP_GET_RGA,
 OP_GET_SUM_INV,
 OP_CL_SUM_DIG,
 OP_RD_SUM_DIG,
 OP_SET_SUM_LSB,
 OP_SET_SUM_MSB,
 OP_INV_SUM_DIG,
 OP_CARRY_LEFT,
 OP_CARRY_RIGHT,
 OP_CL_RGB_DIG,
 OP_RD_RGB_DIG,
 OP_SET_RGB_LSB,
 OP_SHL_RGB,
 OP_GET_RGB,
 -1
};

// �����������
TCuemuALU::TCuemuALU(TWindow *parent)
: TDialog(parent, "EMPTYDIALOG")
{
 TWindow::Attr.Style = WS_CHILD | DS_CONTROL | WS_VISIBLE;
// ��� ������ ����� ��������� � ���� ��������������� ��������
 group1 = new TGroupBox(this, 1000, "RGA", 180, 30, 280, 80);
 group2 = new TGroupBox(this, 1001, "��������", 180, 110, 280, 80);
 group3 = new TGroupBox(this, 1002, "RGB", 180, 190, 280, 80);
 group4 = new TGroupBox(this, 1003, "������", 180, 270, 280, 80);
// �������� ����� ���������
 rga = new TRegister(this, IDC_RGA, 205, 45, 245, 20, 10);
 sum = new TRegister(this, IDC_SUM, 190, 125, 260, 20, 11);
 rgb = new TRegister(this, IDC_RGB, 205, 205, 245, 20, 10);
 mem = new TRegister(this, IDC_MEM, 205, 285, 245, 20, 10);
// � ��������� � ���� ���� ������ ��������
 vrga = new TRegisterValue(this, IDC_RGAVALUE, "�������� � �������� ��������",
                           190, 75, 260, 15, rga, DIGITS_MASK);
 vsum = new TRegisterValue(this, IDC_SUMVALUE, "�������� � �������� ��������",
                           190, 155, 260, 15, sum, DIGITS_MASK);
 vrgb = new TRegisterValue(this, IDC_RGBVALUE, "�������� � �������� ��������",
                           190, 235, 260, 15, rgb, DIGITS_MASK);
 vmem = new TRegisterValue(this, IDC_MEMVALUE, "�������� � �������� ��������",
                           190, 315, 260, 15, mem, DIGITS_MASK);
 int y = 2;
 char buf[256];
 triggers = new TTrigger*[40];
 ::ZeroMemory(triggers, sizeof(TTrigger*)*40);
// �������� ����� ������� ���������
 for (int i=0; column1[i]>=0; i++, y+=27) {
  cmdinfo *cmd = find_command((uint8)column1[i]);
  sprintf(buf, "%s (%d)", cmd->name, column1[i]);
  triggers[column1[i]] = new TTrigger(this, column1[i] + IDC_TRIGGER_BASE, buf,
                                      2, y, 150, 27, TTrigger::LabelLeft);
 }
 y = 2;
// �������� ������ �������
 for (int i=0; column2[i]>=0; i++, y+=27) {
  cmdinfo *cmd = find_command((uint8)column2[i]);
  sprintf(buf, "%s (%d)", cmd->name, column2[i]);
  triggers[column2[i]] = new TTrigger(this, column2[i] + IDC_TRIGGER_BASE, buf,
                                      482, y, 170, 27, TTrigger::LabelRight);
 }
 cmdinfo *cmd = find_command(OP_GET_MEM);
 sprintf(buf, "%s (%d)", cmd->name, OP_GET_MEM);
// ������� ������� ���������� ������ �� ������ ����� ������ ���������
 triggers[OP_GET_MEM] = new TTrigger(this, OP_GET_MEM+IDC_TRIGGER_BASE,
                                     buf, 180, 360, 280, 20, TTrigger::LabelRight);
 execute = new TButton(this, IDC_EXECUTE, "���������", 180, 400, 120, 25);
 clear = new TButton(this, IDC_CLEAR, "�������� �������", 330, 400, 120, 25);
}

// ����������� ��������� ���������
void TCuemuALU::CmChangeRGA()
{
 char buf[256];
 vrga->Invalidate();
 _ui64toa(rga->GetValue(), buf, 2);
 PassCuemuCommandString("seta %s 0", buf);
}

void TCuemuALU::CmChangeRGB()
{
 char buf[256];
 vrgb->Invalidate();
 _ui64toa(rgb->GetValue(), buf, 2);
 PassCuemuCommandString("setb %s 0", buf);
}

void TCuemuALU::CmChangeSUM()
{
 char buf[256];
 vsum->Invalidate();
 _ui64toa(sum->GetValue(), buf, 2);
 PassCuemuCommandString("sets %s 0", buf);
}

void TCuemuALU::CmChangeMEM()
{
 char buf[256];
 vmem->Invalidate();
 _ui64toa(mem->GetValue(), buf, 2);
 PassCuemuCommandString("setm %s 0", buf);
}

void TCuemuALU::CmClear()
{
 for (int i=1; i<40; i++) {
  if (triggers[i]) triggers[i]->SetState(false);
 }
}

// ���������� ������� ������ "���������"
// �������� � ������� �� ������ 0 ��� ���������� �������������,
// ��������� ��, � ����� ������� ��� �������
// ������ 0 �� ����� ���� �� � ����� �� ���������� ������������� ��
void TCuemuALU::CmExecute()
{
 char buf[256]; *buf = '\0';
 char buf2[64];
 for (int i=1; i<40; i++) {
  if (triggers[i]) {
   if (triggers[i]->GetState()) {
    itoa(i, buf2, 10);
    strcat(buf, buf2); strcat(buf, " ");
   }
  }
 }
 PassCuemuCommandString("cmd 0 %s\nam n\nsm t\nsetma 0\nexec\nrm 0\nshow\n", buf);
}

// ���������� ����
void TCuemuALU::Update()
{
 rga->SetValue(::rga);
 rgb->SetValue(::rgb);
 sum->SetValue(::sum);
 mem->SetValue(::mem);
 vrga->Invalidate(); vrgb->Invalidate(); vsum->Invalidate(); vmem->Invalidate();
}

// ����� �������� ���� ����� ������� *����������* ����� ��������� ����������
void TCuemuALU::SetupWindow()
{
 HFONT sysfont = (HFONT)::GetStockObject(ANSI_VAR_FONT);
 TDialog::SetupWindow();
 group1->SetWindowFont(sysfont, true);
 group2->SetWindowFont(sysfont, true);
 group3->SetWindowFont(sysfont, true);
 group4->SetWindowFont(sysfont, true);
 execute->SetWindowFont(sysfont, true);
 clear->SetWindowFont(sysfont, true);
}

DEFINE_RESPONSE_TABLE1(TCuemuALU, TDialog)
 EV_COMMAND(IDC_RGA, CmChangeRGA),
 EV_COMMAND(IDC_RGB, CmChangeRGB),
 EV_COMMAND(IDC_SUM, CmChangeSUM),
 EV_COMMAND(IDC_MEM, CmChangeMEM),
 EV_COMMAND(IDC_CLEAR, CmClear),
 EV_COMMAND(IDC_EXECUTE, CmExecute),
END_RESPONSE_TABLE;