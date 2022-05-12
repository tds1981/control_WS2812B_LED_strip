Effect1:
	in Temp1,TCNT1L ;замер времени
	in Temp2,TCNT1H
	cpi Temp1, 0
	BRNE EndRET

	cpi Temp2, 0
	BREQ IncRed
	cpi Temp2, 40
	BREQ NRed
	cpi Temp2, 85
	BREQ IncBlue
	cpi Temp2, 125
	BREQ NBlue
	cpi Temp2, 165
	BREQ IncGreen
	cpi Temp2, 205
	BREQ NGreen
	RET
IncRed:
	INC Red
	rjmp EndEffect1
IncBlue:
	INC Blue
	rjmp EndEffect1
IncGreen:
	INC Green
	rjmp EndEffect1
NRed:
	ldi Temp1, 0xf0
	SWAP Red
	SWAP Blue
	SWAP Green
	rjmp EndEffect1
NBlue:
	ldi Temp1, 0xf0
	SWAP Red
	SWAP Blue
	SWAP Green
	;AND Red, Temp1
	;AND Blue, Temp1
	;AND Green, Temp1
	rjmp EndEffect1
NGreen:
	ldi Temp1, 0xf0
	SWAP Red
	SWAP Blue
	SWAP Green
	;AND Red, Temp1
	;AND Blue, Temp1
	;AND Green, Temp1
	rjmp EndEffect1

EndEffect1:	
	RCALL UpdateArrayLed
	RCALL ShowLED   ;отображение пикселей
EndRET:	RET


	;Push Red
	;Push Blue
	;Push Green
	;clr Red
	;clr Blue
	;clr Green