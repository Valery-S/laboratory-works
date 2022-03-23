;обработчик прерываний таймера
data segment
	old_8 dd ?
data ends

stk segment para stack 'stack'
	dw 100 dup (?)
stk ends

code segment
	assume cs:code,ds:data,ss:stk
	main proc
			mov ax,data
			mov ds,ax
	;получим адрес стандартного обработчика
			mov ax,3508h	
			int 21h			;vector v es:bx
			mov word ptr old_8,bx
			mov word ptr old_8+2,es
	;установим новый обработчик, адрес в ds:dx
			mov ax,2508h
			mov dx,offset new_8
			mov cx,seg new_8
			mov ds,cx
			int 21h

	;сейчас 18,2 раз в секунду будет вызываться наш бработчик
	;чтобы "увидеть" его выполнение вызовем функцию с ожиданием нажатия клавиши	
			mov ah,01
			int 21h
	;восстановим старый
			mov ax,2508h
			lds dx,old_8
			int 21h

			mov ax,4c00h
			int 21h
	main endp
	
	;новый обработчик
	new_8 proc
	;вывод символа V на экран
			push ax
			mov ah,0eh
			mov al,'V'
			int 10h
		
	;EOI
			mov al,20h
			out 20h,al
			pop ax
			iret
	new_8 endp
	code ends
end main

	