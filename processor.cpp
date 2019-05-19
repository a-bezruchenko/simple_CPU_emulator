#include "processor.h"

processor::processor(microcom *program, char *memory)
{
	microprogram = program;
	RAM = memory;

	E = false;
	cur_mc_adr = 0;
	for (int i = 0; i < 8; i++)
		registers[i] = 0;
}

char processor::getReg(unsigned int reg)
{
	if (reg<0 || reg>8) 
		throw 1;
	else
		return registers[reg];
}

void processor::setReg(unsigned int reg, char value)
{
	if (reg<0 || reg>8)
		throw 2;
	else
		registers[reg] = value;
}

void processor::step()
{
	///// РАБОТА УУ
	/// ПЗУ
	cur_com = microprogram[cur_mc_adr]; // считываем очередную микрокоманду

	/// СФА
	if (cur_com.SFA == 3||	// NEXT
		(cur_com.SFA == 0 && E==true)||	// JNE
		(cur_com.SFA == 1 && (registers[(int)r_IR1]&0x10)==0)) // JI
		cur_mc_adr++;
	else if (cur_com.SFA == 2 || // JMP
		(cur_com.SFA == 0 && E==false) || // JNE
		(cur_com.SFA == 1 && (registers[(int)r_IR1]&0x10)!=0)) // JI
		cur_mc_adr = cur_com.JA;	
	else if (cur_com.SFA == 4)	// DECODE
		cur_mc_adr = ((registers[(int)r_IR1]&0xE0)>>2)|4; // обнуляем младшие 5 бит, сдвигаем на 2, ставим младшие 3 бита = 100
	else
	{
		// обработка ошибки 
	}

	/// блоки формирования операндов
	reg A_num, B_num, C_num; 
	reg op[3];
	op[0] = (reg) (registers[(int)r_IR1]&0x0C>>2);
	op[1] = (reg) (registers[(int)r_IR1]&0x03);
	op[2] = (reg) (registers[(int)r_IR2]>>6);

	// да, по-хорошему надо бы выделить это в отдельную функцию, но мне лень
	if (!cur_com.AMX)
		A_num = cur_com.A;
	else
		A_num = op[(int)cur_com.A];

	if (!cur_com.BMX)
		B_num = cur_com.B;
	else
		B_num = op[(int)cur_com.B];


	if (!cur_com.CMX)
		C_num = cur_com.C;
	else
		C_num = op[(int)cur_com.C];

	char *A, *B, *C; // указатели на нужные регистры
	A = registers + (int)A_num;
	B = registers + (int)B_num;
	C = registers + (int)C_num;

	///// РАБОТА ОУ
	/// блок выбора результата 
	bool isAdr =	(((int)A_num&4)&&(!((int)A_num&2) || !((int)A_num&1))) ||
					(((int)B_num&4)&&(!((int)B_num&2) || !((int)B_num&1))) ||
					(((int)C_num&4)&&(!((int)C_num&2) || !((int)C_num&1)));
	
	// АЛУ
	char temp_alu;
	switch (cur_com.ALU_CODE)
	{ 
	case 0: // ADD и в адресном, и в общем
		temp_alu = *A + *B;
		break;
	case 1: // INC в адресном, NOR в общем
		if (isAdr)
			temp_alu = *C+1;
		else
			temp_alu = ~(*A | *B);
		break;
	case 2: // SHLA в адресном, SHRA в общем
		if (isAdr)
			temp_alu = *A * pow((float)2, *B);
		else
			temp_alu = *A / pow((float)2, *B);
		break;
	case 3: // NOP и в адресном, и в общем
		temp_alu = *A;
		break;
	default:
		;// сообщение об ошибке
		break;
	}
	
	// блок формирования флага
	if (cur_com.WF)
		E = (*A == *B);

	// мульиплексор для выбора между АЛУ и памятью
	*C = cur_com.MEMR ? RAM[*B] : temp_alu;

	// не относится к ОУ; запись в память
	if (cur_com.MEMW)
		RAM[*B] = *A;
}

void processor::print_state()
{
	printf("========================\n");
	printf("Registers::\n");
	char names[8][5] = {"A", "B", "C", "D", "PC", "IR1", "IR2", "temp"};
	for (int i = 0; i<8; i++)
		printf("%s: %d\n", names[i], registers[i]);

	printf("E: %d\n", E);
	printf("Current instruction: %d\n", cur_mc_adr);
	printf("========================\n");
}

