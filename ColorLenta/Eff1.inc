MakeArrayEff1:
nop
MakeArray:
    LDI R19, 30       ; ���������� ���� ������
	
	LDI R21, 250       ;  ����� ����
	LDI R22, 250      ;  ������� ����
	LDI R23, 250      ;  ������ ����
ArrayLed:      
	PUSH R21 ; ����� ����
	PUSH R22 ; ������� ����
	PUSH R23 ; ������ ����

	DEC R19
	BRNE ArrayLed
RET



