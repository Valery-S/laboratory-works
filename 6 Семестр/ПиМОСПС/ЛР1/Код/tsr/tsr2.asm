;tsr перехватывает 9 функцию int21
;защита от повторной загрузки резидентной части
;провер€ем наличие кода 0AAAAh в €чейке [new_21-2]
c1 segment
assume cs:c1,ds:c1
org 100h
main proc
	jmp init
old_21h_off 	dw ?			; јдрес старого обработчика 
old_21h_seg 	dw ?			
string 		db 'Boo, it is Resident Evil!!!$'		; —трока от резидента
sign	 dw 0AAAAh			;дл€ проверки: установлен резидент или нет
new_21:
		
		cmp ah,9
		je ok_09
		jmp dword ptr cs:old_21h_off	; ѕереход на старый обработчик
ok_09:	

		push cs
		pop ds
		mov dx,offset string		; «амена при выводе любой строки 
		mov ah,9			; на свою - 'It is resident!!!'
		jmp dword ptr cs:old_21h_off		
main endp
init proc
		mov ax,3521h		;ѕолучим адрес вектора прерывани€ 21h 
		int 21h			;в es:[bx]
		mov ax, es:[bx-2]		; обратимс€ на 2 байта выше
		cmp ax, 0AAAAh		; если мы уже в пам€ти, то там наш код
		je no_load			; если да, повторно не загружаем
		mov word ptr old_21h_off,bx	; сохраним адрес старого в резидентной части
		mov word ptr old_21h_seg,es
		mov ax,2521h		; ”становим свой
		mov dx,offset new_21
		int 21h
		mov dx,(init-main+10FH)/16	; «авершим и оставим резидента
		mov ax,3100h
		int 21h
;мы уже в пам€ти, сообщим об этом
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