;tsr ������������� 9 ������� int21
;������ �� ��������� �������� ����������� �����
;��������� ������� ���� 0AAAAh � ������ [new_21-2]
c1 segment
assume cs:c1,ds:c1
org 100h
main proc
	jmp init
old_21h_off 	dw ?			; ����� ������� ����������� 
old_21h_seg 	dw ?			
string 		db 'Boo, it is Resident Evil!!!$'		; ������ �� ���������
sign	 dw 0AAAAh			;��� ��������: ���������� �������� ��� ���
new_21:
		
		cmp ah,9
		je ok_09
		jmp dword ptr cs:old_21h_off	; ������� �� ������ ����������
ok_09:	

		push cs
		pop ds
		mov dx,offset string		; ������ ��� ������ ����� ������ 
		mov ah,9			; �� ���� - 'It is resident!!!'
		jmp dword ptr cs:old_21h_off		
main endp
init proc
		mov ax,3521h		;������� ����� ������� ���������� 21h 
		int 21h			;� es:[bx]
		mov ax, es:[bx-2]		; ��������� �� 2 ����� ����
		cmp ax, 0AAAAh		; ���� �� ��� � ������, �� ��� ��� ���
		je no_load			; ���� ��, �������� �� ���������
		mov word ptr old_21h_off,bx	; �������� ����� ������� � ����������� �����
		mov word ptr old_21h_seg,es
		mov ax,2521h		; ��������� ����
		mov dx,offset new_21
		int 21h
		mov dx,(init-main+10FH)/16	; �������� � ������� ���������
		mov ax,3100h
		int 21h
;�� ��� � ������, ������� �� ����
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