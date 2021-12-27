.MODEL SMALL
p1 macro f1;вывод сообщений на экран
	push ax
	push dx
	mov dx,offset f1
	mov ah,9
	int 21h
	pop dx
	pop ax
endm
p2 macro f2;ввод строки символов
	push ax
	push dx
	mov dx,offset f2
	mov ah,0ah
	int 21h
	pop dx
	pop ax
endm
.data
mess0 db 'Input:5 numbers in [-29999,29999]',10,13,'$'
mess00 db 'Press <Enter> after each number',10,13,'$'
mess1 db 'Enter number:$'
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
text_err1 db 'Input error!',10,13,'$'
messovf db 13,10,7,'Overflow!','$'
mesposavg db 13,10,'Positive Average:','$'
messmax db 13,10,'Max:','$'
messmin db 13,10,'Min:','$'
mesposkol db 13,10,'Count of positive:','$'
mesnegSum db 13,10,'Sum of negative:','$'
mesposSum db 13,10,'Sum of positive:','$'
out_str db 6 dup (' '),'$'
flag_err equ 1
.stack 256
.code
start: 		mov ax,@data
		mov ds,ax

;вызов функции 0 -  установка 3 текстового видеорежима, очистка экрана
		mov ax,0003  ;ah=0 (номер функции),al=3 (номер режима)
		int 10h
		p1 mess0
		p1 mess00
;цикл ввода, di - номер числа в массиве
       		xor di,di
       		mov cx, siz ; в cx - размер массива
vvod:		push cx

m1:		p1 mess1     ;вывод сообщения о вводе строки
;ввод числа в виде строки
		p2 in_str
		p1 perevod
;проверка диапазона вводимых чисел (-29999,+29999)
		call diapazon
		cmp bh,flag_err  ;сравним bh и flag_err
		je err1          ;если равен -сообщение об ошибке ввода
;проверка допустимости вводимых символов
		call dopust
		cmp bh,flag_err
		je err1
;преобразование строки в число
		call AscToBin
		inc di
		inc di
		pop cx
		loop vvod
		jmp arifmet
err1:   		p1 text_err1	
		jmp m1
		
OVR:	p1 messovf  ;вывод сообщения о переполнении
		jmp PROGEND
;место для арифметической обработки
;*******************************************************************************
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
		jo  OVR; Если произошло переполнение
		
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
		jo  OVR; Если произошло переполнение
		
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
		
;********************************************************************************************
;вывод результата на экран
		p1 messmax
		mov ax,maxnum	
		call BinToAsc
		p1 out_str
		call clearOutputStr
		
		p1 messmin
		mov ax,minnum	
		call BinToAsc
		p1 out_str
		call clearOutputStr
		
		p1 mesnegSum
		mov ax,negSum	
		call BinToAsc
		p1 out_str
		call clearOutputStr
		
		p1 mesposSum
		mov ax,posSum	
		call BinToAsc
		p1 out_str
		call clearOutputStr
					
		p1 mesposavg
		mov ax,posAvg	
		call BinToAsc
		p1 out_str


		jmp PROGEND

PROGEND:	
		mov ax,4c00h
		int 21h
		
clearOutputStr PROC
	xor si, si
	mov si, offset out_str
	push cx
	mov cl, 06h
_clearCycle:
	mov [si], byte ptr ' '
	inc si
	loop _clearCycle
	pop cx
	ret
ENDP
	
DIAPAZON PROC
;проверка диапазона вводимых чисел -29999,+29999
;буфер ввода - stroka
;через bh возвращается флаг ошибки ввода
        xor bh,bh;
	xor si,si;      номер символа в вводимом числе
;если ввели менее 5 символов проверим их допустимость
	cmp kol,5
	jb dop
;если ввели 5 или более символов проверим является ли первый минусом
	cmp stroka,2dh
	jne plus ;   если 1 символ не минус,проверим число символов
;если первый - минус и символов меньше 6 проверим допустимость символов 
	cmp kol,6
	jb dop        
	inc si;         иначе проверим первую цифру
	jmp first

plus:   cmp kol,6;      введено 6 символов и первый - не минус 
	je error1;       ошибка
first:  cmp stroka[si],32h;сравним первый символ с 2
	jna dop;если первый <=2 -проверим допустимость символов
error1:	mov bh,flag_err;иначе bh=flag_err
dop:	ret
DIAPAZON ENDP
DOPUST PROC
;проверка допустимости вводимых символов
;буфер ввода - stroka
;si - номер символа в строке
;через bh возвращается флаг ошибки ввода
	xor bh,bh
        xor si,si
	xor ah,ah
	xor ch,ch
	mov cl,kol;в ch количество введенных символов
m11:	mov al,[stroka+si]; в al - первый символ
	cmp al,2dh;является ли символ минусом
	jne testdop;если не минус - проверка допустимости
	cmp si,0;если минус  - является ли он первым символом
	jne error2;если минус не первый -ошибка
	jmp m13
;является ли введенный символ цифрой
testdop:cmp al,30h
	jb error2
	cmp al,39h
	ja error2
m13: 	inc si
	loop m11
	jmp m14
error2:	mov bh, flag_err;при недопустимости символа bh=flag_err
m14:	ret
DOPUST ENDP
AscToBin PROC
;в cx количество введенных символов
;в bx - номер символа начиная с последнего 
;буфер чисел - number, в di - номер числа в массиве
	xor ch,ch
	mov cl,kol
	xor bh,bh
	mov bl,cl
	dec bl
	mov si,1  ;в si вес разряда
n1:	mov al,[stroka+bx]
	xor ah,ah
	cmp al,2dh;проверим знак числа
	je otr    ; если число отрицательное
	sub al,30h
	mul si
	add [number+di],ax
	mov ax,si
	mov si,10
	mul si
	mov si,ax
	dec bx
	loop n1
	jmp n2
otr:	neg [number+di];представим отрицательное число в дополнительном коде
n2:	ret
AscToBin ENDP
BinToAsc PROC
;преобразование числа в строку
;число передается через ax
	xor si,si
	add si,5
	mov bx,10
	push ax
	cmp ax,0
	jnl mm1
	neg ax
mm1:	cwd
	idiv bx
	add dl,30h
	mov [out_str+si],dl
	dec si
	cmp ax,0
	jne mm1
	pop ax
	cmp ax,0
	jge mm2
	mov [out_str+si],2dh
mm2:	ret
BinToAsc ENDP
         		
end start