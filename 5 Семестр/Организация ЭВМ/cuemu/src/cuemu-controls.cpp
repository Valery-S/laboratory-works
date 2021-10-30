#include "cuemu-controls.h"
#include <owl/uihelper.h>
#include <cstdio>

// ����� ��������� ��������
TColor TTrigger::enabled_color(127, 255, 127);
TColor TTrigger::disabled_color(0, 127, 0);

// ���������� ����������� ��������
void TTrigger::EvPaint()
{
 TPaintDC dc(*this);              // �������� ���������� �����������
 TRect rc = GetWindowRect();
 rc.right -= rc.left; rc.bottom -= rc.top; rc.left = rc.top = 0;
 if (focus) dc.DrawFocusRect(rc); // ���� ����� ����� ����, ��������� ���
 dc.SetBkColor(TColor::Sys3dFace);// ��������� ���� ���� ����
 switch(style) {
  case LabelLeft:                 // ����� �����
  {
   TRect textpos = rc;
   TFont font((HFONT)::GetStockObject(ANSI_VAR_FONT));
   TBrush brush(value ? enabled_color : disabled_color);
   char buf[1024];
   textpos.right -= TRIGGER_WIDTH+4;
   textpos.top = 1; textpos.bottom -= 1;
   GetWindowText(buf, 1023);
   dc.SelectObject(font);
   dc.SelectObject(brush);
   dc.DrawText(buf, strlen(buf), textpos, DT_RIGHT | DT_WORDBREAK);
   dc.RestoreFont();
   TRect trigger(rc.right - TRIGGER_WIDTH - 2, 2, rc.right - 2, 2 + TRIGGER_WIDTH);
   TUIBorder::DrawEdge(dc, trigger, BDR_SUNKENINNER | BDR_RAISEDOUTER,
                       BF_RECT);
   trigger = trigger.Inflate(-2, -2);
   dc.PatBlt(trigger);
   dc.RestoreBrush();
  }
  break;
  case LabelRight:                  // ����� ������
  {
   TRect textpos = rc;
   TFont font((HFONT)::GetStockObject(ANSI_VAR_FONT));
   TBrush brush(value ? enabled_color : disabled_color);
   char buf[1024];
   textpos.right -= TRIGGER_WIDTH+4;
   textpos.left = TRIGGER_WIDTH+4;
   textpos.top = 1; textpos.bottom -= 1;
   GetWindowText(buf, 1023);
   dc.SelectObject(font);
   dc.SelectObject(brush);
   dc.DrawText(buf, strlen(buf), textpos, DT_LEFT | DT_WORDBREAK);
   dc.RestoreFont();
   TRect trigger(2, 2, TRIGGER_WIDTH + 2, 2 + TRIGGER_WIDTH);
   TUIBorder::DrawEdge(dc, trigger, BDR_SUNKENINNER | BDR_RAISEDOUTER,
                       BF_RECT);
   trigger = trigger.Inflate(-2, -2);
   dc.PatBlt(trigger);
   dc.RestoreBrush();
  }
  break;
  case NoLabel:                     // ����� ���
  {
   rc.Inflate(-2, -2);
   TUIBorder::DrawEdge(dc, rc, BDR_SUNKENINNER | BDR_RAISEDOUTER,
                       BF_RECT);
   rc.Inflate(-2, -2);
   TBrush brush(value ? enabled_color : disabled_color);
   dc.SelectObject(brush);
   dc.PatBlt(rc);
   dc.RestoreBrush();
  }
  break;
 }
}

// ��� ������� ������� ��� ���� wnd �� ��������� ���������� hdc
void EraseBackground(TWindow *wnd, HDC hdc)
{
 TDC dc(hdc);
 TRect rc = wnd->GetClientRect();   // ���������� ��������� �������
 TBrush br(TColor::Sys3dFace);
 dc.SelectObject(br);               // ������� ����� ��������� ������ ����
 dc.PatBlt(rc);                     // ���������� �������
 dc.RestoreBrush();
}

// ��������� ������� ���� ��������
bool TTrigger::EvEraseBkgnd(HDC hdc)
{
 EraseBackground(this, hdc);
 return true;
}

// ��������� ������� ������
void TTrigger::EvKeyDown(uint key, uint, uint)
{
 if (key==VK_SPACE || key==VK_RETURN) {
  value = !value;       // ��� ������� ������� ��� Enter'� ������ ���������
  SetFocus();           // �������� �� ���������������
  NotifyParent();
  Invalidate();
 }
}

// ��������� ������� ����� ������ ����
void TTrigger::EvLButtonDown(uint, TPoint &)
{
 value = !value;
 SetFocus();
 NotifyParent();
 Invalidate();
}

// ��������� ��������� ������ ����� - �������� ����������� ����
void TTrigger::EvSetFocus(HWND)
{
 focus = true;
 Invalidate();
}

// ��������� ������ ������ ����� - ���� �����������
void TTrigger::EvKillFocus(HWND)
{
 focus = false;
 Invalidate();
}

// ����������� ����-������ � ���, ��� ��������� �������� ����������
void TTrigger::NotifyParent()
{
 GetParentO()->SendMessage(WM_COMMAND, (WORD)GetId(), (LONG)(HWND)*this);
}

// ����������� ������ TRegister()
TRegister::TRegister(TWindow *parent, int id,
                     int x, int y, int w, int h, int bits, qword val)
: TControl(parent, id, "", x, y, w, h),
  count(bits),
  focus(false),
  value(val)
{
 int triggerwidth = w/bits;
 TRect rc(0, 0, w, h);
 triggers = new TTrigger*[bits];
 for (int off=w-triggerwidth, i=0; off>=0 && i<bits; i++, off-=triggerwidth) {
  triggers[i] = new TTrigger(this, i, "", off, 0, triggerwidth, h,
                             TTrigger::NoLabel);
 }
// ����������� ���� �� ������ ������ �� ����-������� (�.�. ��������)
 Attr.Style |= WS_CLIPCHILDREN;
}

// ���������� OWL ��� �������������� �������� ���� (��������� �����������)
void TRegister::SetupWindow()
{
 TControl::SetupWindow();
 qword tmp = value;                       // ��������� ��������� ���������
 for (int i=0; i<count; i++, tmp>>=1) {
  triggers[i]->SetState((tmp & 1)!=0);
 }
}

// ������������� �������� �������� � qw
void TRegister::SetValue(qword qw)
{
 value = qw;
 qword tmp = value;
 for (int i=0; i<count; i++, tmp>>=1) {
  triggers[i]->SetState((tmp & 1)!=0);
 }
}

// ���������� ������� ���� ����
bool TRegister::EvEraseBkgnd(HDC hdc)
{
 EraseBackground(this, hdc);
 return true;
}

// ��������� ��������� WM_COMMAND
// ��� ��������� ����� ���� �������� ������ �� ����-�������
// (�.�. ��������)
TResult TRegister::EvCommand(uint id, THandle h, uint notify)
{
 TTrigger *altered = triggers[id];     // �������, ���������� ���� ���������
 if (altered->GetState()) {            // ����� �������� value
  value |= qword(1)<<id;
 } else {
  value &= ~(qword(1)<<id);
 }
// ����� ����� ��������� ����-������ � ���, ��� �������� �������� ����������
 GetParentO()->SendMessage(WM_COMMAND, (WORD)GetId(), (LONG)(HWND)*this);
 return TWindow::EvCommand(id, h, notify);
}

bool TRegisterValue::EvEraseBkgnd(HDC hdc)
{
 EraseBackground(this, hdc);
 return true;
}

// ����������� ���� TRegisterValue
void TRegisterValue::EvPaint()
{
 TPaintDC dc(*this);
// �� ��������� ������ ����� System
// ����� ������� ��������� ����� ��� ���������� ����
 TFont font((HFONT)::GetStockObject(ANSI_VAR_FONT));
 TSize textsize;
 TRect rc = GetWindowRect();
 rc.right -= rc.left; rc.bottom -= rc.top; rc.left = rc.top = 0;
// ��������� ��������� ���� - �� � ����� ��������� ��������
 char buf[1024];
 GetWindowText(buf, 1023);
// ����� �������
 dc.SelectObject(font);
 dc.SetBkColor(TColor::Sys3dFace);
 textsize = dc.GetTextExtent(buf, strlen(buf));
 TRect textpos(0, 0, textsize.cx+1, rc.bottom);
// ����� � ������������� �� ������ ������� �� ����������� � �� ������ �� ���������
 dc.DrawText(buf, strlen(buf), textpos, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
 TRect ledpos(textpos.right+7, 0, rc.right, rc.bottom);
// ����� ����� ��� ������� ���������� �����
 TUIBorder::DrawEdge(dc, ledpos, BDR_SUNKENINNER | BDR_RAISEDOUTER,
                     BF_RECT);
// ����� ����� ������� � ��� �������
 ledpos.Inflate(-2, -2);
// �������� �������
 TBrush br(TColor::Black);
 dc.SelectObject(br);
 dc.PatBlt(ledpos);
 dc.SetTextColor(TColor(127, 255, 127));
 dc.SetBkColor(TColor::Black);
// ����� �����
 sprintf(buf, "%Lu", (reg->GetValue()>>shr) & mask);
 dc.DrawText(buf, strlen(buf), ledpos, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
 dc.RestoreFont();
 dc.RestoreBrush();
}

// ����������� TMemoryGrid
// �������� _headers ��������� �� ������ ���������� ��� ������� ������
// ���� ������ ������ ������������, ���� ���������� ���� TMemoryGrid
TMemoryGrid::TMemoryGrid(TWindow *parent, int id, int x, int y, int w, int h,
                         uint _rows, uint _cols, uint _nheaders,
                         THeader *_headers)
: TControl(parent, id, "", x, y, w, h),
  rows(_rows),
  cols(_cols),
  nheaders(_nheaders),
  headerdata(_headers),
  setup(false)
{
 values = new qword[rows];
// ���������� ��� �������� ������ ��������� ����
 ZeroMemory(values, sizeof(qword)*rows);
 Attr.Style |= WS_CLIPCHILDREN;
}

// ���������� ��� �������� ����
void TMemoryGrid::SetupWindow()
{
 TControl::SetupWindow();
 TWindowDC dc(*this);
 TFont font((HFONT)::GetStockObject(ANSI_VAR_FONT));
 dc.SelectObject(font);
// ������� ������ ������ � ��������� ���������� ����
 TSize size = dc.GetTextExtent("X", 1);
 TRect rc = GetClientRect();     // ���������� ������� ����
 dc.RestoreFont();
// ������ ������. 20 �������� ��������� ��� ������ ������� � ����� ������� ����
 cellwidth = (rc.right-20) / cols;
 header = new TColumnHeader(this, 100, 0, 0, rc.right, size.cy+5);
// �.�. TControl::SetupWindow() ��� ���� �������, ���� header
// �������� ������� ����
 header->Create();
// �� ��������� �����-���� ����� System
 header->SetWindowFont(font, true);
// ��������� �������� � header. ����� ����� ������ �������
// ����� ������, ����� ��������� ����� �������������� ��������������� ��������
 THdrItem item("");
 item.SetWidth(rc.right - cols*cellwidth);
 header->Add(item);
 for (uint i=0; i<nheaders; i++) {
  THdrItem item(headerdata[i].caption);
  item.SetWidth(cellwidth*headerdata[i].columns);
  header->Add(item);
 }
// ��� �������� ���������� ������ ������� ��� �������� ������ �������
// size.cy - ������ ������
 tablestart = (size.cy+5)*2;
// ������ ������ ������
 cellheight = (rc.bottom - tablestart)/rows;
 setup = true;
}

// ��������� ������� ����
bool TMemoryGrid::EvEraseBkgnd(HDC hdc)
{
 TDC dc(hdc);
 TRect rc = GetClientRect();
// PatBlt() ��������� ������ ��������� ��������� ������������� ����� ������
 dc.PatBlt(rc, WHITENESS);
 return true;
}

// ����������� ������� ������
void TMemoryGrid::EvPaint()
{
 if (!setup) return;
 TPaintDC dc(*this);
 TRect rc = GetClientRect();
// �������� ������ ������
 TSize size = dc.GetTextExtent("X", 1);
// �������� "����������" �����
 TFont font((HFONT)::GetStockObject(ANSI_VAR_FONT));
// ���� ����� ����� �����
 TPen pen(TColor(180, 180, 180));
 TBrush brush(TColor::Black);
 dc.SelectObject(pen);
 dc.SelectObject(font);
 dc.SelectObject(brush);
// ��� ������ ������ ��� �� ��� ��������� �� ������
 dc.SetBkMode(TRANSPARENT);
// ����� �����, ���������� �������� �������
 for (uint i=1; i<=cols; i++) {
  int x = rc.right - i*cellwidth;
  dc.MoveTo(x, size.cy+5);
  dc.LineTo(x, rc.bottom);
 }
// ����� ������� ������� ����� 5
 for (uint i=5; i<=cols; i+=5) {
  char buf[32];
  itoa(i, buf, 10);
  dc.TextOut(rc.right-i*cellwidth, size.cy+5, buf);
 }
// ����� �����, ���������� �������� ������
 for (uint i=0; i<rows; i++) {
  int y = tablestart + i*cellheight;
  dc.MoveTo(0, y);
  dc.LineTo(rc.right, y);
 }
// ����� ������� ����� - ����� 2
 for (uint i=1; i<=rows; i+=2) {
  int y = tablestart + (i-1)*cellheight;
  char buf[32];
  itoa(i, buf, 10);
  dc.TextOut(0, y, buf);
 }
// �� �����, ��� �������� ������ ���������, ���������� ������ ������
 TPen blackpen(TColor::Black);
 dc.SelectObject(blackpen);
 for (int i=nheaders-1, pos=0; i>=0; i--) {
  pos += headerdata[i].columns;
  int x = rc.right - pos*cellwidth;
  dc.MoveTo(x, size.cy+5);
  dc.LineTo(x, rc.bottom);
 }
// ����� ����������� �����. ������� ������ ��������� ������, ���������
// �������� ������ ������
 for (uint i=1; i<=rows; i++) {
  qword tmp = GetValue(i);
  for (uint n=1; n<=cols; n++, tmp>>=1) {
   if (tmp & 1) {
    TRect r;
    r.left   = rc.right - n*cellwidth + 1;
    r.top    = tablestart+(i-1)*cellheight+1;
    r.right  = r.left + cellwidth - 1;
    r.bottom = r.top + cellheight - 1;
    dc.PatBlt(r);
   }
  }
 }
}

// ��� ������� ����� ������ ���� (pt - ���������� ��������� ���� � ������ �������)
// ����� ����������, ����� ������ ����� ��������
void TMemoryGrid::EvLButtonDown(uint, TPoint &pt)
{
 TRect rc = GetClientRect();
 int tablestartx = (rc.right-cols*cellwidth);
 if (pt.x<=tablestartx || pt.y<=(int)tablestart) return;
 uint col = (rc.right - pt.x)/cellwidth;
 uint row = (pt.y - tablestart)/cellheight;
 if (col>=cols || row>=rows) return;
 values[row] ^= qword(1)<<col;
 Invalidate();
 GetParentO()->SendMessage(WM_COMMAND, (WORD)GetId() | (DWORD(row+1)<<16), (LONG)(HWND)*this);
}

// ����������� ��������
// ������-��, ��������� WM_PAINT ��� TRegister �� ����� (�������������� ������),
// �.�. �������� ���������������� ����, ����� ��� �����
// �������� �������� ���������, ����� ������� ���� ������� MessageBox
// ������ ���� � ���������. ��� ���� �������� �������� ������-�� ��
// ����������������... (� ��������� �������� ���������������� ���������),
// ����� ����� ��������� ��� ����-������� �������������� � ����� ������
// �������� ���������� dc ����� ����� ��� ����, ����� ��������� Windows ��
// �������� ������ � ���������� ����������� (TPaintDC �������
// � ������������ BeginPaint(), � � ����������� - EndPaint()), ��� ����
// ����������� ��� ����� ���������� �������...
void TRegister::EvPaint()
{
 TPaintDC dc(*this);
 for (int i=0; i<count; i++) if (triggers[i]) triggers[i]->Invalidate();
}

// ������� ������������
DEFINE_RESPONSE_TABLE1(TTrigger, TControl)
 EV_WM_PAINT,
 EV_WM_ERASEBKGND,
 EV_WM_KEYDOWN,
 EV_WM_LBUTTONDOWN,
 EV_WM_SETFOCUS,
 EV_WM_KILLFOCUS,
END_RESPONSE_TABLE;

DEFINE_RESPONSE_TABLE1(TRegister, TControl)
 EV_WM_ERASEBKGND,
 EV_WM_PAINT,
END_RESPONSE_TABLE;

DEFINE_RESPONSE_TABLE1(TRegisterValue, TControl)
 EV_WM_ERASEBKGND,
 EV_WM_PAINT,
END_RESPONSE_TABLE;

DEFINE_RESPONSE_TABLE1(TMemoryGrid, TControl)
 EV_WM_ERASEBKGND,
 EV_WM_PAINT,
 EV_WM_LBUTTONDOWN,
END_RESPONSE_TABLE;
