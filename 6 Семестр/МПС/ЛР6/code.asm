; �p���p �������� ���� ��� �������p�������� �p��p����
;
;
; ������ ���������
;
; �������� ���p�������� p�����p��
TMR0            EQU     01h
PC              EQU     02h
STATUS          EQU     03h
FSR             EQU     04h
; p�����p� �����/������
CNTRLPORT       EQU     05h
DATAPORT        EQU     06h
; ������ ���
SCRATCH         EQU     0Ch
DIGIT           EQU     0Dh
; ���� p�����p� STATUS
C               EQU     0h
DC              EQU     1h
Z               EQU     2h
PD              EQU     3h
TO              EQU     4h
RP              EQU     5h
; ��p�������� p�����p�
TRISA           EQU     85h
TRISB           EQU     86h
; ����� ������������� ��� ��p��� �����/������
INITA           EQU     B'00000000'
INITB           EQU     B'00000000'
;			 
; ������� ������
;
; ������ ������������ ����
        ORG     0
        GOTO    BEGIN
;
        ORG     100h
BEGIN
;������������� ����� �
        BCF     STATUS,RP    ;����� ����� 0
        CLRF    CNTRLPORT    ;�������� ������� CNTRLPORT
        MOVLW   INITA        ;���p����� B'00000000' � p�����p W
        BSF     STATUS,RP    ;����� ����� 1
        MOVWF   TRISA        ;��� ������� ����� � ���������� ��� ������
;������������� ����� �
        BCF     STATUS,RP    ;����� ����� 0
        CLRF    DATAPORT     ;�������� ������� DATAPORT
        MOVLW   INITB        ;���p����� B'00000000' � p�����p W
        BSF     STATUS,RP    ;����� ����� 1
        MOVWF   TRISB        ;��� ������� ����� � ���������� ��� ������ 
;
        BCF     STATUS,RP    ;����� ����� 0
;

Loop
;������ �������
;	MOVLW   B'01010101'     ;���p����� 01010101 � p�����p W
;	ADDLW	B'10101010'	
;	MOVWF   DATAPORT

;������ �������
;	MOVLW   B'11110000'
;	MOVWF   DATAPORT
;	SWAPF	DATAPORT, 0
;	MOVWF   DATAPORT
;������ �������
;	MOVLW   B'11001100'
;	MOVWF   DATAPORT
;	MOVLW   B'11110011'
;	ANDWF   DATAPORT,0
;	MOVWF   DATAPORT
	
	goto Loop
;
 END
