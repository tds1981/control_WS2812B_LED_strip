;
; ����������
; ------------- ������� --------------
	LDI R19, 5			; ���������� ��������
	LDI R20, 75         ;
	LDI R21, 0 
	LDI R22, 40
ArrayLed:                       
	PUSH R21			; ����� ����
	                 
	PUSH R20			; ������� ����
	ADD R20,R22 
           
	PUSH R21			; ������ ����

	DEC R19
	BRNE ArrayLed

;  ������� � ������
	LDI R19, 5			; ���������� ���� ��������
	LDI R20, 75         ;
	LDI R21, 0 
	LDI R22, 40
ArrayLed1:                       
	PUSH R22			; ����� ����
	ADD R20,R22
	                 
	PUSH R20			; ������� ����
           
	PUSH R21			; ������ ����

	DEC R19
	BRNE ArrayLed1


	
	in R16, SPL

	