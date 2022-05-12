;
; НЕДОДЕЛАНО
; ------------- красный --------------
	LDI R19, 5			; количество пикселей
	LDI R20, 75         ;
	LDI R21, 0 
	LDI R22, 40
ArrayLed:                       
	PUSH R21			; синий цвет
	                 
	PUSH R20			; красный цвет
	ADD R20,R22 
           
	PUSH R21			; зелёный цвет

	DEC R19
	BRNE ArrayLed

;  красный и зелёный
	LDI R19, 5			; количество груп пикселей
	LDI R20, 75         ;
	LDI R21, 0 
	LDI R22, 40
ArrayLed1:                       
	PUSH R22			; синий цвет
	ADD R20,R22
	                 
	PUSH R20			; красный цвет
           
	PUSH R21			; зелёный цвет

	DEC R19
	BRNE ArrayLed1


	
	in R16, SPL

	