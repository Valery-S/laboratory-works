// ���������� �������� ���������� ��� cuemu
#ifndef CUEMU_CONTROLS_H
#define CUEMU_CONTROLS_H
#include <owl/pch.h>
#include <owl/colmnhdr.h>
#include "executer.h"

#define TRIGGER_WIDTH 12

// "�������" - ������� � ����� �����������
// ������ checkbox'�, �� �������� ��� ���������� ��������� � ��������
class TTrigger: public TControl {
public:
 enum TStyle {
  LabelLeft, LabelRight, NoLabel    // ��������� �������
 };
// �����������
 TTrigger(TWindow *parent, int id, const char *label, int x, int y, int w, int h,
          TStyle _style)
 : TControl(parent, id, label, x, y, w, h),
   value(false),
   style(_style),
   focus(false)
 {;}
// ������� �������� ���������
 bool GetState() const {return value;}
 void SetState(bool st) {value = st; Invalidate();}
protected:
 DECLARE_RESPONSE_TABLE(TTrigger);
 TStyle style;                      // ����� ��������
 bool value;                        // ����������
 bool focus;                        // true, ���� ���� ����� ����� �����

 static TColor enabled_color;       // ���� ��������� 1
 static TColor disabled_color;      // ���� ��������� 0

 bool EvEraseBkgnd(HDC hdc);        // ����������� �������
 void EvPaint();
 void EvSetFocus(HWND);
 void EvKillFocus(HWND);
 void EvKeyDown(uint key, uint, uint);
 void EvLButtonDown(uint, TPoint &);
 void NotifyParent();
};

// "�������"
// ��� �� ���� ������� "���������" (TTrigger)
// ������������ ����� ��������� - 64
class TRegister: public TControl {
public:
 TRegister(TWindow *parent, int id, int x, int y, int w, int h,
           int bits, qword val=0);

// ����������. ����������� ������ ������ ���������� �� ��������. ����
// �������� (��� ���� �������� � ������� new) ����� �������������
// ����������� � ����������� TWindow
~TRegister() {delete [] triggers;}

 qword GetValue() {return value;}      // ������� ������ �� ��������� ��������
 void SetValue(qword v);

protected:
 DECLARE_RESPONSE_TABLE(TRegister);
 qword value;                          // ������� �������� ��������
 int count;                            // ����� ������������ �������� (LSB)
 bool focus;                           // true, ���� ���� ����� ����� �����
 TTrigger **triggers;                  // ������ ���������� �� ��������

 bool EvEraseBkgnd(HDC hdc);           // ����������� �������
 void EvPaint();
 void EvSetFocus(HWND);
 void EvKillFocus(HWND);
 void SetupWindow();
 TResult EvCommand(uint id, THandle, uint);
};

// ���� ������� ���������� ����������� � ��������� � ����������
// ��� �������� � ���������� ����
class TRegisterValue: public TControl {
public:
 TRegisterValue(TWindow *parent, int id, const char *label,
                int x, int y, int w, int h, TRegister *_reg,
                qword _mask=(qword)-1, int _shr=0)
 : TControl(parent, id, label, x, y, w, h),
   reg(_reg), mask(_mask), shr(_shr)
 {;}
protected:
 DECLARE_RESPONSE_TABLE(TRegisterValue);
 TRegister *reg;                 // ��������� �������
 qword mask;                     // ����� ������������ �������� ��������
 int shr;                        // ����� ������������ ����� ���������
 void EvPaint();                 // ������ �� shr ��������
 bool EvEraseBkgnd(HDC hdc);
};

// ��� ��� ������� �������������� "������� ������"
// �������� rows x cols (cols<=64, �.�. ������� �������� ��� ������
// ������������ ����)
class TMemoryGrid: public TControl {
public:

 struct THeader {        // ��������� ���������� � ��������� ���������� �������
  const char *caption;   // ������ ���������
  int columns;           // ����� ������� ��� ����������
 };

 TMemoryGrid(TWindow *parent, int id, int x, int y, int w, int h, uint _rows,
             uint _cols, uint _nheaders, THeader *_headers);
~TMemoryGrid() {delete [] values;}

// ������ row ����� ������ ���������� � 1
 void SetValue(uint row, qword qw) {values[row-1] = qw;}
 qword GetValue(uint row) {return values[row-1];}
 uint GetRows() const {return rows;}
 uint GetCols() const {return cols;}
protected:
 qword *values;                  // ������ ����� �������
 uint rows, cols, nheaders;      // ����� ��������, ����� � ����������
 THeader *headerdata;            // ������ ����������
 TColumnHeader *header;          // ������� ���������� - ���������
 int textheight;                 // ������ ������ � ��������� ���������� ����
 int tablestart;                 // �������� ������ ����������� ������� � ����
 int cellwidth, cellheight;      // ������ � ������ ����� "������" � ����
 bool setup;                     // ���� true, �� ���� ��������� �������
 void EvPaint();
 bool EvEraseBkgnd(HDC hdc);
 void EvLButtonDown(uint, TPoint &pt);
 void SetupWindow();
 DECLARE_RESPONSE_TABLE(TMemoryGrid);
};

#endif
