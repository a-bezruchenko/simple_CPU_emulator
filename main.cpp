// main.cpp: ���������� ����� ����� ��� ����������� ����������.
//

/*
	������ ������ ���������� ������ ���� � ������������, �� ��� ���� � ������

	����� �������� �� ��������� ���������� ��������
		1 � ���������� � ������� processor::getReg: 
		2 � ���������� � ������� processor::setReg

*/

#include "stdio.h"
#include "processor.h"

int getNumber(const char text[80], int minValue, int maxValue)
{
	int buff = minValue - 1;
	printf(text);
	while (buff < minValue || buff > maxValue)
	{
		scanf("%d", &buff);
		if (buff < minValue || buff > maxValue)
			printf("\nInvalid value! Value must be between %d and %d\n", minValue, maxValue);
	}
	return buff;
}

int main()
{
	/*
		���� ��������:
			0	LD R2 * 2^R3 + const
			1	LD const
			2	ST R2 * 2^R3 + const
			3	ST const
			4	ADD R2, R3
			5	ADD R2, const
			6	SHRA R2, R3
			7	SHRA R2, const
			8	NOR R2, R3
			9	NOR R2, const
			A	JE const
			B	JE R1 + const
			C	JMP const
			D	JMP R1 + const
			E	XCH R1, R2
			F	XCH R1, R2 (�� ��, ��� � E)
	*/

	// ����������� ������; char, ������ ��� ��������� ������������
	char RAM[256] = 
	{0x10,	// LD A, adr
	3,		// adr = 3
	0x40,	// ADD A, A
	42};	// MEM[3]
	
	
	// ��������������
	microcom microprogram[64]=
	{
		{false, r_A, 	false,	r_PC, 	false, r_IR1, 	0, 	false, true, false,		3, 	0},
		{false, r_PC, 	false,	r_A, 	false, r_PC, 	1, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_PC, 	false, r_IR2, 	0, 	false, true, false,		3, 	0},
		{false, r_temp, false,	r_temp, false, r_temp,  3, 	false, false, false,	4, 	0},
		{false, r_temp, false,	r_temp, false, r_temp, 	3, 	false, false, false,	1, 	9},
		{true,	r_B, 	true,	r_C, 	false, r_IR2, 	2, 	false, false, false,	3, 	0},
		{false, r_PC, 	false,	r_A, 	false, r_PC, 	1, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_PC, 	false, r_temp, 	0, 	false, true, false,		3, 	0},
		{false, r_temp, false,	r_IR2, 	false, r_IR2, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_IR2, 	true,  r_A, 	0, 	false, true, false,		2, 	55},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_temp, false,	r_temp, false, r_temp, 	3, 	false, false, false,	1, 	17},
		{true,	r_B, 	true,	r_C, 	false, r_IR2, 	2, 	false, false, false,	3, 	0},
		{false, r_PC, 	false,	r_A, 	false, r_PC, 	1, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_PC, 	false, r_temp, 	0, 	false, true, false,		3, 	0},
		{false, r_temp, false,	r_IR2, 	false, r_IR2, 	0, 	false, false, false,	3, 	0},
		{true,	r_A, 	false,	r_IR2, 	false, r_temp, 	0, 	false, false, true,		2, 	55},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_temp, false,	r_temp, false, r_temp, 	0, 	false, false, false,	1, 	22},
		{true,	r_B, 	true,	r_C,	true,  r_A, 	0, 	true, false, false,		2, 	55},
		{true,	r_B, 	false,	r_IR2, 	true,  r_A, 	0, 	true, false, false,		2, 	55},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_temp, false,	r_temp, false, r_temp, 	3, 	false, false, false,	1, 	28},
		{true,	r_B, 	true,	r_C, 	true,  r_A,		2, 	true, false, false,		2, 	55},
		{true,	r_B, 	false,	r_IR2, 	true,  r_A,		2, 	true, false, false,		2, 	55},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_temp, false,	r_temp, false, r_temp, 	3, 	false, false, false,	1, 	38},
		{true,	r_B, 	true,	r_C, 	true,  r_A,		1, 	true, false, false,		2, 	55},
		{true,	r_B, 	false,	r_IR2, 	true,  r_A,		1, 	true, false, false,		2, 	55},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_temp, false,	r_temp, false, r_temp, 	3, 	false, false, false,	0, 	55},
		{false, r_temp, false,	r_temp, false, r_temp, 	3, 	false, false, false,	1, 	47},
		{false, r_IR2, 	false,	r_A, 	false, r_PC, 	3, 	false, false, false,	2, 	0},
		{false, r_IR2, 	true,	r_A, 	false, r_PC, 	0, 	false, false, false,	2, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{false, r_A, 	false,	r_A, 	false, r_A, 	0, 	false, false, false,	3, 	0},
		{true,	r_A, 	false,	r_A, 	false, r_temp, 	3, 	false, false, false,	3, 	0},
		{true,	r_B, 	false,	r_A, 	true,  r_A, 	3, 	false, false, false,	3, 	0},
		{false, r_temp, false,	r_A, 	true,  r_B, 	3, 	false, false, false,	2, 	55},
		{false, r_PC, 	false,	r_A, 	false, r_PC, 	1, 	false, false, false,	2, 	0}
	};

	

	processor p(microprogram, RAM);

	int action, temp;
	bool HALT = false; // ������� ��������� 

	while (!HALT) // �������� ���� ������ ���������
	{
	/*
		�������� ��������:
		-1.	(exit)					����� �� ���������			
		 0.	(help)					������� ������ ��������� ���������
		 1.	(step)					������� ���� ���
		 2.	(nsteps)				������� �������� ���-�� �����
		 3.	(print proc state)		����������� ��������� ���������� (��������, ������� ����� ������������, �.�.)
		 4.	(print memory state)	����������� ��������� ������
		 5.	(step and print)		������� ��� � ����������� ��������� ����������
		 6.	(print cell)			����������� �������� ������ ������
		 7. (edit register)			�������� ������� � �������� �������
		 8. (edit memory)			�������� ������ ������ � �������� �������

		��������� ���� � �������:
		- ��������� ��������� ������ �� �����
	*/
		action = getNumber("\nEnter the action: ", -1, 8);
		
		switch (action)
		{
			case -1:
				HALT = true;
				break;

			case 0:
				printf("========================\n");
				printf("-1 - exit\n");
				printf(" 0 - help\n");
				printf(" 1 - step\n");
				printf(" 2 - nsteps\n");
				printf(" 3 - print_proc_state\n");
				printf(" 4 - print_memory_state\n");
				printf(" 5 - step and print\n");
				printf(" 6 - print cell\n");
				printf(" 7 - edit register\n");
				printf(" 8 - edit memory\n");
				printf("========================\n");
				break;

			case 1:
				p.step();
				break;

			case 2:
				printf("Enter number of steps: ");
				scanf("%d", &temp);
				for (int i = 0; i < temp; i++)
					p.step();
				break;

			case 3:
				p.print_state();
				break;

			case 4:
				printf("========================\n");
				for (int i = 0; i < 256; i++) // ��������, ����� ��� ������������� � �������� ����, �� �����
					printf("%x\n", RAM[i]);
				printf("========================\n");
				break;

			case 5:
				p.step();
				p.print_state();
				break;

			case 6:
				printf("Enter address of memory cell: ");
				scanf("%d", &temp);
				printf("HEX: %x\n", RAM[temp]);
				printf("DEC: %d\n", RAM[temp]);
				break;

			case 7:
				temp = getNumber("Register � ", 0, 7);
				printf("\nPrevious content of register: %d\n", p.getReg(temp));
				p.setReg(temp, (char)getNumber("Enter new value: ", 0, 255));
				break;

			case 8:
				temp = getNumber("Enter address: ", 0, 255);
				printf("\nPrevious content of memory cell: %d\n", RAM[temp]);
				RAM[temp] = getNumber("Enter new value: ", 0, 255);
				break;
		}
	}
	return 0;
}


