#include "cuemu-controls.h"
#include <owl/uihelper.h>
#include <cstdio>

// Цвета состояний триггера
TColor TTrigger::enabled_color(127, 255, 127);
TColor TTrigger::disabled_color(0, 127, 0);

// Обработчик перерисовки триггера
void TTrigger::EvPaint()
{
 TPaintDC dc(*this);              // Контекст устройства перерисовки
 TRect rc = GetWindowRect();
 rc.right -= rc.left; rc.bottom -= rc.top; rc.left = rc.top = 0;
 if (focus) dc.DrawFocusRect(rc); // Если фокус ввода есть, отобразим это
 dc.SetBkColor(TColor::Sys3dFace);// Системный цвет фона окна
 switch(style) {
  case LabelLeft:                 // Метка слева
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
  case LabelRight:                  // Метка справа
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
  case NoLabel:                     // Метки нет
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

// Эта функция очищает фон окна wnd на контексте устройства hdc
void EraseBackground(TWindow *wnd, HDC hdc)
{
 TDC dc(hdc);
 TRect rc = wnd->GetClientRect();   // Координаты очищаемой области
 TBrush br(TColor::Sys3dFace);
 dc.SelectObject(br);               // Очищать будем системным цветом фона
 dc.PatBlt(rc);                     // Собственно очистка
 dc.RestoreBrush();
}

// Обработка очистки фона триггера
bool TTrigger::EvEraseBkgnd(HDC hdc)
{
 EraseBackground(this, hdc);
 return true;
}

// Обработка нажатий клавиш
void TTrigger::EvKeyDown(uint key, uint, uint)
{
 if (key==VK_SPACE || key==VK_RETURN) {
  value = !value;       // При нажатии пробела или Enter'а меняем состояние
  SetFocus();           // триггера на противоположное
  NotifyParent();
  Invalidate();
 }
}

// Обработка нажатия левой кнопки мыши
void TTrigger::EvLButtonDown(uint, TPoint &)
{
 value = !value;
 SetFocus();
 NotifyParent();
 Invalidate();
}

// Обработка получения фокуса ввода - вызывает перерисовку окна
void TTrigger::EvSetFocus(HWND)
{
 focus = true;
 Invalidate();
}

// Обработка потери фокуса ввода - тоже перерисовка
void TTrigger::EvKillFocus(HWND)
{
 focus = false;
 Invalidate();
}

// Уведомление окна-предка о том, что состояние триггера изменилось
void TTrigger::NotifyParent()
{
 GetParentO()->SendMessage(WM_COMMAND, (WORD)GetId(), (LONG)(HWND)*this);
}

// Конструктор класса TRegister()
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
// Перерисовка окна не должна влиять на окна-потомки (т.е. триггеры)
 Attr.Style |= WS_CLIPCHILDREN;
}

// Вызывается OWL при действительном создании окна (получении дескриптора)
void TRegister::SetupWindow()
{
 TControl::SetupWindow();
 qword tmp = value;                       // Установим состояния триггеров
 for (int i=0; i<count; i++, tmp>>=1) {
  triggers[i]->SetState((tmp & 1)!=0);
 }
}

// Устанавливает значение регистра в qw
void TRegister::SetValue(qword qw)
{
 value = qw;
 qword tmp = value;
 for (int i=0; i<count; i++, tmp>>=1) {
  triggers[i]->SetState((tmp & 1)!=0);
 }
}

// Обработчик очистки фона окна
bool TRegister::EvEraseBkgnd(HDC hdc)
{
 EraseBackground(this, hdc);
 return true;
}

// Обработка сообщений WM_COMMAND
// Это сообщение может быть получено только от окна-потомка
// (т.к. триггера)
TResult TRegister::EvCommand(uint id, THandle h, uint notify)
{
 TTrigger *altered = triggers[id];     // Триггер, изменивший свое состояние
 if (altered->GetState()) {            // Нужно обновить value
  value |= qword(1)<<id;
 } else {
  value &= ~(qword(1)<<id);
 }
// Также нужно уведомить окно-предок о том, что значение регистра изменилось
 GetParentO()->SendMessage(WM_COMMAND, (WORD)GetId(), (LONG)(HWND)*this);
 return TWindow::EvCommand(id, h, notify);
}

bool TRegisterValue::EvEraseBkgnd(HDC hdc)
{
 EraseBackground(this, hdc);
 return true;
}

// Перерисовка окна TRegisterValue
void TRegisterValue::EvPaint()
{
 TPaintDC dc(*this);
// По умолчанию выбран шрифт System
// Лучше выбрать системный шрифт для диалоговых окон
 TFont font((HFONT)::GetStockObject(ANSI_VAR_FONT));
 TSize textsize;
 TRect rc = GetWindowRect();
 rc.right -= rc.left; rc.bottom -= rc.top; rc.left = rc.top = 0;
// Получение заголовка окна - он и будет выводимой надписью
 char buf[1024];
 GetWindowText(buf, 1023);
// Вывод надписи
 dc.SelectObject(font);
 dc.SetBkColor(TColor::Sys3dFace);
 textsize = dc.GetTextExtent(buf, strlen(buf));
 TRect textpos(0, 0, textsize.cx+1, rc.bottom);
// Вывод с выравниванием на правую сторону по горизонтали и по центру по вертикали
 dc.DrawText(buf, strlen(buf), textpos, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
 TRect ledpos(textpos.right+7, 0, rc.right, rc.bottom);
// Вывод рамки для области выводимого числа
 TUIBorder::DrawEdge(dc, ledpos, BDR_SUNKENINNER | BDR_RAISEDOUTER,
                     BF_RECT);
// Рамка имеет толщину в два пикселя
 ledpos.Inflate(-2, -2);
// Закраска области
 TBrush br(TColor::Black);
 dc.SelectObject(br);
 dc.PatBlt(ledpos);
 dc.SetTextColor(TColor(127, 255, 127));
 dc.SetBkColor(TColor::Black);
// Вывод числа
 sprintf(buf, "%Lu", (reg->GetValue()>>shr) & mask);
 dc.DrawText(buf, strlen(buf), ledpos, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
 dc.RestoreFont();
 dc.RestoreBrush();
}

// Конструктор TMemoryGrid
// Параметр _headers указывает на массив заголовков для матрицы памяти
// Этот массив должен существовать, пока существует окно TMemoryGrid
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
// Изначально все значения должны содержать нули
 ZeroMemory(values, sizeof(qword)*rows);
 Attr.Style |= WS_CLIPCHILDREN;
}

// Вызывается при создании окна
void TMemoryGrid::SetupWindow()
{
 TControl::SetupWindow();
 TWindowDC dc(*this);
 TFont font((HFONT)::GetStockObject(ANSI_VAR_FONT));
 dc.SelectObject(font);
// Получим размер текста в контексте устройства окна
 TSize size = dc.GetTextExtent("X", 1);
 TRect rc = GetClientRect();     // Клиентская область окна
 dc.RestoreFont();
// Ширина ячейки. 20 пикселов отводится для вывода адресов с левой стороны окна
 cellwidth = (rc.right-20) / cols;
 header = new TColumnHeader(this, 100, 0, 0, rc.right, size.cy+5);
// Т.к. TControl::SetupWindow() уже была вызвана, окно header
// придется создать явно
 header->Create();
// По умолчанию опять-таки шрифт System
 header->SetWindowFont(font, true);
// Добавляем элементы в header. Слева будет пустой элемент
// такой ширины, чтобы остальные точно соответстовали соответствующим колонкам
 THdrItem item("");
 item.SetWidth(rc.right - cols*cellwidth);
 header->Add(item);
 for (uint i=0; i<nheaders; i++) {
  THdrItem item(headerdata[i].caption);
  item.SetWidth(cellwidth*headerdata[i].columns);
  header->Add(item);
 }
// Это значение достаточно хорошо подходи для ординаты начала матрицы
// size.cy - высота шрифта
 tablestart = (size.cy+5)*2;
// Расчет высоты ячейки
 cellheight = (rc.bottom - tablestart)/rows;
 setup = true;
}

// Обработка очистки фона
bool TMemoryGrid::EvEraseBkgnd(HDC hdc)
{
 TDC dc(hdc);
 TRect rc = GetClientRect();
// PatBlt() позволяет быстро закрасить указанный прямоугольник белым цветом
 dc.PatBlt(rc, WHITENESS);
 return true;
}

// Перерисовка матрицы памяти
void TMemoryGrid::EvPaint()
{
 if (!setup) return;
 TPaintDC dc(*this);
 TRect rc = GetClientRect();
// Получаем размер шрифта
 TSize size = dc.GetTextExtent("X", 1);
// Выбираем "правильный" шрифт
 TFont font((HFONT)::GetStockObject(ANSI_VAR_FONT));
// Цвет линий будет серым
 TPen pen(TColor(180, 180, 180));
 TBrush brush(TColor::Black);
 dc.SelectObject(pen);
 dc.SelectObject(font);
 dc.SelectObject(brush);
// При выводе текста фон за ним удаляться не должен
 dc.SetBkMode(TRANSPARENT);
// Вывод линий, отделяющих соседние колонки
 for (uint i=1; i<=cols; i++) {
  int x = rc.right - i*cellwidth;
  dc.MoveTo(x, size.cy+5);
  dc.LineTo(x, rc.bottom);
 }
// Вывод номеров колонок через 5
 for (uint i=5; i<=cols; i+=5) {
  char buf[32];
  itoa(i, buf, 10);
  dc.TextOut(rc.right-i*cellwidth, size.cy+5, buf);
 }
// Вывод линий, отделяющих соседние строки
 for (uint i=0; i<rows; i++) {
  int y = tablestart + i*cellheight;
  dc.MoveTo(0, y);
  dc.LineTo(rc.right, y);
 }
// Вывод номеров строк - через 2
 for (uint i=1; i<=rows; i+=2) {
  int y = tablestart + (i-1)*cellheight;
  char buf[32];
  itoa(i, buf, 10);
  dc.TextOut(0, y, buf);
 }
// Те линии, что отделяют разные заголовки, перерисуем черным цветом
 TPen blackpen(TColor::Black);
 dc.SelectObject(blackpen);
 for (int i=nheaders-1, pos=0; i>=0; i--) {
  pos += headerdata[i].columns;
  int x = rc.right - pos*cellwidth;
  dc.MoveTo(x, size.cy+5);
  dc.LineTo(x, rc.bottom);
 }
// Вывод содержимого ячеек. Нулевые ячейки останутся белыми, единичные
// закрасим черным цветом
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

// При нажатии левой кнопки мыши (pt - координаты указателя мыши в момент нажатия)
// нужно определить, какую ячейку нужно изменить
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

// Перерисовка регистра
// Вообще-то, обработка WM_PAINT для TRegister не нужна (перерисовывать нечего),
// т.к. триггеры перерисовываются сами, когда это нужно
// Странная проблема возникает, когда главное окно создает MessageBox
// поверх окна с регистром. При этом триггеры регистра почему-то не
// перерисовываются... (а отдельные триггеры перерисовываются нормально),
// Здесь можно заставить все окна-потомки перерисоваться в любом случае
// Контекст устройства dc здесь нужен для того, чтобы уведомить Windows об
// успешном начале и завершении перерисовки (TPaintDC вызовет
// в конструкторе BeginPaint(), а в деструкторе - EndPaint()), без него
// наблюдаются еще более интересные эффекты...
void TRegister::EvPaint()
{
 TPaintDC dc(*this);
 for (int i=0; i<count; i++) if (triggers[i]) triggers[i]->Invalidate();
}

// Таблицы обработчиков
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
