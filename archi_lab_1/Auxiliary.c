#include "Auxiliary.h"

bool MemoryParsing(String memFilePath){
	/* input: mem file path
	   output: indicator for success
	   this function parse the memory file to an array
	*/
	int memIndex = 0;
	long int hexNum;
	bool failed = false;
	FILE *memFile = fopen(memFilePath, "r");


	if (memFile != NULL){
		char line[128]; /* or other suitable maximum line size */
		while (fgets(line, sizeof line, memFile) != NULL) /* read a line */{
			if (memIndex == MEMORY_SIZE){
				break;
			}
			sscanf(line, "%x", &hexNum);
			Mem[memIndex] = hexNum;
			memIndex++;
		}
		fclose(memFile);
	}
	else {
		fprintf("couldnt open file < %s >\n", memFilePath);
		failed = true;
	}
	return failed;
}
/*
ProcImag InitProcImage() {
	// input: Nan
	//   output: initiated ProcImag struct
	 //  this function initiant the proccessor image
	
	ProcImag img;

	img.pc = 0;
	img.r0 = 0;
	img.r1 = 0;
	img.r2 = 0;
	img.r3 = 0;
	img.r4 = 0;
	img.r5 = 0;
	img.r6 = 0;
	img.r7 = 0;

	return img;
}
*/

String GetOpName(OpCode opcode){
	/* input: OpCode enumarate
	   output: OpCode string
	   this function return the opcode represnted by an enum as a string
	*/
	switch (opcode){
	case ADD:
		return "ADD";
	case SUB:
		return "SUB";
	case LSF:
		return "LSF";
	case RSF:
		return "RSF";
	case AND:
		return "AND";
	case OR:
		return "OR";
	case XOR:
		return "XOR";
	case LHI:
		return "LHI";
	case LD:
		return "LD";
	case ST:
		return "ST";
	case JLT:
		return  "JLT";
	case JLE:
		return "JLE";
	case JEQ:
		return "JEQ";
	case JNE:
		return "JNE";
	case JIN:
		return "JIN";
	case HLT:
		return "HLT";
	default:
		break;
	}
}

bool TracePrint(String traceFilePath, Instruction* preformedInst, ProcImag* proccesImage, String exeStr, int instCount) {
	/* input:
	   output:
	   this function prints the trace for each instruction
	*/
	FILE * traceFile;
	bool failed=false;

	traceFile = fopen(traceFilePath, "a");
	if (traceFile != NULL) {
		fprintf(traceFile, "--- instruction %d (%04x) @ PC %d (%04x) -----------------------------------------------------------\n",
			instCount, instCount, proccesImage->pc, proccesImage->pc);
		fprintf(traceFile, "pc = %04x, inst = %08x, opcode = %d (%s), dst = %d, src0 = %d, src1 = %d, immediate = %08x\n",
			proccesImage->pc, preformedInst->instruction, preformedInst->opcode, GetOpName(preformedInst->opcode), preformedInst->dst, preformedInst->src0,
			preformedInst->src1, preformedInst->immediate);
		fprintf(traceFile, "r[0] = %08x r[1] = %08x r[2] = %08x r[3] = %08x\n",
			proccesImage->r0, proccesImage->r1, proccesImage->r2, proccesImage->r3);
		fprintf(traceFile, "r[4] = %08x r[5] = %08x r[6] = %08x r[7] = %08x\n\n",
			proccesImage->r4, proccesImage->r5, proccesImage->r6, proccesImage->r7);
		fprintf(traceFile, exeStr);
		fclose(traceFile);
	}
	else{
		fprintf("couldnt open file < %s >\n", traceFilePath);
		failed = true;
	}
	return failed;
}

bool SramMemDump(String sramFilePath) {
	/* input: Sram file path
	   output: indicator of success
	   this function export the memory to file
	*/
	bool failed = false;
	FILE *sramFile;
	int i;

	sramFile = fopen(sramFilePath, "w");
	if (sramFile != NULL) {
		for (i = 0; i < MEMORY_SIZE; i++)
			fprintf(sramFile, "%08x\n", Mem[i]);
		fclose(sramFile);
	}
	else {
		fprintf("couldnt open file < %s >\n", sramFilePath);
		failed = true;
	}
	return failed;
}