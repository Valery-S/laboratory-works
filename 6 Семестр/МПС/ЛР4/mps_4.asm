const addrPrinter 5h
const addrKeyRowScan 3h
const addrKeyColScan 4h
const addrSpeacker 6h
const addrPrinterReady 7h
const stackPosition 0500h ; �������� ������� ����� ��-���������
const lastSymbolPosition 80h ; ��� ��������� ������� ����������

jmp begin

skip 30h
jmp interruptReq

skip 100h

:begin

lxi sp, stackPosition
ei
jmp selectText1

:start
    ; ****************************
    ; Return to normal background*
    ; ****************************
    lda needRestart
    cpi 00h
    jnz checkText
    
    jmp selectText1
    
:checkText
    ; ***************************
    ; Check for other job       *
    ; ***************************
   
lda currentText
cpi 00h
jz selectText1
jmp selectText2
   
:selectText1
    lxi h, text
    shld currentText
    jmp output
    
:selectText2
    lxi h, textName
    shld currentText
    jmp output
    
:output
    mvi a, 00h
    sta needRestart

    mvi e, 01h ; ������������� ����� �������� ������������ �������
    ;lxi b, 8000h ; ��������� ����������� ���� BC ��������� 8000h
    ;stax b ; ��������� "0" � ������� ������� ( "�����" ��������� )
    out 00h
    
    lhld currentText
    ;lxi h, text ; ��������� � ����������� ���� HL ����� ������� ��������
                ; �.� ����� ������� �������
    
    
; ����� ������� �������
:prepareFirstSymbol
    
    ;lxi sp, stackPosition ; ��������� ������� �����
    push h ; ���������� ����� �������� ������� � �����
    
    mvi a, 01h ; ������ ������� ����������� 1-�� �������
    ;sphl ; ��������� ������� ����� � ������ ��������� ������
    
:showSymbol
    ;pop h ; ��������� � HL ����� ������������� �������
    
    mov d, a
    push h
    
    mov a, m
    cpi 0FFh
    jnz nextSymbol
    inx h
    mov a, m
    cpi 0FFh
    jnz nextSymbol
    
    pop h
    pop h ; extct old h
    jmp start
    
:nextSymbol
    pop h

    mov a, d
    ; show next symbol

    mov d, a
    mov a, m
    ;sta 8001h
    out 01h
    inx h
    mov a, m
    ;sta 8002h
    out 02h
    inx h
    mov a, d
    
    ;shld 8001h ; ���������� � (8001h) �������� �� ����������� ���� HL
               ; �.� ����� � �������� DD6 � DD7
    
    ;inx h
    ;inx h
    ;shld currentSymbol
    
    ;stax b ; ��������� ���������� ������������ A �� ������ (BC) 
           ; �.� ����������� ������������ �������
    out 00h
    
    mov d, a ; ��������� ������� ������� � �������� D
             ; �.�. ����������� ����������� ��� ��������
    
    mvi a, 1h ; ��������� � ����������� "����� ��������"
    
; ���� ���� ����������� �� ������ ������ ����
:waitLoop
    dcr a
    cpi 00h
    jnz waitLoop
    
    ; ������� ������� �������
    mvi a, 0h 
    ;stax b
    out 00h
    
    ; ����� ��������
    
    mov a, d ; ��������������� ����� ������� ������� � �����������
    
    cpi lastSymbolPosition ; ���������, �������� �� ������� ��������� � ���������� 
    jz loadNextSymbol ; ���� ��������� ��������� � ���������� �������
    
    rlc ; ��������� ����� ������� ������� � ����������
    ;mov d, a ; ��������� ����� ������� � �������� D
    
    jmp showSymbol ; ��������� ���� �� �������� ���� ���������
    
:loadNextSymbol
    ;lxi sp, stackPosition ; ��������������� ����������� ������� ������� �����
    ;dcx sp ; ��������� �������� ������� ����� �� 2 �.� � ����� ��� ���� 
    ;dcx sp ; ����������� ������� ����������� ���� HL
    
    pop h ; �������� ����� �������� ������� � 1-� ������� �� ����������
    inx h ; ����������� �� 2 ��� �� �������� ����� ���������� �������������
    inx h ; �������
    
    lda needRestart
    cpi 01h
    jnz prepareFirstSymbol
    
    jmp start

 :interruptReq
    ;saving variables
    push b
    push d
    mov e, a
    push h
   
   lxi h, oldKeyboardState
   
    ; scan 1s line
    mvi a, 01h
    out addrKeyRowScan
    
    in addrKeyColScan
    cmp m
    jz check2Row
    
    mov m, a
    cpi 00h
    jz check2Row
    
    mvi a, 01h
    sta needRestart
    sta currentText
    
    jmp endOfInt
    
:check2Row
    inx h

    mvi a, 02h
    out addrKeyRowScan
    
    in addrKeyColScan
    cmp m
    jz check3Row
    
    mov m, a
    cpi 00h
    jz check3Row
    
    push h
    lxi h, printerText
    
    :printerLoop
        mov a, m
        cpi 00h
        jz endPrinterLoop
        push d
        mov d, a
        
        :printerWait
            in addrPrinterReady
            cpi 00h
            jz endPrinterWait
            jmp printerWait
            
        :endPrinterWait
            mov a, d
            pop d
        
        out addrPrinter
        inx h
        jmp printerLoop
        
    :endPrinterLoop
    pop h
    
    jmp endOfInt
    
:check3Row
    inx h

    mvi a, 04h
    out addrKeyRowScan
    
    in addrKeyColScan
    cmp m
    jz endOfInt
    mov m, a
    
    cpi 00h
    jz endOfInt

    mvi a, 00h
    out addrSpeacker
    mvi a, 01h
    out addrSpeacker
    
:endOfInt 
    pop h
    mov a, e
    pop d
    pop b
 
    ei
    ret
; ******************************************************************************
; * ������ ������                                                              *
; ****************************************************************************** 

currentText dw 00h
needRestart db 00h

oldKeyboardState db 00h, 00h, 00h, 00h

printerText db '15-3-2022', 00h

text dw 0h,0h, 0h,0939h, 0939h, 003fh, 025ch, 0h, 0h,0FFFFh
textName dw 0h, 0h,39h,6eh,600h,900h,3fh,73h,6eh,930h,3fh,939h,0h, 0h,0FFFFh
