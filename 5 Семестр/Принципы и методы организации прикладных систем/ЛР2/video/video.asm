.model small

.stack 200h

.data

    bios equ 0FFFFh
    video equ 0B800h
    color equ 0A3h

.code

_main:
	;Инициализация сегментов
	mov ah, 0
	mov al, 3
	int 10h
	mov ax, bios
	mov es, ax

	mov ax, video
	mov ds, ax
	;Инициализация регистров источника и приёмника данных
    mov si, 05h
    mov di, 00h
	
	;Инициализация счётчика
    mov cx, 0008h

m1:
    mov al, es:[si]
    mov ah, color
    mov ds:[di], ax
    inc di
    inc di
    inc si
    loop m1

    mov ah, 4ch
    mov al, 0
    int 21h

end _main
