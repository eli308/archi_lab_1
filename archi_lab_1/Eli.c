
#include "Eli.h"
#include "Auxiliary.h"

void parser(int *procimg, Instruction *inst, char *exeStr)
{
	int halt = 0, inst_num=0;
	while (1)
	{
		MemToInst(Mem[inst_num], inst); // update instruction field
		if (inst->opcode == HLT)
			break;
		ExecuteCmd(procimg, inst, exeStr, &inst_num);

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

void ExecuteCmd(int *procimg, Instruction *cmd, char *exeStr, int *inst_num) // need to code the pc increment and the inst_num increment.
{
	if (cmd->opcode == ADD)
	{
		AddFunc(procimg, cmd, exeStr);
		return;
	}
	if (cmd->opcode == SUB)
	{
		SubFunc(procimg, cmd, exeStr);
		return;
	}
	if (cmd->opcode == LSF)
	{
		LsfFunc(procimg, cmd, exeStr);
		return;
	}
	if (cmd->opcode == RSF)
	{
		RsfFunc(procimg, cmd, exeStr);
		return;
	}
	if (cmd->opcode == AND)
	{
		AndFunc(procimg, cmd, exeStr);
		return;
	}
	if (cmd->opcode == OR)
	{
		OrFunc(procimg, cmd, exeStr);
		return;
	}
	if (cmd->opcode == XOR)
	{
		XorFunc(procimg, cmd, exeStr);
		return;
	}


}

// exe funcs
void AddFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = cmd->immediate + *(procimg + cmd->src0);
		strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate + cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate + *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd->dst, cmd->src1, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) + *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d + %d", cmd->dst, cmd->src0, cmd->src1);
	}
}

void SubFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) - cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d - %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate - cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d - %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate - *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d - %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) - *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d - %d", cmd->dst, cmd->src0, cmd->src1);
	}
}

void LsfFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) << cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d << %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate << cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d << %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate << *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d << %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) << *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d << %d", cmd->dst, cmd->src0, cmd->src1);
	}
}

void RsfFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) >> cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d >> %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate >> cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d >> %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate >> *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d >> %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) >> *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d >> %d", cmd->dst, cmd->src0, cmd->src1);
	}
}

void AndFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) & cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d & %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate & cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d & %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate & *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d & %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) & *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d & %d", cmd->dst, cmd->src0, cmd->src1);
	}
}

void OrFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) | cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d | %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate | cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d | %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate | *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d | %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) | *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d | %d", cmd->dst, cmd->src0, cmd->src1);
	}
}

void OrFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) ^ cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d ^ %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate ^ cmd->immediate;
		strcpy(exeSrt, "EXEC: R[%d] = %d ^ %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate ^ *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d ^ %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) ^ *(procimg + cmd->src1);
		strcpy(exeSrt, "EXEC: R[%d] = %d ^ %d", cmd->dst, cmd->src0, cmd->src1);
	}
}