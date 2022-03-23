;Программа вычисляет сумму цифр в числе с помощью рекурсии
;Начальное число записывается в переменную number
;Результат записывается в переменную summa
.MODEL SMALL
.STACK 0FFH
.DATA
number dw 4321
summa dw 0
.CODE
sum proc 
		push bp
		mov bp,sp
		
		;Получаем аргумент из стека
		mov cx,[bp+4]
		
		;Получаем последнюю цифру числа
		mov ax,cx
		mov cx,10
		div cx
		
		;Добавляем к сумме последнюю цифру
		mov bx,summa
		add bx,dx
		mov summa,bx
		 
		;Проверяем число на наличие в нем цифр
		mov cx,ax
		jcxz end_p
		
		mov dx,0
		
		;Заносим в стек оставшееся число
		push ax
		call sum
end_p:	
		mov sp,bp
		pop bp	
		ret
sum endp
	
main:	
		;Инициализация сегмента данных
		mov ax,@data
		mov ds,ax	
		
       	push number
		call sum
		mov ax,4c00h
		int 21h

end main
