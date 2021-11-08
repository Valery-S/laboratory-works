; Лабораторная работа №2
; Сухоруков Валерий
; Перестановка a(n),a(n-1),a(n-2),...,a(n/2),a(1),a(2),...,a(n/2-1).
; Многосегментная программа. Создаётся exe файл

.model small
.stack 200h

d1 segment para public 'data'
mess1 db 'Input: ',10,13,'$'
in_str db 22 dup (?)
d1 ends

e1 segment para public 'data'
mess2 db 10,13, 'Output: ',10,13,'$'
out_str db 20 dup ('$')
e1 ends


c1 segment para public 'code'
assume cs:c1, ds:d1, es:e1

start:
    ;Инициализация сегментов
    mov ax, d1
    mov ds, ax
    mov ax, e1
    mov es, ax

    ;Вывод строки запроса 
    mov dx, offset mess1
    mov ah, 9
    int 21h

    ;Считывание исходного массива
    mov dx, offset in_str
    mov in_str, 20
    mov ah, 10
    int 21h

    ;Инициализация регистра источника данных на конец исходного массива
    mov cl, in_str + 1         ;Количество элементов в массиве
    xor ch, ch                 ;Очистка регистра ch
    mov ax, offset in_str+1    ;Адрес, предшествующий первому элементу  
    add ax,cx                  ;Запись адреса последнего элемента
    mov si,ax                  ;Инициализация регистра источника данных 
    
    ;Инициализация регистра приёмника данных на начало выходного массива
    mov di, offset out_str

    ;Определения числа повторений первого цикла - Переставка второй 
    ;части исходного массива в начало нового в обратном порядке.
    ;Число повторений - количество элементов делить на 2.
    shr cx,1                    ;Деление выполняется сдвигом на 1 в право
    
m1:
    mov al, [si]
    mov es:[di],al
    dec si
    inc di
    loop m1

    ;Инициализация регистра источника данных на начало исходного массива
    mov si, offset in_str+2

    ;Определения числа повторений второго цикла - Переставка первой 
    ;части исходного массива в конец нового.
    ;Число повторений - количество элементов делить на 2.
    mov cl, in_str + 1              
    shr cx,1


m2:
    mov al,[si]
    mov es:[di],al
    inc si
    inc di
    loop m2

    ;Вывод строки, предшествующей выходному массиву
    mov ax, es
    mov ds, ax
    mov dx, offset mess2
    mov ah, 9
    int 21h

    ;Вывод нового массива
    mov dx, offset out_str
    mov ah, 9
    int 21h

    mov ah, 7
    int 21h

    mov ax, 4c00h
    int 21h

c1 ends

end start