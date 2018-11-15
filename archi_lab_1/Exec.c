
#include "Exec.h"
#include "Auxiliary.h"

void ExecFlow(int *procimg, Instruction *inst, char *exeStr)
{
		
	int halt = 0, inst_num=0;
	while (!halt)
	{
		MemToInst(Mem[*(procimg +8)], inst); // update instruction field
		// print trace func - david
		ExecuteCmd(procimg, inst, exeStr, &inst_num, &halt);
		inst_num++; // instruction number increment
		//print exeStr - david
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

void ExecuteCmd(int *procimg, Instruction *cmd, char *exeStr, int *inst_num, int *halt) // need to code the pc increment and the inst_num increment.
{
	// Arithmetic funcs opcodes
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
	if (cmd->opcode == LHI)
	{
		XorFunc(procimg, cmd, exeStr);
		return;
	}
	// Load/Store funcs opcode
	if (cmd->opcode == LD)
	{
		LdFunc(procimg, cmd, exeStr);
		return;
	}
	if (cmd->opcode == ST)
	{
		StFunc(procimg, cmd, exeStr);
		return;
	}
	//Flow control funcs opcode
	if (cmd->opcode == JLT)
	{
		JltFunc(procimg, cmd, exeStr);
		return;
	}
	if (cmd->opcode == JLE)
	{
		JleFunc(procimg, cmd, exeStr);
		return;
	}
	if (cmd->opcode == JEQ)
	{
		JeqFunc(procimg, cmd, exeStr);
		return;
	}
	if (cmd->opcode == JNE)
	{
		JneFunc(procimg, cmd, exeStr);
		return;
	}
	if (cmd->opcode == JIN)
	{
		JinFunc(procimg, cmd, exeStr);
		return;
	}
	//HALT
	if (cmd->opcode == HLT)
	{
		HltFunc(procimg, cmd, exeStr);
		*halt = 1;
		return;
	}



}

// Arithmetic funcs
void AddFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->dst == 0 || cmd->dst == 1)
	{
		cmd->dst = 2; // changed to R2 to fix wrong command. cant write to R0 or R1.
		cmd->instruction = cmd->instruction & 0xFE3FFFFF; // make dst bits zero
		cmd->instruction = cmd->instruction + 0x00800000; // make bits 22-24 (dst field) to be R2 reg.
	}		
		if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = cmd->immediate + *(procimg + cmd->src0);
		sprintf(exeSrt, "EXEC: R[%d] = %d + %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate + cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d + %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate + *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d + %d", cmd->dst, cmd->src1, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) + *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d + %d", cmd->dst, cmd->src0, cmd->src1);
	}
	*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
}

void SubFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->dst == 0 || cmd->dst == 1)
	{
		cmd->dst = 2; // changed to R2 to fix wrong command. cant write to R0 or R1.
		cmd->instruction = cmd->instruction & 0xFE3FFFFF; // make dst bits zero
		cmd->instruction = cmd->instruction + 0x00800000; // make bits 22-24 (dst field) to be R2 reg.
	}
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) - cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d - %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate - cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d - %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate - *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d - %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) - *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d - %d", cmd->dst, cmd->src0, cmd->src1);
	}
	*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
}

void LsfFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->dst == 0 || cmd->dst == 1)
	{
		cmd->dst = 2; // changed to R2 to fix wrong command. cant write to R0 or R1.
		cmd->instruction = cmd->instruction & 0xFE3FFFFF; // make dst bits zero
		cmd->instruction = cmd->instruction + 0x00800000; // make bits 22-24 (dst field) to be R2 reg.
	}
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) << cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d << %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate << cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d << %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate << *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d << %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) << *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d << %d", cmd->dst, cmd->src0, cmd->src1);
	}
	*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
}

void RsfFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->dst == 0 || cmd->dst == 1)
	{
		cmd->dst = 2; // changed to R2 to fix wrong command. cant write to R0 or R1.
		cmd->instruction = cmd->instruction & 0xFE3FFFFF; // make dst bits zero
		cmd->instruction = cmd->instruction + 0x00800000; // make bits 22-24 (dst field) to be R2 reg.
	}
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) >> cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d >> %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate >> cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d >> %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate >> *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d >> %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) >> *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d >> %d", cmd->dst, cmd->src0, cmd->src1);
	}
	*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
}

void AndFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->dst == 0 || cmd->dst == 1)
	{
		cmd->dst = 2; // changed to R2 to fix wrong command. cant write to R0 or R1.
		cmd->instruction = cmd->instruction & 0xFE3FFFFF; // make dst bits zero
		cmd->instruction = cmd->instruction + 0x00800000; // make bits 22-24 (dst field) to be R2 reg.
	}
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) & cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d & %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate & cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d & %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate & *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d & %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) & *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d & %d", cmd->dst, cmd->src0, cmd->src1);
	}
	*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
}

void OrFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->dst == 0 || cmd->dst == 1)
	{
		cmd->dst = 2; // changed to R2 to fix wrong command. cant write to R0 or R1.
		cmd->instruction = cmd->instruction & 0xFE3FFFFF; // make dst bits zero
		cmd->instruction = cmd->instruction + 0x00800000; // make bits 22-24 (dst field) to be R2 reg.
	}
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) | cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d | %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate | cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d | %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate | *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d | %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) | *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d | %d", cmd->dst, cmd->src0, cmd->src1);
	}
	*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
}

void XorFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	if (cmd->dst == 0 || cmd->dst == 1)
	{
		cmd->dst = 2; // changed to R2 to fix wrong command. cant write to R0 or R1.
		cmd->instruction = cmd->instruction & 0xFE3FFFFF; // make dst bits zero
		cmd->instruction = cmd->instruction + 0x00800000; // make bits 22-24 (dst field) to be R2 reg.
	}
	if (cmd->src1 == 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) ^ cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d ^ %d", cmd->dst, cmd->src0, cmd->immediate);
	}
	if (cmd->src1 == 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate ^ cmd->immediate;
		sprintf(exeSrt, "EXEC: R[%d] = %d ^ %d", cmd->dst, cmd->immediate, cmd->immediate);
	}
	if (cmd->src1 != 1 && cmd->src0 == 1)
	{
		*(procimg + cmd->dst) = cmd->immediate ^ *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d ^ %d", cmd->dst, cmd->immediate, cmd->src1);
	}
	if (cmd->src1 != 1 && cmd->src0 != 1)
	{
		*(procimg + cmd->dst) = *(procimg + cmd->src0) ^ *(procimg + cmd->src1);
		sprintf(exeSrt, "EXEC: R[%d] = %d ^ %d", cmd->dst, cmd->src0, cmd->src1);
	}
	*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
}

void LhiFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	int tmp;
	if (cmd->dst == 0 || cmd->dst == 1)
	{
		cmd->dst = 2; // changed to R2 to fix wrong command. cant write to R0 or R1.
		cmd->instruction = cmd->instruction & 0xFE3FFFFF; // make dst bits zero
		cmd->instruction = cmd->instruction + 0x00800000; // make bits 22-24 (dst field) to be R2 reg.
	}
	tmp = cmd->immediate;
	tmp = tmp << 16; 
	*(procimg + cmd->dst) = *(procimg + cmd->dst) & 0x0000FFFF; //make bits 31-16 zero.
	*(procimg + cmd->dst) = *(procimg + cmd->dst) + tmp; // add the tmp bits (immediate bits) to bits 31-16
	sprintf(exeSrt, "EXEC: Loaded R[%d] high bits with the immediate bits", cmd->dst);
	*(procimg + 8) = *(procimg + 8) + 1; // PC + 1

}

// Load Store funcs
void LdFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	int mem_addr;
	if (cmd->dst == 0 || cmd->dst == 1)
	{
		cmd->dst = 2; // changed to R2 to fix wrong command. cant write to R0 or R1.
		cmd->instruction = cmd->instruction & 0xFE3FFFFF; // make dst bits zero
		cmd->instruction = cmd->instruction + 0x00800000; // make bits 22-24 (dst field) to be R2 reg.
	}
	mem_addr = *(procimg + cmd->src1);
	mem_addr = mem_addr & 0x0000FFFF; // take only first 16 bits because memory size is 2^16.
	*(procimg + cmd->dst) = Mem[mem_addr]; //make bits 31-16 zero.

	sprintf(exeSrt, "EXEC: Loaded to R[%d] the data from Mem[%d]", cmd->dst, mem_addr);
	*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
}

void StFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	int mem_addr;
	mem_addr = *(procimg + cmd->src1);
	mem_addr = mem_addr & 0x0000FFFF; // take only first 16 bits because memory size is 2^16.
	Mem[mem_addr] = *(procimg + cmd->src0);

	sprintf(exeSrt, "EXEC: Stored R[%d] to memory at address %d",cmd->src0,mem_addr);
	*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
}

// Flow control funcs
void JltFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	int jump_taken = 0;
	if (*(procimg + cmd->src0) < *(procimg + cmd->src1))
	{
		jump_taken = 1;
		*(procimg + 7) = *(procimg + 8);
		*(procimg + 8) = cmd->immediate;
	}
	sprintf(exeSrt, "EXEC: Jump to %d if %d < %d",cmd->immediate, cmd->src0, cmd->src1);
	if (!jump_taken)
	{
		*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
	}
}

void JleFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	int jump_taken = 0;
	if (*(procimg + cmd->src0) <= *(procimg + cmd->src1))
	{
		jump_taken = 1;
		*(procimg + 7) = *(procimg + 8);
		*(procimg + 8) = cmd->immediate;
	}
	sprintf(exeSrt, "EXEC: Jump to %d if %d <= %d", cmd->immediate, cmd->src0, cmd->src1);
	if (!jump_taken)
	{
		*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
	}
}

void JeqFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	int jump_taken = 0;
	if (*(procimg + cmd->src0) == *(procimg + cmd->src1))
	{
		jump_taken = 1;
		*(procimg + 7) = *(procimg + 8);
		*(procimg + 8) = cmd->immediate;
	}
	sprintf(exeSrt, "EXEC: Jump to %d if %d == %d", cmd->immediate, cmd->src0, cmd->src1);
	if (!jump_taken)
	{
		*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
	}
}

void JneFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	int jump_taken = 0;
	if (*(procimg + cmd->src0) != *(procimg + cmd->src1))
	{
		jump_taken = 1;
		*(procimg + 7) = *(procimg + 8);
		*(procimg + 8) = cmd->immediate;
	}
	sprintf(exeSrt, "EXEC: Jump to %d if %d != %d", cmd->immediate, cmd->src0, cmd->src1);
	if (!jump_taken)
	{
		*(procimg + 8) = *(procimg + 8) + 1; // PC + 1
	}
}

void JinFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	int tmp;
	tmp = *(procimg + cmd->src0);
	tmp = tmp & 0x0000FFFF; // take only first 16 bits to be used as address
	*(procimg + 7) = *(procimg + 8); // r7 saves current pc
	*(procimg + 8) = tmp; // pc = 16 first bits of src0
	sprintf(exeSrt, "EXEC: Jumped to address %d in memory", tmp);
}
//HALT
void HltFunc(int *procimg, Instruction *cmd, char *exeSrt)
{
	sprintf(exeSrt, "EXEC: Halting");
}