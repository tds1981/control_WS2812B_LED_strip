; --------------- ��������� �������� ������ ������ ------------------------------------------
RegimWorks:
	CPI Regim, 1
	BRNE Reg2
	CBI PORTD, 2 ;  ��� ��������� 
	CBI PORTD, 3 ;  ���� ��������� 
	SBI PORTD, 4 ;  ���� ��������� 
Reg2:
	CPI Regim, 2
	BRNE Reg3
	SBI PORTD, 2 ;  ���� ��������� 
	CBI PORTD, 3 ;  ��� ��������� 
	CBI PORTD, 4 ;  ���� ��������� 
Reg3:
	CPI Regim, 3
	BRNE Reg4
	CBI PORTD, 2 ;  ��� ��������� 
	SBI PORTD, 3 ;  ��� ��������� 
	CBI PORTD, 4 ;  ���� ��������� 
Reg4:
	CPI Regim, 4
	BRNE Reg5
	SBI PORTD, 2 ;  ���� ��������� 
	SBI PORTD, 3 ;  ���� ��������� 
	CBI PORTD, 4 ;  ���� ��������� 
Reg5:
	CPI Regim, 5
	BRNE Reg6
	
	in Temp1,TCNT1L
	in Temp2,TCNT1H
	cpi Temp1, 0
	BRNE EndShowRegim
	cpi Temp2, 0b10000000 
	BREQ OffLed
	cpi Temp2, 0
	BREQ OnLed
	rjmp EndShowRegim

OnLed:
	SBI PORTD, 2 ;  ��� ��������� 
	SBI PORTD, 3 ;  ��� ��������� 
	SBI PORTD, 4 ;  ��� ��������� 
	rjmp EndShowRegim

OffLed:
	CBI PORTD, 2 ;  ���� ��������� 
	CBI PORTD, 3 ;  ���� ��������� 
	CBI PORTD, 4 ;  ���� ��������� 

	inc RunPixel
	CP  CountLED, RunPixel
	brsh NoMaxRunPixel
	clr RunPixel
NoMaxRunPixel:
	RCALL UpdateArrayLed    ; ������� ������� �������� ������� ������
	mov R19, CountLED       ; ���������� ���� ������
	clr  r29				;�������� ������� ���� Y
    ldi  r28, $60			;���������� ����� ������� ����� � ������� ���� Y
	add r28, RunPixel
	add r28, RunPixel
	add r28, RunPixel
	ldi Temp1, 0xff
	EOR Green, Temp1
	EOR Red, Temp1
	EOR Blue, Temp1
	ST Y+, Green  ; ������ ����
	ST Y+, Red	; ������� ����
	ST Y+, Blue	; ����� ����
	ST Y+, Green  ; ������ ����
	ST Y+, Red	; ������� ����
	ST Y+, Blue	; ����� ����
	ST Y+, Green  ; ������ ����
	ST Y+, Red	; ������� ����
	ST Y+, Blue	; ����� ����
	RCALL ShowLED			; ������� ������ ������� ������

Reg6:
	CPI Regim, 6
	BRNE EndShowRegim

	SBI PORTD, 2 ;  ��� ��������� 
	CBI PORTD, 3 ;  ��� ��������� 
	SBI PORTD, 4 ;  ��� ��������� 
	RCall Effect1

EndShowRegim:
	RET

; --------------------------------------------------------------------------------------------------
; ------------------ ����� ������ ���� ------------------
PlusButton:
	LDI Temp2, 0
ButtonControl1:
    in Temp1, PINB
	sbrc Temp1, 1
	RET
	inc Temp2    ; ������� ������������
	CPI Temp2, 255
	BRNE ButtonControl1

m1:	in Temp1, PINB  ;���� �������� ���������� ������
	sbrs Temp1, 1
	rjmp m1

	CPI Regim, 1
	BRNE PInstReg2

	LDI Temp1, 30
	CPSE CountLED, Temp1
	inc CountLED
	RCALL ShowLED

PInstReg2:
	CPI Regim, 2
	BRNE PInstReg3
	;LDI Temp1, 20
	;ADD Red, Temp1
	Mov Temp1, Red
	ANDI Temp1, 0b11110000
	SWAP Temp1
	inc Temp1
	SWAP Temp1
	ANDI Temp1, 0b11110000
	Ldi Temp2, 0b00001111
	AND Red, Temp2
	ADD  Red, Temp1
PInstReg3:
	CPI Regim, 3
	BRNE PInstReg4
	;LDI Temp1, 20
	;ADD Green, Temp1
	Mov Temp1, Green
	ANDI Temp1, 0b11110000
	SWAP Temp1
	inc Temp1
	SWAP Temp1
	ANDI Temp1, 0b11110000
	Ldi Temp2, 0b00001111
	AND Green, Temp2
	ADD  Green, Temp1
PInstReg4:
	CPI Regim, 4
	BRNE PInstEndShowRegim
	;LDI Temp1, 20
	;ADD Blue, Temp1
	Mov Temp1, Blue
	ANDI Temp1, 0b11110000
	SWAP Temp1
	inc Temp1
	SWAP Temp1
	ANDI Temp1, 0b11110000
	Ldi Temp2, 0b00001111
	AND Blue, Temp2
	ADD  Blue, Temp1
PInstEndShowRegim:
	RCALL UpdateArrayLed    ; ������� ������� �������� ������� ������
	RCALL ShowLED			; ������� ������ ������� ������
	RET
		
; -----------------------------------------------------------
; ------------------ ����� ������ ����� ---------------
MinusButton:
	LDI Temp2, 0
ButtonControl2:
    in Temp1, PINB
	sbrc Temp1, 2
	RET
	;rcall Delay
	inc Temp2    ; ������� ������������
	CPI Temp2, 255
	BRNE ButtonControl2

m2:	in Temp1, PINB	;���� �������� ���������� ������
	sbrs Temp1, 2
	rjmp m2

	CPI Regim, 1
	BRNE MInstReg2
	LDI Temp1, 1
	CPSE CountLED, Temp1
	dec CountLED
	RCALL ShowLED
MInstReg2:
	CPI Regim, 2
	BRNE MInstReg3
	;LDI Temp1, 20
	;SUB Red, Temp1
	Mov Temp1, Red
	inc Temp1
	ANDI Temp1, 0b00001111
	Ldi Temp2, 0b11110000
	AND Red, Temp2
	ADD  Red, Temp1
MInstReg3:
	CPI Regim, 3
	BRNE MInstReg4
	;LDI Temp1, 20
	;SUB Green, Temp1
	Mov Temp1, Green
	inc Temp1
	ANDI Temp1, 0b00001111
	Ldi Temp2, 0b11110000
	AND Green, Temp2
	ADD  Green, Temp1
MInstReg4:
	CPI Regim, 4
	BRNE MInstEndShowRegim
	;LDI Temp1, 20
	;SUB Blue, Temp1
	Mov Temp1, Blue
	inc Temp1
	ANDI Temp1, 0b00001111
	Ldi Temp2, 0b11110000
	AND Blue, Temp2
	ADD  Blue, Temp1
MInstEndShowRegim:
EndMinusB:
	RCALL UpdateArrayLed    ; ������� ������� �������� ������� ������
	RCALL ShowLED			; ������� ������ ������� ������
	RET

; --------------------------------------------------------------
; ------------------ ����� ������ ����� ------------------------
NewRegimButton:
	LDI Temp2, 0
ButtonControl3:
    in Temp1, PINB
	sbrc Temp1, 0
	RET
	;rcall Delay
	inc Temp2    ; ������� ������������
	CPI Temp2, 255
	BRNE ButtonControl3

m3:	in Temp1, PINB
	sbrs Temp1, 0
	rjmp m3

	INC Regim		; ������� � ������ ������ 
	CPI Regim, 7
	BRNE EndNewRegimButton
	SUBI Regim, 6

	CPI Regim, 6 ;������������� ������ 6
	BRNE EndNewRegimButton
	clr Red
	clr Blue
	clr Green
	RCALL UpdateArrayLed
	RCALL ShowLED

EndNewRegimButton:
	RET


