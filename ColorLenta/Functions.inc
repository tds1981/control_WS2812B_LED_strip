
Delay:           ; задержка между циклами зажигани€ диодов
	LDI R20, 5
Loopinloop:  
	nop
	DEC R20
	;SBI PORTD, 3 ;  «ажеч индикаторный светодиод установить бит 
	BRNE Loopinloop
	DEC R19
	BRNE Delay
	RET