;тестовая программа для экспериментов с резидентом
c1 segment 
assume cs:c1, ds:c1,  ss:c1
org 100h
start:	
	mov ah, 9
	mov dx,offset mess_in
	int 21h
	
	mov ax, 4c00h
	int 21h
mess_in db 'No rezident!$'
c1 ends
end start