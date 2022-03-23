c1 segment
	assume cs:c1
	org 100h
	main proc
		jmp init
		;резидентные данные
		old_21h_off 	dw ?			; Адрес старого обработчика 
		old_21h_seg 	dw ?			
		string 		db 'Boo, it is Resident Evil!!!$'		; Строка от резидента
		;резидентный код
		new_21:
				
				cmp ah,9
				je ok_09
				jmp dword ptr cs:old_21h_off	; Переход на старый обработчик, все как обычно
		ok_09:	

				push cs
				pop ds
				mov dx,offset string		; Замена при выводе любой строки на свою
				mov ah,9			
				jmp dword ptr cs:old_21h_off	; старый обработчик выполнится, но строку мы подменили	
	main endp

	init proc
		mov ax,3521h		; получим вектор прерывания 21h es:[bx] 
		int 21h			; но прежде чем изменить,  сохраним его
		mov word ptr old_21h_off,bx	; запишем старый адрес в old_21h_...
		mov word ptr old_21h_seg,es
		mov ax,2521h		; Установим новый обработчик
		mov dx,offset new_21	; наш код
		int 21h
		mov dx,(init-main+10FH)/16	; Завершить и оставить резидента
		mov ax,3100h
		int 21h
	;программа завершится,а резидент останется
	;теперь при запуске любой программы, которая вызовет функцию 9 int21
	;будет выводиться "наша" строка
	init endp
c1 ends
end main