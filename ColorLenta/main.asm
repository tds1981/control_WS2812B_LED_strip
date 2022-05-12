.list
.CSEG
.ORG 0x0000
; --------------- Основные параметры работы светодиодной ленты ---------------------
.def Temp1 = R16
.def Temp2 = R17

.def Regim = R25 
	ldi r16, 0x01
	mov Regim, r16 

	ldi Temp1, 0	; синий
.def Blue = R10    ; фоновые цвета
	mov Blue, Temp1

	ldi Temp1, 0	; красный
.def Red = R11
	mov Red, Temp1

	ldi Temp1, 0	; зелёный
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

LDI R16,Low(RAMEND) ; инициализация стека
OUT SPL,R16
LDI R16,High(RAMEND)
OUT SPH,R16

ldi r16, 0xff
out DDRD, r16  ; порт D1 и D2, 3 и 4 и 5 на вывод DDRD=1 

ldi r16, 0x00
out DDRB, r16   ; Кнопки: порт B1 и B2 на ввод DDRB=0  
ldi r16, 0xff
out PORTB, r16   ; Кнопки: включили резисторы 

ldi r16, 0x80	; Выключение компоратора
out ACSR, r16

; ----------------------- Инициализация таймера Т1 ------------------------
ldi Temp1, 0b00000101 ; тактовая частота / 1024 (с выхода делителя)
out TCCR1B, Temp1	 ; Инициализация таймера T1
CLR Temp1
out TCNT1H, Temp1
out TCNT1L, Temp1

; ------------------------- НАЧАЛО ОСНОВНОГО ЦИКЛА ПРОГРАММЫ  -----------------------------------
StartProgram:

	in  Temp1, TCNT0 ; замер времени
	cpi Temp1, 107
	brlo NoTime
	inc MyTimer ; 1сек = 128 ед. в MyTimer 
NoTime:

	RCALL RegimWorks    ; Вызов подпрограммы индикации режима из файла RegimWork.inc

;---------------------------  ОПРОС КНОПОК (функции из файла RegimWork.inc) -----------------------------------------------	
	RCALL NewRegimButton
	RCALL PlusButton
	RCALL MinusButton

	;LDI Temp2, 2    ; Задержка на 37 мсек
	;RCALL Delay     ; Задержка между циклами зажигания диодов 
	
rjmp StartProgram

; --------------- ПОДПРОГРАММЫ ---------------------------

.include "RegimWork.inc"
.include "ShowLED.inc"
.include "Effects.inc"

;.include "Eff1.inc"
;  .include "Eff2.inc"
;.include "Eff3.inc"

; ------ Подпрограмма задержки. В Temp2 заносится длительность задержки. Одна единица Temp2 = 18 мсек. (1 сек = 54 ед. в Temp2)
DelayT0:       
	ldi Temp1, 0b00000101 ; тактовая частота / 1024 (с выхода делителя)
	out TCCR0, Temp1	 ; Инициализация таймера T0 
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
;Delay:           ; Подпрограмма задержки
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

