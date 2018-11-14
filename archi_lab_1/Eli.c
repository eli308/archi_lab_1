
#include "Eli.h"
#include "Auxiliary.h"

void parser(int *procimg, Instruction *inst, char *exeStr)
{
	int halt = 0, inst_num=0;
	while (1)
	{
		MemToInst(Mem[inst_num], inst); // update instruction field
		if inst

	}
}



void MemToInst(int mem, Instruction *inst)
{
	int tmp = mem;
	// set imm
	inst->immediate = (tmp & 0x0000FFFF);
	// set opcode
	inst->opcode = ((tmp & 0x3E000000) >> 25);
	//set src1
	inst->src1 = ((tmp >> 16) & 0x00000007);
	//set src0
	inst->src0 = ((tmp >> 19) & 0x00000007);
	//set dst
	inst->dst = ((tmp >> 22) & 0x00000007);
	inst->instruction = mem;
}

void ExecuteCmd(int *procimg, Instruction cmd, char *exeSrt)
{
	if (cmd.opcode == ADD)
	{
		if (cmd.src1 == 1 && cmd.src0 != 1)
		{
			*(procimg + cmd.dst) = cmd.immediate + *(procimg + cmd.src0);
			strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd.dst, cmd.src0, cmd.immediate);
		}
		if (cmd.src1 == 1 && cmd.src0 == 1)
		{
			*(procimg + cmd.dst) = cmd.immediate + cmd.immediate;
			strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd.dst, cmd.immediate, cmd.immediate);
		}
		if (cmd.src1 != 1 && cmd.src0 == 1)
		{
			*(procimg + cmd.dst) = cmd.immediate + *(procimg + cmd.src1);
			strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd.dst, cmd.src1, cmd.immediate);
		}
		if (cmd.src1 != 1 && cmd.src0 != 1)
		{
			*(procimg + cmd.dst) = *(procimg + cmd.src0) + *(procimg + cmd.src1);
			strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd.dst, cmd.src0, cmd.src0);
		}
		
	}
}
void AddFunc(int *procimg, Instruction cmd, char *exeSrt)
{
	if (cmd.src1 == 1 && cmd.src0 != 1)
	{
		*(procimg + cmd.dst) = cmd.immediate + *(procimg + cmd.src0);
		strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd.dst, cmd.src0, cmd.immediate);
	}
	if (cmd.src1 == 1 && cmd.src0 == 1)
	{
		*(procimg + cmd.dst) = cmd.immediate + cmd.immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd.dst, cmd.immediate, cmd.immediate);
	}
	if (cmd.src1 != 1 && cmd.src0 == 1)
	{
		*(procimg + cmd.dst) = cmd.immediate + *(procimg + cmd.src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd.dst, cmd.src1, cmd.immediate);
	}
	if (cmd.src1 != 1 && cmd.src0 != 1)
	{
		*(procimg + cmd.dst) = *(procimg + cmd.src0) + *(procimg + cmd.src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd.dst, cmd.src0, cmd.src0);
	}
}