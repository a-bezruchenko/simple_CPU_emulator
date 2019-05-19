#include <iostream>
#include "string.h"

#include "math.h"

enum reg
{
	r_A, r_B, r_C, r_D, r_PC, r_IR1, r_IR2, r_temp
};

struct microcom
{
	bool AMX;
	reg A;
	bool BMX;
	reg B;
	bool CMX;
	reg C;
	int ALU_CODE;
	bool WF;
	bool MEMR;
	bool MEMW;
	int SFA;
	int JA;
};

class processor
{
public:
	processor(microcom *program, char *memory);
	void step();
	void print_state();
	char getReg(unsigned int reg);
	void setReg(unsigned int reg, char value);
private:
	char registers[8];
	bool E;
	microcom *microprogram; // микропрограмма
	char *RAM;				// не является частью процессора, но нужно связать его с внешней памятью

	microcom cur_com;		// текущая микрокоманда
	int cur_mc_adr;			// адрес текущей микрокоманды
};