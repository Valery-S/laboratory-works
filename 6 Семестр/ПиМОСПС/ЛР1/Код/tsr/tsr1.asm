c1 segment
	assume cs:c1
	org 100h
	main proc
		jmp init
		;����������� ������
		old_21h_off 	dw ?			; ����� ������� ����������� 
		old_21h_seg 	dw ?			
		string 		db 'Boo, it is Resident Evil!!!$'		; ������ �� ���������
		;����������� ���
		new_21:
				
				cmp ah,9
				je ok_09
				jmp dword ptr cs:old_21h_off	; ������� �� ������ ����������, ��� ��� ������
		ok_09:	

				push cs
				pop ds
				mov dx,offset string		; ������ ��� ������ ����� ������ �� ����
				mov ah,9			
				jmp dword ptr cs:old_21h_off	; ������ ���������� ����������, �� ������ �� ���������	
	main endp

	init proc
		mov ax,3521h		; ������� ������ ���������� 21h es:[bx] 
		int 21h			; �� ������ ��� ��������,  �������� ���
		mov word ptr old_21h_off,bx	; ������� ������ ����� � old_21h_...
		mov word ptr old_21h_seg,es
		mov ax,2521h		; ��������� ����� ����������
		mov dx,offset new_21	; ��� ���
		int 21h
		mov dx,(init-main+10FH)/16	; ��������� � �������� ���������
		mov ax,3100h
		int 21h
	;��������� ����������,� �������� ���������
	;������ ��� ������� ����� ���������, ������� ������� ������� 9 int21
	;����� ���������� "����" ������
	init endp
c1 ends
end main