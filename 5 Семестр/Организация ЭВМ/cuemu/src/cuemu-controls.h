// Раширенные элементы управления для cuemu
#ifndef CUEMU_CONTROLS_H
#define CUEMU_CONTROLS_H
#include <owl/pch.h>
#include <owl/colmnhdr.h>
#include "executer.h"

#define TRIGGER_WIDTH 12

// "Триггер" - элемент с двумя состояниями
// Аналог checkbox'а, но выглядит как квадратный светодиод с надписью
class TTrigger: public TControl {
public:
 enum TStyle {
  LabelLeft, LabelRight, NoLabel    // Положение надписи
 };
// Конструктор
 TTrigger(TWindow *parent, int id, const char *label, int x, int y, int w, int h,
          TStyle _style)
 : TControl(parent, id, label, x, y, w, h),
   value(false),
   style(_style),
   focus(false)
 {;}
// Функции контроля состояния
 bool GetState() const {return value;}
 void SetState(bool st) {value = st; Invalidate();}
protected:
 DECLARE_RESPONSE_TABLE(TTrigger);
 TStyle style;                      // Стиль элемента
 bool value;                        // Состоняние
 bool focus;                        // true, если окно имеет фокус ввода

 static TColor enabled_color;       // Цвет состояния 1
 static TColor disabled_color;      // Цвет состояния 0

 bool EvEraseBkgnd(HDC hdc);        // Обработчики событий
 void EvPaint();
 void EvSetFocus(HWND);
 void EvKillFocus(HWND);
 void EvKeyDown(uint key, uint, uint);
 void EvLButtonDown(uint, TPoint &);
 void NotifyParent();
};

// "Регистр"
// Это по сути линейка "триггеров" (TTrigger)
// Максимальное число триггеров - 64
class TRegister: public TControl {
public:
 TRegister(TWindow *parent, int id, int x, int y, int w, int h,
           int bits, qword val=0);

// Деструктор. Освобождаем только массив указателей на триггеры. Сами
// триггеры (они тоже выделены с помощью new) будут автоматически
// освобождены в деструкторе TWindow
~TRegister() {delete [] triggers;}

 qword GetValue() {return value;}      // Функции работы со значением регистра
 void SetValue(qword v);

protected:
 DECLARE_RESPONSE_TABLE(TRegister);
 qword value;                          // Текущее значение регистра
 int count;                            // Число отображаемых разрядов (LSB)
 bool focus;                           // true, если окно имеет фокус ввода
 TTrigger **triggers;                  // Массив указателей на триггеры

 bool EvEraseBkgnd(HDC hdc);           // Обработчики событий
 void EvPaint();
 void EvSetFocus(HWND);
 void EvKillFocus(HWND);
 void SetupWindow();
 TResult EvCommand(uint id, THandle, uint);
};

// Этот элемент управления связывается с регистром и отображает
// его значение в десятичном виде
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
 TRegister *reg;                 // Связанный регистр
 qword mask;                     // Маска отображаемых разрядов регистра
 int shr;                        // Перед отображением число сдвигатся
 void EvPaint();                 // вправо на shr разрядов
 bool EvEraseBkgnd(HDC hdc);
};

// Это уже элемент редактирования "матрицы памяти"
// размером rows x cols (cols<=64, т.к. матрица хранится как массив
// учетверенных слов)
class TMemoryGrid: public TControl {
public:

 struct THeader {        // Структура информации о заголовке нескольких колонок
  const char *caption;   // Строка заголовка
  int columns;           // Число колонок под заголовком
 };

 TMemoryGrid(TWindow *parent, int id, int x, int y, int w, int h, uint _rows,
             uint _cols, uint _nheaders, THeader *_headers);
~TMemoryGrid() {delete [] values;}

// Индекс row здесь должен начинаться с 1
 void SetValue(uint row, qword qw) {values[row-1] = qw;}
 qword GetValue(uint row) {return values[row-1];}
 uint GetRows() const {return rows;}
 uint GetCols() const {return cols;}
protected:
 qword *values;                  // Массив строк матрицы
 uint rows, cols, nheaders;      // Число столбцов, строк и заголовков
 THeader *headerdata;            // Массив заголовков
 TColumnHeader *header;          // Элемент управления - заголовок
 int textheight;                 // Высота текста в контексте устройства окна
 int tablestart;                 // Ордината начала отображения матрицы в окне
 int cellwidth, cellheight;      // Ширина и высота одной "ячейки" в окне
 bool setup;                     // Если true, то окно полностью создано
 void EvPaint();
 bool EvEraseBkgnd(HDC hdc);
 void EvLButtonDown(uint, TPoint &pt);
 void SetupWindow();
 DECLARE_RESPONSE_TABLE(TMemoryGrid);
};

#endif
