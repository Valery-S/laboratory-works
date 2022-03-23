;tsr перехватывает  int21 функции 9 и 99h
; функцию 99 используем для защиты от повторной загрузки резидентной части
;прежде чем загружать вызовем функцию 99 и сравним ее ответ с заданным кодом
;наша функция будет возвращать код DADAh в регистре ax
c1 segment
assume cs:c1,ds:c1
org 100h
main proc
	jmp init
old_21h_off 	dw ?			; Адрес старого обработчика 
old_21h_seg 	dw ?			
string 		db 'Boo, it is Resident Evil!!!$'		; Строка от резидента

new_21:
		
		cmp ah,9
		je ok_09
		cmp ah,99h; 	нас вызывают для проверки
		jne no_me
		mov ax,0DADAh; 	так будет "отвечать" наш резидент		
		iret
		
no_me:		jmp dword ptr cs:old_21h_off	; Переход на старый обработчик
ok_09:	

		push cs
		pop ds
		mov dx,offset string		; Замена при выводе любой строки 
		mov ah,9			; на свою - 'It is resident!!!'
		jmp dword ptr cs:old_21h_off		
main endp
init proc
		mov ah,99h	;вызовем функцию 99 
		int 21h		;проверим, что она "ответит"

		cmp ax,0DADAh	;если наш резидент загружен, получим "ответ" ax= 0DADAh
		je no_load		;значит, резидент уже в памяти, второй раз не загружаем, уходим,сообщаем
;иначе, перехватываем прерывание, загружаем резидент
		mov ax,3521h		;Получим адрес вектора прерывания 21h
		int 21h		
		mov word ptr old_21h_off,bx	;сохраним его в резидентной части
		mov word ptr old_21h_seg,es
		mov ax,2521h		; Установим новый
		mov dx,offset new_21
		int 21h
		mov dx,(init-main+10FH)/16	; Завершим и оставим резидента
		mov ax,3100h
		int 21h
;мы уже в памяти, сообщим об этом
no_load: 		mov ah,40h
		mov dx,offset test_str
		mov cx,nn
		mov bx,1
		int 21h
		mov ax,4c00h
		int 21h
init endp
test_str db 'Your Resident already loaded!'
nn=$-test_str
c1 ends
end main