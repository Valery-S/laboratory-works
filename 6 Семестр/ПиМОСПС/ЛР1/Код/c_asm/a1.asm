.model small
extrn _printf:near
extrn _getch:near
extrn  _summ:word
PUBLIC _asmrazn
PUBLIC asmsumm
.CODE
_asmrazn PROC near           
	push bp
	mov bp,sp
;Вызов функции С printf(mes1)
	mov dx,offset mes1
	push dx
	call _printf
	pop ax
    mov ax,[bp+4]     ;1-ый аргумент a
    sub ax,[bp+6]     ;2-ой аргумент b, разность a-b
;Возвращаемое значение в AX
	push ax
    call _getch
	pop ax
	pop bp
	ret;вернуться, а стек очистит вызвавшая нас функция
_asmrazn endp

;для разнообразия в следующей процедуре используем ;возможность определить аргументы в директиве PROC
;порядок - как в объявлении функции на ЯВУ:x-1-ый;y-2-ой 
asmsumm PROC  near x:word,y:word
	push bp
	mov bp,sp
;Вызов функции С printf(mes2)
	mov dx,offset mes2
	push dx
	call _printf
	pop ax
    mov ax,y            ;2-ой аргумент b [bp+4]
    add ax,x            ;1-ый аргумент a [bp+6]и сумма
;Возвращаемое значение _summ
	mov _summ,ax
    call _getch
	pop bp
	ret 4;вернуться и очистить стек (вытолкнуть 4 байта)
asmsumm endp
.data
mes1 db "Процедура на ассемблере вычисляет a-b ",10,13,0
mes2 db 10,13,"Процедура на ассемблере вычисляет a+b",10,13,0
end;
