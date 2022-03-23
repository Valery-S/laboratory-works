const addrPrinter 5h
const addrKeyRowScan 3h
const addrKeyColScan 4h
const addrSpeacker 6h
const addrPrinterReady 7h
const stackPosition 0500h ; Значение вершины стека по-умолчанию
const lastSymbolPosition 80h ; Код последней позиции индикатора

jmp begin

skip 30h
jmp interruptReq

skip 100h

:begin

lxi sp, stackPosition
ei
jmp selectText1

:start
    ; ****************************
    ; Return to normal background*
    ; ****************************
    lda needRestart
    cpi 00h
    jnz checkText
    
    jmp selectText1
    
:checkText
    ; ***************************
    ; Check for other job       *
    ; ***************************
   
lda currentText
cpi 00h
jz selectText1
jmp selectText2
   
:selectText1
    lxi h, text
    shld currentText
    jmp output
    
:selectText2
    lxi h, textName
    shld currentText
    jmp output
    
:output
    mvi a, 00h
    sta needRestart

    mvi e, 01h ; Устанавливаем номер текущего выводимового символа
    ;lxi b, 8000h ; Загружаем регистровую пару BC значением 8000h
    ;stax b ; Загружаем "0" в регистр позиции ( "гасим" индикатор )
    out 00h
    
    lhld currentText
    ;lxi h, text ; Загружаем в регистровую пару HL адрес массива символов
                ; т.е адрес первого символа
    
    
; Вывод первого символа
:prepareFirstSymbol
    
    ;lxi sp, stackPosition ; Установка вершины стека
    push h ; Сохранияем адрес текущего символа в стеке
    
    mvi a, 01h ; Задаем позицию отображения 1-го символа
    ;sphl ; Переносим вершину стека в начало выводимой строки
    
:showSymbol
    ;pop h ; Загружаем в HL адрес отображаемого символа
    
    mov d, a
    push h
    
    mov a, m
    cpi 0FFh
    jnz nextSymbol
    inx h
    mov a, m
    cpi 0FFh
    jnz nextSymbol
    
    pop h
    pop h ; extct old h
    jmp start
    
:nextSymbol
    pop h

    mov a, d
    ; show next symbol

    mov d, a
    mov a, m
    ;sta 8001h
    out 01h
    inx h
    mov a, m
    ;sta 8002h
    out 02h
    inx h
    mov a, d
    
    ;shld 8001h ; Записываем в (8001h) значение из регистровой пары HL
               ; т.е вывод в регистры DD6 и DD7
    
    ;inx h
    ;inx h
    ;shld currentSymbol
    
    ;stax b ; Загружаем содержимое аккумулятора A по адресу (BC) 
           ; т.е отображение загруженного символа
    out 00h
    
    mov d, a ; сохраняем текущую позицию в регистре D
             ; т.к. аккумулятор потребуется для ожидания
    
    mvi a, 1h ; Загружаем в аккумулятор "время ожидания"
    
; Ждем пока аккумулятор не станет равным нулю
:waitLoop
    dcr a
    cpi 00h
    jnz waitLoop
    
    ; Очищаем регистр позиции
    mvi a, 0h 
    ;stax b
    out 00h
    
    ; Сдвиг символов
    
    mov a, d ; Восстанавливаем номер текущей позиции в аккумулятор
    
    cpi lastSymbolPosition ; Проверяем, является ли позиция последней в индикаторе 
    jz loadNextSymbol ; Если последняя переходим к следующему символу
    
    rlc ; Вычисляем новую позицию символа в индикаторе
    ;mov d, a ; Сохраняем новую позицию в регистре D
    
    jmp showSymbol ; Выполняем пока не заполним весь индикатор
    
:loadNextSymbol
    ;lxi sp, stackPosition ; Восстанавливаем изначальную позицию вершины стека
    ;dcx sp ; Уменьшаем значение вершины стека на 2 т.к в стеке уже есть 
    ;dcx sp ; сохраненное знаение регистровой пары HL
    
    pop h ; Получаем адрес текущего символа в 1-й позиции на индикаторе
    inx h ; Увеличиваем на 2 что бы получить адрес следующего отображаемого
    inx h ; символа
    
    lda needRestart
    cpi 01h
    jnz prepareFirstSymbol
    
    jmp start

 :interruptReq
    ;saving variables
    push b
    push d
    mov e, a
    push h
   
   lxi h, oldKeyboardState
   
    ; scan 1s line
    mvi a, 01h
    out addrKeyRowScan
    
    in addrKeyColScan
    cmp m
    jz check2Row
    
    mov m, a
    cpi 00h
    jz check2Row
    
    mvi a, 01h
    sta needRestart
    sta currentText
    
    jmp endOfInt
    
:check2Row
    inx h

    mvi a, 02h
    out addrKeyRowScan
    
    in addrKeyColScan
    cmp m
    jz check3Row
    
    mov m, a
    cpi 00h
    jz check3Row
    
    push h
    lxi h, printerText
    
    :printerLoop
        mov a, m
        cpi 00h
        jz endPrinterLoop
        push d
        mov d, a
        
        :printerWait
            in addrPrinterReady
            cpi 00h
            jz endPrinterWait
            jmp printerWait
            
        :endPrinterWait
            mov a, d
            pop d
        
        out addrPrinter
        inx h
        jmp printerLoop
        
    :endPrinterLoop
    pop h
    
    jmp endOfInt
    
:check3Row
    inx h

    mvi a, 04h
    out addrKeyRowScan
    
    in addrKeyColScan
    cmp m
    jz endOfInt
    mov m, a
    
    cpi 00h
    jz endOfInt

    mvi a, 00h
    out addrSpeacker
    mvi a, 01h
    out addrSpeacker
    
:endOfInt 
    pop h
    mov a, e
    pop d
    pop b
 
    ei
    ret
; ******************************************************************************
; * Секция данных                                                              *
; ****************************************************************************** 

currentText dw 00h
needRestart db 00h

oldKeyboardState db 00h, 00h, 00h, 00h

printerText db '15-3-2022', 00h

text dw 0h,0h, 0h,0939h, 0939h, 003fh, 025ch, 0h, 0h,0FFFFh
textName dw 0h, 0h,39h,6eh,600h,900h,3fh,73h,6eh,930h,3fh,939h,0h, 0h,0FFFFh
