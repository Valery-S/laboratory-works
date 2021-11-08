; ������������ ������ �2
; ��������� �������
; ������������ a(n),a(n-1),a(n-2),...,a(n/2),a(1),a(2),...,a(n/2-1).
; ��������������� ���������. �������� exe ����

.model small
.stack 200h

d1 segment para public 'data'
mess1 db 'Input: ',10,13,'$'
in_str db 22 dup (?)
d1 ends

e1 segment para public 'data'
mess2 db 10,13, 'Output: ',10,13,'$'
out_str db 20 dup ('$')
e1 ends


c1 segment para public 'code'
assume cs:c1, ds:d1, es:e1

start:
    ;������������� ���������
    mov ax, d1
    mov ds, ax
    mov ax, e1
    mov es, ax

    ;����� ������ ������� 
    mov dx, offset mess1
    mov ah, 9
    int 21h

    ;���������� ��������� �������
    mov dx, offset in_str
    mov in_str, 20
    mov ah, 10
    int 21h

    ;������������� �������� ��������� ������ �� ����� ��������� �������
    mov cl, in_str + 1         ;���������� ��������� � �������
    xor ch, ch                 ;������� �������� ch
    mov ax, offset in_str+1    ;�����, �������������� ������� ��������  
    add ax,cx                  ;������ ������ ���������� ��������
    mov si,ax                  ;������������� �������� ��������� ������ 
    
    ;������������� �������� �������� ������ �� ������ ��������� �������
    mov di, offset out_str

    ;����������� ����� ���������� ������� ����� - ���������� ������ 
    ;����� ��������� ������� � ������ ������ � �������� �������.
    ;����� ���������� - ���������� ��������� ������ �� 2.
    shr cx,1                    ;������� ����������� ������� �� 1 � �����
    
m1:
    mov al, [si]
    mov es:[di],al
    dec si
    inc di
    loop m1

    ;������������� �������� ��������� ������ �� ������ ��������� �������
    mov si, offset in_str+2

    ;����������� ����� ���������� ������� ����� - ���������� ������ 
    ;����� ��������� ������� � ����� ������.
    ;����� ���������� - ���������� ��������� ������ �� 2.
    mov cl, in_str + 1              
    shr cx,1


m2:
    mov al,[si]
    mov es:[di],al
    inc si
    inc di
    loop m2

    ;����� ������, �������������� ��������� �������
    mov ax, es
    mov ds, ax
    mov dx, offset mess2
    mov ah, 9
    int 21h

    ;����� ������ �������
    mov dx, offset out_str
    mov ah, 9
    int 21h

    mov ah, 7
    int 21h

    mov ax, 4c00h
    int 21h

c1 ends

end start