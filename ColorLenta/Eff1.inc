MakeArrayEff1:
nop
MakeArray:
    LDI R19, 30       ; количество груп байтов
	
	LDI R21, 250       ;  синий цвет
	LDI R22, 250      ;  красный цвет
	LDI R23, 250      ;  зелёный цвет
ArrayLed:      
	PUSH R21 ; синий цвет
	PUSH R22 ; красный цвет
	PUSH R23 ; зелёный цвет

	DEC R19
	BRNE ArrayLed
RET



