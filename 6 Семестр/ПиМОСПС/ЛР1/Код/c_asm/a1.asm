.model small
extrn _printf:near
extrn _getch:near
extrn  _summ:word
PUBLIC _asmrazn
PUBLIC asmsumm
.CODE
_asmrazn PROC near           
	push bp
	mov bp,sp
;�맮� �㭪樨 � printf(mes1)
	mov dx,offset mes1
	push dx
	call _printf
	pop ax
    mov ax,[bp+4]     ;1-� ��㬥�� a
    sub ax,[bp+6]     ;2-�� ��㬥�� b, ࠧ����� a-b
;�����頥��� ���祭�� � AX
	push ax
    call _getch
	pop ax
	pop bp
	ret;��������, � �⥪ ����� �맢���� ��� �㭪��
_asmrazn endp

;��� ࠧ����ࠧ�� � ᫥���饩 ��楤�� �ᯮ��㥬 ;����������� ��।����� ��㬥��� � ��४⨢� PROC
;���冷� - ��� � ������� �㭪樨 �� ���:x-1-�;y-2-�� 
asmsumm PROC  near x:word,y:word
	push bp
	mov bp,sp
;�맮� �㭪樨 � printf(mes2)
	mov dx,offset mes2
	push dx
	call _printf
	pop ax
    mov ax,y            ;2-�� ��㬥�� b [bp+4]
    add ax,x            ;1-� ��㬥�� a [bp+6]� �㬬�
;�����頥��� ���祭�� _summ
	mov _summ,ax
    call _getch
	pop bp
	ret 4;�������� � ������ �⥪ (��⮫����� 4 ����)
asmsumm endp
.data
mes1 db "��楤�� �� ��ᥬ���� ������ a-b ",10,13,0
mes2 db 10,13,"��楤�� �� ��ᥬ���� ������ a+b",10,13,0
end;
