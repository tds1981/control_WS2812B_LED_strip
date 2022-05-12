.list
.CSEG
.ORG 0x0000
; --------------- �������� ��������� ������ ������������ ����� ---------------------
.def Temp1 = R16
.def Temp2 = R17

.def Regim = R25 
	ldi r16, 0x01
	mov Regim, r16 

	ldi Temp1, 0	; �����
.def Blue = R10    ; ������� �����
	mov Blue, Temp1

	ldi Temp1, 0	; �������
.def Red = R11
	mov Red, Temp1

	ldi Temp1, 0	; ������
.def Green = R12
	mov Green, Temp1 

	ldi Temp1, 30
.def CountLED = R13
	mov CountLED, Temp1
	
	ldi Temp1, 0
.def RunPixel = R5
	mov RunPixel, Temp1

.def MyTimer = R6
	mov MyTimer, Temp1

; -------------------------------------------------------------

LDI R16,Low(RAMEND) ; ������������� �����
OUT SPL,R16
LDI R16,High(RAMEND)
OUT SPH,R16

ldi r16, 0xff
out DDRD, r16  ; ���� D1 � D2, 3 � 4 � 5 �� ����� DDRD=1 

ldi r16, 0x00
out DDRB, r16   ; ������: ���� B1 � B2 �� ���� DDRB=0  
ldi r16, 0xff
out PORTB, r16   ; ������: �������� ��������� 

ldi r16, 0x80	; ���������� �����������
out ACSR, r16

; ----------------------- ������������� ������� �1 ------------------------
ldi Temp1, 0b00000101 ; �������� ������� / 1024 (� ������ ��������)
out TCCR1B, Temp1	 ; ������������� ������� T1
CLR Temp1
out TCNT1H, Temp1
out TCNT1L, Temp1

; ------------------------- ������ ��������� ����� ���������  -----------------------------------
StartProgram:

	in  Temp1, TCNT0 ; ����� �������
	cpi Temp1, 107
	brlo NoTime
	inc MyTimer ; 1��� = 128 ��. � MyTimer 
NoTime:

	RCALL RegimWorks    ; ����� ������������ ��������� ������ �� ����� RegimWork.inc

;---------------------------  ����� ������ (������� �� ����� RegimWork.inc) -----------------------------------------------	
	RCALL NewRegimButton
	RCALL PlusButton
	RCALL MinusButton

	;LDI Temp2, 2    ; �������� �� 37 ����
	;RCALL Delay     ; �������� ����� ������� ��������� ������ 
	
rjmp StartProgram

; --------------- ������������ ---------------------------

.include "RegimWork.inc"
.include "ShowLED.inc"
.include "Effects.inc"

;.include "Eff1.inc"
;  .include "Eff2.inc"
;.include "Eff3.inc"

; ------ ������������ ��������. � Temp2 ��������� ������������ ��������. ���� ������� Temp2 = 18 ����. (1 ��� = 54 ��. � Temp2)
DelayT0:       
	ldi Temp1, 0b00000101 ; �������� ������� / 1024 (� ������ ��������)
	out TCCR0, Temp1	 ; ������������� ������� T0 
	CLR Temp1
	out TCNT0,Temp1
Delay123:
	in  Temp1, TCNT0
	cpi  Temp1, 255
	brne Delay123
	CLR Temp1
	out TCNT0,Temp1
	DEC Temp2
	brne Delay123
	RET

;---------------------------------------------
;Delay:           ; ������������ ��������
;	mov r2, Temp1
;	mov r3, Temp2
;	LDI Temp1, 255
;Delay1: 
;	nop
;	DEC Temp1
;	BRNE Delay1
;	mov Temp1,r2
;	mov Temp2, r3
;	RET

