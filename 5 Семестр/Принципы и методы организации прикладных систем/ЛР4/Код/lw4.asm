d1 SEGMENT para public USE16 'data'
	InSnowmanColor   equ 00001110b	;черный фон  - желтые буквы
	SnowmanColor     equ 00001011b	;черный фон  - голубые буквы
	BroomColor       equ 0000110b	;черный фон  - коричневые буквы
	BucketColor      equ 00000010b	;черный фон  - синие буквы
	waitBgColor      equ 00010010b  ;серый  фон  - синие буквы 
	mainBgColor      equ 00010010b  ;синий  фон  - зеленые буквы
	errorBgColor     equ 01000000b	;красный фон - черные буквы
	errorBgColorWait equ 11000000b	;красный фон - черные моргающие буквы
	resultBGColor    equ 01110001b	;серый фон   - синие буквы
	videoSeg         equ 0b800h
	
	;Снеговик
	Snowman1 db 16 dup (' '),'*******','$'
	Snowman2 db 16 dup (' '),'*     *','$'
	Snowman3 db 14 dup (' '),'*         *','$'
	Snowman4 db 13 dup (' '),'*           * ','$'
	Snowman5 db 13 dup (' '),'*           *','$'
	Snowman6 db 13 dup (' '),'*           *','$'
	Snowman7 db 13 dup (' '),'*   ****    * ','$'
	Snowman8 db 14 dup (' '),'*         *        *','$'
	Snowman9 db 8 dup (' '),'*       *******         *','$'
	Snowman10 db 9 dup (' '),'*   *           *     * ','$'
	Snowman11 db 10 dup (' '),'* *             *  *   ','$'
	Snowman12 db 11 dup (' '),'**             * *    ','$'
	Snowman13 db 12 dup (' '),'*             *      ','$'
	Snowman14 db 13 dup (' '),'*           *','$'
	Snowman15 db 15 dup (' '),'*********','$'
	Snowman16 db 13 dup (' '),'*           *','$'
	Snowman17 db 12 dup (' '),'*             *','$'
	
	Eyes db'*     *','$'
	Point db '*','$'
	Mouth db 4 dup ('*')
	
	Broom1 db'*   *   *','$'
	Broom2 db'*  *  *','$'
	Broom3 db'* * *','$'
	Broom4 db'***','$'
	

	mainWindowXStart db 6d
	mainWindowYStart db 7d
	mainWindowXEnd   db 55d
	mainWindowYEnd   db	13d
	
	WaitToStartText     db 'Press Enter to start, F4 to exit.$'
	WaitToMoveWiindow   db 'Use the arrows to move window, press Enter to Start, F4 to exit.$'
	WaitAnyKeyToExit    db 'Press any key to exit.$'
	WaitToReloadOrExit1 db 'Press F5 to show credits, F4 to exit.$'
	WaitToExit          db 'F4 to exit.$'
	Result				db 'Results$'	
	
	
	
	coursorX db 0
	coursorY db 0
	
	
	in_str label byte ;строка символов (не более 6)
	razmer db 7
	kol db (?)
	stroka db 7 dup (?)   ;знак числа (для отрицательных), 5 цифр, enter
	number dw 5 dup (0)   ;массив чисел
	siz dw 5              ;количество чисел
	maxnum dw 0           ;наибольшее
	minnum dw 0           ;наименьшее
	negNum dw 5 dup (0)   ;Отрицательные элементы
	posNum dw 5 dup (0)   ;Положительные элементы
	negSum dw 0           ;Сумма отрицательных
	posSum dw 0           ;Сумма положительных
	posAvg dw 0		      ;Среднее полжительных чисел
	posKol dw 0 		  ;Количество положительных
	perevod db 10,13,'$'
	text_err1 db 'Input error!$'
	messovf db 'Overflow!$'
	mesposavg db'Positive Average:$'
	messmax db 'Max:$'
	messmin db 'Min:$'
	mesposkol db 'Count of positive:$'
	mesnegSum db 'Sum of negative:$'
	mesposSum db 'Sum of positive:$'
	enter_please db 'Input number from -29999 to 29999: $'
	out_str db 6 dup (' '),'$'
	flag_err equ 1
	
d1 ENDS

st1 SEGMENT para stack USE16 'stack'
	dw 100 dup (?)
st1 ENDS


;Макрос рисования окна
; xStart - левый верхний угол - столбец
; yStart - левый верхний угол - строка
; xEnd   - правый нижний угол - столбец
; yEnd   - правый нижний угол - строка
drawWindow macro xStart, yStart, xEnd, yEnd, color	
	mov ah, 06
	mov al, 00
	
	mov ch, yStart				;левый верхний угол - строка
	mov cl, xStart				;левый верхний угол - столбец
	
	mov dh, yEnd				;правый нижний угол - строка
	mov dl, xEnd				;правый нижний угол - столбец
	
	mov bh, color				;установка цвета фона и цвета букв
	
	int 10h						;прерывание отрисовки
endm

;Макрос вывода в окне
; string - текст для вывода
; row    - строка вывода
; column - колонка вывода 
printInWindow macro string, row, column
	push ax
	push dx
	
	mov ah,2
	mov dh,row
	mov dl,column
	mov bh,0
	int 10h
	
	mov ah, 09h
	mov dx, offset string
	int 21h
	
	pop dx
	pop ax
endm

; Макрос ввода строки символов
; string - строка для ввода
input macro srting 	
	push ax 
	push dx
	mov dx, offset srting
	mov ah, 0Ah
	int 21h
	pop dx
	pop ax
endm

;Макрос вывода сообщений на экран
; string - строка для вывода
print macro srting		
	push ax
	push dx
	mov dx, offset srting
	mov ah, 09h
	int 21h
	pop dx
	pop ax
endm

; Макорс рисования снеговика
drawSnowman macro 
	printInWindow Snowman1, 6, 0		
	printInWindow Snowman2, 7, 0		
	printInWindow Snowman2, 8, 0		
	printInWindow Snowman2, 9, 0		
	printInWindow Snowman1, 10, 0
	printInWindow Snowman3, 11, 0
	printInWindow Snowman4, 12, 0		
	printInWindow Snowman5, 13, 0
	printInWindow Snowman6, 14, 0
	printInWindow Snowman7, 15, 0
	printInWindow Snowman8, 16, 0
	printInWindow Snowman9, 17, 0
	printInWindow Snowman10, 18, 0
	printInWindow Snowman11, 19, 0
	printInWindow Snowman12, 20, 0
	printInWindow Snowman13, 21, 0
	printInWindow Snowman13, 22, 0
	printInWindow Snowman14, 23, 0
	printInWindow Snowman15, 24, 0
	printInWindow Snowman16, 25, 0
	printInWindow Snowman17, 26, 0
	printInWindow Snowman17, 27, 0
	printInWindow Snowman17, 28, 0
	printInWindow Snowman17, 29, 0
	printInWindow Snowman17, 30, 0
	printInWindow Snowman17, 31, 0
	printInWindow Snowman16, 32, 0
	printInWindow Snowman15, 33, 0
endm

.386
c1 SEGMENT para public USE16 'code'
	ASSUME cs:c1, ds:d1, ss:st1

;Процедура сдвига окна влево
leftShift PROC
	cmp mainWindowXStart, 0
	je retleftShift
	dec mainWindowXStart
	dec mainWindowXEnd
retleftShift:
	ret
ENDP



;Процедура сдвига окна вправо
rightShift PROC
	cmp mainWindowXEnd, 79
	je retrightShift
	inc mainWindowXStart
	inc mainWindowXEnd
retrightShift:
	ret
ENDP



;Процедура сдвига окна вверх
upShift PROC
	cmp mainWindowYStart, 0
	je relupShift
	dec mainWindowYStart
	dec mainWindowYEnd
relupShift:
	ret
ENDP



;Процедура сдвига окна вниз
downShift PROC
	cmp mainWindowYEnd, 23
	je downshitRet
	inc mainWindowYStart
	inc mainWindowYEnd
downshitRet:
	ret
ENDP

;Старт программы
start:	
	mov ax, videoSeg
	mov es, ax
	mov ax, d1
	mov ds, ax

;********************************************* Снеговик *********************************************************
	drawWindow 0, 10, 80, 35, SnowmanColor	
	drawWindow 0, 0, 80, 9, BucketColor	
	drawSnowman
	
	drawWindow 15, 12, 23, 15, InSnowmanColor
	printInWindow Eyes, 12, 16
	printInWindow Point, 13, 19
	printInWindow Mouth, 15, 17

	drawWindow 28, 12, 40, 16, BroomColor
	drawWindow 33, 17, 34, 22, BroomColor
	printInWindow Broom1, 12, 29
	printInWindow Broom2, 13, 30
	printInWindow Broom3, 14, 31
	printInWindow Broom4, 15, 32
	printInWindow Point, 16, 33
	printInWindow Point, 17, 33
	printInWindow Point, 18, 33
	printInWindow Point, 19, 33
	printInWindow Point, 20, 33
	printInWindow Point, 21, 33
	printInWindow Point, 22, 33
	
	
;******************************* Переход от вступления к двиганию окна ******************************************
;Ожидание нажатие F4/Enter
waitToStart:
	drawWindow 0, 36, 80, 36, waitBgColor
	printInWindow WaitToStartText, 36, 0
	mov ah, 000								;ожидание ввода клавиши
	int 16h
	cmp ax, 3E00h							;сравнение с ASCII-кодом клавиши F4
	je programEnd
	cmp ax, 1C0Dh							;сравнение с ASCII и скан кодом клавиши Enter
	je moveWindow
	loop waitToStart
;**************************************** Двигаем окно  ***********************************************************
moveWindow:
	mov ax, 03h		;очистка экрана
	int 10h			
	drawWindow mainWindowXStart, mainWindowYStart, mainWindowXEnd, mainWindowYEnd, mainBgColor
	drawWindow 0, 24, 80, 24, waitBgColor
	printInWindow WaitToMoveWiindow, 24, 0
	

	mov ah, 00								;ожидание ввода клавиши
	int 16h
	cmp ax, 3E00h							;сравнение с ASCII-кодом клавиши F4
	je programEnd
	
	cmp ax, 1C0Dh							;сравнение с ASCII и скан кодом клавиши Enter							
	je startInput
	
	cmp ax, 4B00h							;сравнение с ASCII и скан кодом клавиши 'Стрелочка влево'
	je moveLeft
	
	cmp ax, 4D00h							;сравнение с ASCII и скан кодом клавиши 'Стрелочка вправо'
	je moveRight
	
	cmp ax, 4800h							;сравнение с ASCII и скан кодом клавиши 'Стрелочка вниз'
	je moveUp
	
	cmp ax, 5000h							;сравнение с ASCII и скан кодом клавиши 'Стрелочка вверх'
	je moveDown
	
	loop moveWindow
	
moveLeft:
	call leftShift
	jmp moveWindow
	
moveRight:
	call rightShift
	jmp moveWindow
	
moveUp:
	call upShift
	jmp moveWindow
	
moveDown:
	call downShift
	jmp moveWindow
	
;************************************* Вводим значения ************************************************	
startInput:
	mov ax, 03h		;очистка экрана
	int 10h	
	drawWindow mainWindowXStart, mainWindowYStart, mainWindowXEnd, mainWindowYEnd, mainBgColor
	
	mov al, mainWindowXStart
	mov coursorX, al
	
	mov al, mainWindowYStart
	mov coursorY, al
	
	inc coursorX
	
	xor di,di		;di - номер числа в массиве
    mov cx, siz		;cx - размер массива
	
inputValues:
	push cx

	inc coursorY
	
	;Вывод сообщения о вводе строки
	printInWindow enter_please, coursorY, coursorX	
	input in_str 		;Ввод числа в виде строки
	
	call diapazon		;Проверка диапазона вводимых чисел (-29999,+29999)
	cmp bh, flag_err  	;Сравним bh и flag_err
	je inErr         	;Если равен 1 сообщение об ошибке ввода

	call dopust			;Проверка допустимости вводимых символов
	cmp bh, flag_err  	;Сравним bh и flag_err
	je inErr         	;Если равен 1 сообщение об ошибке ввода
	
	call AscToBin 	    ;Преобразование строки в число
	inc di
	inc di
	pop cx
	loop inputValues
	jmp arifmet
	
inErr:  
	drawWindow 27, 9, 53, 16, errorBgColor
	drawWindow 27, 15, 53, 16, errorBgColorWait
	printInWindow text_err1, 12, 34
	printInWindow WaitAnyKeyToExit, 15, 30
	mov ah, 000								;ожидание ввода клавиши
	int 16h
	jmp programEnd
	
;***************************************** Арифметическая обработка *****************************************	
arifmet:
		mov cx, siz 	; В (cx) - размер массива
		xor si,si
;Поиск максимального и минимального элементов
		mov ax,number
		mov maxnum,ax
		mov minnum,ax
		
max:
		mov ax,number+si
		cmp ax,maxnum
		jle min
		mov maxnum,ax
		jmp min
		
min:	cmp ax,minnum
		jge next
		mov minnum,ax
		jmp next

next: 	inc si
		inc si
		loop max
		
; Поиск отрицательных элементов и рассчет их суммы
		mov cx, siz 	; В (cx) - размер массива
		mov si, offset number
		mov di, offset negNum
negFind:	
		mov ax, [si]
		cmp ax, 0
		jge endNegFind
		mov [di], ax
		add negSum, ax ; Сумма отрицательных
		jo  overFlowErr; Если произошло переполнение
		
		inc di
		inc di
	
endNegFind:
		inc si
		inc si
		loop negFind
		
		mov cx, siz
		mov si, offset number
		mov di, offset posNum
		xor bx, bx
; Поиск положительных элементов	и рассчет их среднего
posFind:
		mov ax, [si]
		cmp ax, 0
		jl endPosFind
		mov [di], ax
		add posSum, ax ; Сумма положительных
		jo  overFlowErr; Если произошло переполнение
		
		inc di
		inc di
		inc bx	; Считаем количество положительных элементов
		
	
endPosFind:
		inc si
		inc si
		loop posFind
	
; Поиск среднего положительного
		mov dx,0
		mov ax,posSum
		cmp bx,0
		je endAvg
		div bx
		mov posAvg, ax
endAvg:
		jmp resOutput

;*********************************************************** Вывод ошибок ************************************************************
overFlowErr:		
	drawWindow 27, 9, 53, 16, errorBgColor
	drawWindow 27, 15, 53, 16, errorBgColorWait
	printInWindow messovf, 12, 36
	printInWindow WaitAnyKeyToExit, 15, 30
	mov ah, 00
	int 16h
	jmp programEnd

;*************************************************** Вывод полученных результатов ****************************************************	
resOutput:
	drawWindow 20, 9, 65, 17, resultBGColor
	printInWindow Result, 10, 39
	printInWindow mesposSum, 13, 25
	mov ax, posSum
	call BinToAsc
	printInWindow out_str, 13, 55

	mov cx,6			;очистка буфера вывода
	xor si,si
clear1:		
	mov [out_str+si],' '
	inc si
	loop clear1

	printInWindow mesposavg, 14, 25
	mov ax,posAvg	
	call BinToAsc
	printInWindow out_str, 14, 55

	mov cx,6			;очистка буфера вывода
	xor si,si
clear2:		
	mov [out_str+si],' '
	inc si
	loop clear2

	printInWindow messmax, 15, 25
	mov ax,maxnum	
	call BinToAsc
	printInWindow out_str, 15, 55
	
	mov cx,6			;очистка буфера вывода
	xor si,si
		
clear3:		
	mov [out_str+si],' '
	inc si
	loop clear3

	printInWindow messmin, 16, 25
	mov ax,minnum	
	call BinToAsc
	printInWindow out_str, 16, 55
		
	mov cx,6			;очистка буфера вывода
	xor si,si
	
clear4:		
	mov [out_str+si],' '
	inc si
	loop clear4

	printInWindow mesnegSum, 17, 25
	mov ax,negSum	
	call BinToAsc
	printInWindow out_str, 17, 55
		

	
	
programEnd:	

	mov ax, 4c00h	;завершение работы
	int 21h 


;****************************************************
;* Проверка диапазона вводимых чисел -29999,+29999	*
;* Аргументы:										*
;* 		Буфер ввода - stroka						*
;* 													*
;* Результат:										*
;* 		bh - флаг ошибки ввода						*
;****************************************************
DIAPAZON PROC
    xor bh, bh
	xor si, si
	
	cmp kol, 05h 	; Если ввели менее 5 символов, проверим их допустимость
	jb dop
		
	cmp stroka, 2dh 	; Eсли ввели 5 или более символов проверим является ли первый минусом
	jne plus 	; Eсли 1 символ не минус, проверим число символов
	
	cmp kol, 06h 	; Eсли первый - минус и символов меньше 6 проверим допустимость символов 
	jb dop        
	
	inc si		; Иначе проверим первую цифру
	jmp first

plus:   
	cmp kol,6	; Bведено 6 символов и первый - не минус 
	je error1	; Oшибка
	
first:  
	cmp stroka[si], 32h	; Cравним первый символ с '2'
	jna dop		; Eсли первый <= '2' - проверим допустимость символов
	
error1:
	mov bh, flag_err	; Иначе bh = flag_err
	
dop:	
	ret
DIAPAZON ENDP



;****************************************************
;* Проверка допустимости вводимых символов			*
;* Аргументы:										*
;* 		Буфер ввода - stroka						*
;*		si - номер символа в строке					*
;* 													*
;* Результат:										*
;* 		bh - флаг ошибки ввода						*
;****************************************************
DOPUST PROC

	xor bh, bh
    xor si, si
	xor ah, ah
	xor ch, ch
	
	mov cl, kol	; В (cl) количество введенных символов
	
m11:	
	mov al, [stroka + si] 	; B (al) - первый символ
	cmp al, 2dh	; Является ли символ минусом
	jne testdop	; Если не минус - проверка допустимости
	cmp si, 00h	; Если минус  - является ли он первым символом
	jne error2	; Если минус не первый - ошибка
	jmp m13
	
testdop:
	cmp al, 30h	;Является ли введенный символ цифрой
	jb error2
	cmp al, 39h
	ja error2
	
m13: 	
	inc si
	loop m11
	jmp m14
	
error2:	
	mov bh, flag_err	; При недопустимости символа bh = flag_err
	
m14:	
	ret
DOPUST ENDP



;****************************************************
;* ASCII to number									*
;* Аргументы:										*
;* 		B cx количество введенных символов			*
;*		B bx - номер символа начиная с последнего 	*
;* 													*
;* Результат:										*
;* 		Буфер чисел - number						*
;*		B di - номер числа в массиве				*
;****************************************************
AscToBin PROC
	xor ch, ch
	mov cl, kol
	xor bh, bh
	mov bl, cl
	dec bl
	mov si, 01h  ; В si вес разряда
	
n1:	
	mov al, [stroka + bx]
	xor ah, ah
	cmp al, 2dh	; Проверим знак числа
	je otr	; Eсли число отрицательное
	sub al,	30h
	mul si
	add [number + di], ax
	mov ax, si
	mov si, 10
	mul si
	mov si, ax
	dec bx
	loop n1
	jmp n2
otr:	
	neg [number + di]	; Представим отрицательное число в дополнительном коде
	
n2:	
	ret
AscToBin ENDP



;****************************************************
;* Number to ASCII									*
;* Аргументы:										*
;* 		Число передается через ax					*
;* 													*
;* Результат:										*
;* 		Буфер чисел - out_str						*
;****************************************************
BinToAsc PROC
	xor si, si
	add si, 05h
	mov bx, 0Ah
	push ax
	cmp ax, 00h
	jnl mm1
	neg ax
	
mm1:	
	cwd
	idiv bx
	add dl,30h
	mov [out_str + si], dl
	dec si
	cmp ax, 00h
	jne mm1
	pop ax
	cmp ax, 00h
	jge mm2
	mov [out_str + si], 2dh
	
mm2:	
	ret
BinToAsc ENDP

c1 ENDS	
end start	
