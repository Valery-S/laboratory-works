;tsr �������������  int21 ������� 9 � 99h
; ������� 99 ���������� ��� ������ �� ��������� �������� ����������� �����
;������ ��� ��������� ������� ������� 99 � ������� �� ����� � �������� �����
;���� ������� ����� ���������� ��� DADAh � �������� ax
c1 segment
assume cs:c1,ds:c1
org 100h
main proc
	jmp init
old_21h_off 	dw ?			; ����� ������� ����������� 
old_21h_seg 	dw ?			
string 		db 'Boo, it is Resident Evil!!!$'		; ������ �� ���������

new_21:
		
		cmp ah,9
		je ok_09
		cmp ah,99h; 	��� �������� ��� ��������
		jne no_me
		mov ax,0DADAh; 	��� ����� "��������" ��� ��������		
		iret
		
no_me:		jmp dword ptr cs:old_21h_off	; ������� �� ������ ����������
ok_09:	

		push cs
		pop ds
		mov dx,offset string		; ������ ��� ������ ����� ������ 
		mov ah,9			; �� ���� - 'It is resident!!!'
		jmp dword ptr cs:old_21h_off		
main endp
init proc
		mov ah,99h	;������� ������� 99 
		int 21h		;��������, ��� ��� "�������"

		cmp ax,0DADAh	;���� ��� �������� ��������, ������� "�����" ax= 0DADAh
		je no_load		;������, �������� ��� � ������, ������ ��� �� ���������, ������,��������
;�����, ������������� ����������, ��������� ��������
		mov ax,3521h		;������� ����� ������� ���������� 21h
		int 21h		
		mov word ptr old_21h_off,bx	;�������� ��� � ����������� �����
		mov word ptr old_21h_seg,es
		mov ax,2521h		; ��������� �����
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