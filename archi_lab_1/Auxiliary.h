#ifndef AUXILIARY_H_   /* Include guard */
#define AUXILIARY_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MEMORY_SIZE		(65536)




typedef signed short 	Int16;
typedef unsigned int  	Uint32;
typedef unsigned char 	Byte;
typedef char * String;

typedef enum OpCode_t {
	ADD,		// R[dst] = R[src0] +  R[src1]
	SUB,		// R[dst] = R[sec0] -  R[src1] 
	LSF,		// R[dst] = R[sec0] << R[src1]
	RSF,		// R[dst] = R[sec0] >> R[src1]
	AND,		// R[dst] = R[sec0] &  R[src1]
	OR,			// R[dst] = R[sec0] |  R[src1]
	XOR,		// R[dst] = R[sec0] ^  R[src1]
	LHI,		// Load the high bits [31:16] of the dst register with immediate[15:0]

	LD,			// R[dst] = M[R[src1]]
	ST,         // M[R[src1]] = R[src0]

	JLT = 16,   // Jumps to immediate[15:0] if R[src0] < R[src1]
	JLE,		// Jumps to immediate[15:0] if R[src0] <= R[src1]
	JEQ,		// Jumps to immediate[15:0] if R[src0] == R[src1]
	JNE,		// Jumps to immediate[15:0] if R[src0] != R[src1]
	JIN,		// Indirect jump tp address R[src0]

	HLT = 24    // halts the simulator.
} OpCode;

typedef struct  Instruction_t {
	OpCode			opcode;
	int				instruction;
	Byte			dst;
	Byte			src0;
	Byte			src1;
	Int16			immediate;
} Instruction;

/* changed to array
typedef struct ProcImag_t {
	int pc;
	int r0;
	int r1;
	int r2;
	int r3;
	int r4;
	int r5;
	int r6;
	int r7;
}ProcImag;
*/ 


Uint32	   Mem[MEMORY_SIZE];

//ProcImag InitProcImage();   changed procimage to be an array of int.
bool MemoryParsing(String memFilePath);
bool SramMemDump(String sramFilePath);
bool TracePrint(String traceFilePath, Instruction* preformedInst, ProcImag* proccesImage, String exeStr, int instCount);
String GetOpName(OpCode opcode);
#endif