
Delay:           ; �������� ����� ������� ��������� ������
	LDI R20, 5
Loopinloop:  
	nop
	DEC R20
	;SBI PORTD, 3 ;  ����� ������������ ��������� ���������� ��� 
	BRNE Loopinloop
	DEC R19
	BRNE Delay
	RET