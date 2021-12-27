.MODEL SMALL
p1 macro f1;�뢮� ᮮ�饭�� �� �࠭
	push ax
	push dx
	mov dx,offset f1
	mov ah,9
	int 21h
	pop dx
	pop ax
endm
p2 macro f2;���� ��ப� ᨬ�����
	push ax
	push dx
	mov dx,offset f2
	mov ah,0ah
	int 21h
	pop dx
	pop ax
endm
.data
mess0 db 'Input:5 numbers in [-29999,29999]',10,13,'$'
mess00 db 'Press <Enter> after each number',10,13,'$'
mess1 db 'Enter number:$'
in_str label byte ;��ப� ᨬ����� (�� ����� 6)
razmer db 7
kol db (?)
stroka db 7 dup (?)   ;���� �᫠ (��� ����⥫���), 5 ���, enter
number dw 5 dup (0)   ;���ᨢ �ᥫ
siz dw 5              ;������⢮ �ᥫ
maxnum dw 0           ;�������襥
minnum dw 0           ;�������襥
negNum dw 5 dup (0)   ;����⥫�� ������
posNum dw 5 dup (0)   ;������⥫�� ������
negSum dw 0           ;�㬬� ����⥫���
posSum dw 0           ;�㬬� ������⥫���
posAvg dw 0		      ;�।��� �����⥫��� �ᥫ
posKol dw 0 		  ;������⢮ ������⥫���
perevod db 10,13,'$'
text_err1 db 'Input error!',10,13,'$'
messovf db 13,10,7,'Overflow!','$'
mesposavg db 13,10,'Positive Average:','$'
messmax db 13,10,'Max:','$'
messmin db 13,10,'Min:','$'
mesposkol db 13,10,'Count of positive:','$'
mesnegSum db 13,10,'Sum of negative:','$'
mesposSum db 13,10,'Sum of positive:','$'
out_str db 6 dup (' '),'$'
flag_err equ 1
.stack 256
.code
start: 		mov ax,@data
		mov ds,ax

;�맮� �㭪樨 0 -  ��⠭���� 3 ⥪�⮢��� �����०���, ���⪠ �࠭�
		mov ax,0003  ;ah=0 (����� �㭪樨),al=3 (����� ०���)
		int 10h
		p1 mess0
		p1 mess00
;横� �����, di - ����� �᫠ � ���ᨢ�
       		xor di,di
       		mov cx, siz ; � cx - ࠧ��� ���ᨢ�
vvod:		push cx

m1:		p1 mess1     ;�뢮� ᮮ�饭�� � ����� ��ப�
;���� �᫠ � ���� ��ப�
		p2 in_str
		p1 perevod
;�஢�ઠ ��������� �������� �ᥫ (-29999,+29999)
		call diapazon
		cmp bh,flag_err  ;�ࠢ��� bh � flag_err
		je err1          ;�᫨ ࠢ�� -ᮮ�饭�� �� �訡�� �����
;�஢�ઠ �����⨬��� �������� ᨬ�����
		call dopust
		cmp bh,flag_err
		je err1
;�८�ࠧ������ ��ப� � �᫮
		call AscToBin
		inc di
		inc di
		pop cx
		loop vvod
		jmp arifmet
err1:   		p1 text_err1	
		jmp m1
		
OVR:	p1 messovf  ;�뢮� ᮮ�饭�� � ��९�������
		jmp PROGEND
;���� ��� ��䬥��᪮� ��ࠡ�⪨
;*******************************************************************************
arifmet:
		mov cx, siz 	; � (cx) - ࠧ��� ���ᨢ�
		xor si,si
;���� ���ᨬ��쭮�� � �������쭮�� ����⮢
		mov ax,number
		mov maxnum,ax
		mov minnum,ax
		
max:
		mov ax,number+si
		cmp ax,maxnum
		jle min
		mov maxnum,ax
		jmp min
		
min:	cmp ax,minnum
		jge next
		mov minnum,ax
		jmp next

next: 	inc si
		inc si
		loop max
		
; ���� ����⥫��� ����⮢ � ����� �� �㬬�
		mov cx, siz 	; � (cx) - ࠧ��� ���ᨢ�
		mov si, offset number
		mov di, offset negNum
negFind:	
		mov ax, [si]
		cmp ax, 0
		jge endNegFind
		mov [di], ax
		add negSum, ax ; �㬬� ����⥫���
		jo  OVR; �᫨ �ந��諮 ��९�������
		
		inc di
		inc di
	
endNegFind:
		inc si
		inc si
		loop negFind
		
		mov cx, siz
		mov si, offset number
		mov di, offset posNum
		xor bx, bx
; ���� ������⥫��� ����⮢	� ����� �� �।����
posFind:
		mov ax, [si]
		cmp ax, 0
		jl endPosFind
		mov [di], ax
		add posSum, ax ; �㬬� ������⥫���
		jo  OVR; �᫨ �ந��諮 ��९�������
		
		inc di
		inc di
		inc bx	; ��⠥� ������⢮ ������⥫��� ����⮢
		
	
endPosFind:
		inc si
		inc si
		loop posFind
	
; ���� �।���� ������⥫쭮��
		mov dx,0
		mov ax,posSum
		cmp bx,0
		je endAvg
		div bx
		mov posAvg, ax
endAvg: 
		
;********************************************************************************************
;�뢮� १���� �� �࠭
		p1 messmax
		mov ax,maxnum	
		call BinToAsc
		p1 out_str
		call clearOutputStr
		
		p1 messmin
		mov ax,minnum	
		call BinToAsc
		p1 out_str
		call clearOutputStr
		
		p1 mesnegSum
		mov ax,negSum	
		call BinToAsc
		p1 out_str
		call clearOutputStr
		
		p1 mesposSum
		mov ax,posSum	
		call BinToAsc
		p1 out_str
		call clearOutputStr
					
		p1 mesposavg
		mov ax,posAvg	
		call BinToAsc
		p1 out_str


		jmp PROGEND

PROGEND:	
		mov ax,4c00h
		int 21h
		
clearOutputStr PROC
	xor si, si
	mov si, offset out_str
	push cx
	mov cl, 06h
_clearCycle:
	mov [si], byte ptr ' '
	inc si
	loop _clearCycle
	pop cx
	ret
ENDP
	
DIAPAZON PROC
;�஢�ઠ ��������� �������� �ᥫ -29999,+29999
;���� ����� - stroka
;�१ bh �����頥��� 䫠� �訡�� �����
        xor bh,bh;
	xor si,si;      ����� ᨬ���� � �������� �᫥
;�᫨ ����� ����� 5 ᨬ����� �஢�ਬ �� �����⨬����
	cmp kol,5
	jb dop
;�᫨ ����� 5 ��� ����� ᨬ����� �஢�ਬ ���� �� ���� ����ᮬ
	cmp stroka,2dh
	jne plus ;   �᫨ 1 ᨬ��� �� �����,�஢�ਬ �᫮ ᨬ�����
;�᫨ ���� - ����� � ᨬ����� ����� 6 �஢�ਬ �����⨬���� ᨬ����� 
	cmp kol,6
	jb dop        
	inc si;         ���� �஢�ਬ ����� ����
	jmp first

plus:   cmp kol,6;      ������� 6 ᨬ����� � ���� - �� ����� 
	je error1;       �訡��
first:  cmp stroka[si],32h;�ࠢ��� ���� ᨬ��� � 2
	jna dop;�᫨ ���� <=2 -�஢�ਬ �����⨬���� ᨬ�����
error1:	mov bh,flag_err;���� bh=flag_err
dop:	ret
DIAPAZON ENDP
DOPUST PROC
;�஢�ઠ �����⨬��� �������� ᨬ�����
;���� ����� - stroka
;si - ����� ᨬ���� � ��ப�
;�१ bh �����頥��� 䫠� �訡�� �����
	xor bh,bh
        xor si,si
	xor ah,ah
	xor ch,ch
	mov cl,kol;� ch ������⢮ ��������� ᨬ�����
m11:	mov al,[stroka+si]; � al - ���� ᨬ���
	cmp al,2dh;���� �� ᨬ��� ����ᮬ
	jne testdop;�᫨ �� ����� - �஢�ઠ �����⨬���
	cmp si,0;�᫨ �����  - ���� �� �� ���� ᨬ�����
	jne error2;�᫨ ����� �� ���� -�訡��
	jmp m13
;���� �� �������� ᨬ��� ��ன
testdop:cmp al,30h
	jb error2
	cmp al,39h
	ja error2
m13: 	inc si
	loop m11
	jmp m14
error2:	mov bh, flag_err;�� �������⨬��� ᨬ���� bh=flag_err
m14:	ret
DOPUST ENDP
AscToBin PROC
;� cx ������⢮ ��������� ᨬ�����
;� bx - ����� ᨬ���� ��稭�� � ��᫥����� 
;���� �ᥫ - number, � di - ����� �᫠ � ���ᨢ�
	xor ch,ch
	mov cl,kol
	xor bh,bh
	mov bl,cl
	dec bl
	mov si,1  ;� si ��� ࠧ�鸞
n1:	mov al,[stroka+bx]
	xor ah,ah
	cmp al,2dh;�஢�ਬ ���� �᫠
	je otr    ; �᫨ �᫮ ����⥫쭮�
	sub al,30h
	mul si
	add [number+di],ax
	mov ax,si
	mov si,10
	mul si
	mov si,ax
	dec bx
	loop n1
	jmp n2
otr:	neg [number+di];�।�⠢�� ����⥫쭮� �᫮ � �������⥫쭮� ����
n2:	ret
AscToBin ENDP
BinToAsc PROC
;�८�ࠧ������ �᫠ � ��ப�
;�᫮ ��।����� �१ ax
	xor si,si
	add si,5
	mov bx,10
	push ax
	cmp ax,0
	jnl mm1
	neg ax
mm1:	cwd
	idiv bx
	add dl,30h
	mov [out_str+si],dl
	dec si
	cmp ax,0
	jne mm1
	pop ax
	cmp ax,0
	jge mm2
	mov [out_str+si],2dh
mm2:	ret
BinToAsc ENDP
         		
end start