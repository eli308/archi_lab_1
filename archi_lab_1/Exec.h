//
// Created by David Sriker on 16/11/2018.
//

#ifndef LAB1_ARCHLAB_EXEC_H
#define LAB1_ARCHLAB_EXEC_H

#include "Auxiliary.h"
bool ExecFlow(int *procimg, Instruction *inst, char *exeStr,String traceFilePath);
void MemToInst(int mem, Instruction *inst);
void ExecuteCmd(int *procimg, Instruction *cmd, char *exeStr, int *inst_num, int *halt);

// Arithmetic funcs
void AddFunc(int *procimg, Instruction *cmd, char *exeSrt);
void SubFunc(int *procimg, Instruction *cmd, char *exeSrt);
void LsfFunc(int *procimg, Instruction *cmd, char *exeSrt);
void RsfFunc(int *procimg, Instruction *cmd, char *exeSrt);
void AndFunc(int *procimg, Instruction *cmd, char *exeSrt);
void OrFunc(int *procimg, Instruction *cmd, char *exeSrt);
void XorFunc(int *procimg, Instruction *cmd, char *exeSrt);
void LhiFunc(int *procimg, Instruction *cmd, char *exeSrt);

// Load Store funcs
void LdFunc(int *procimg, Instruction *cmd, char *exeSrt);
void StFunc(int *procimg, Instruction *cmd, char *exeSrt);

// Flow Control funcs
void JltFunc(int *procimg, Instruction *cmd, char *exeSrt);
void JleFunc(int *procimg, Instruction *cmd, char *exeSrt);
void JeqFunc(int *procimg, Instruction *cmd, char *exeSrt);
void JneFunc(int *procimg, Instruction *cmd, char *exeSrt);
void JinFunc(int *procimg, Instruction *cmd, char *exeSrt);

//HALT
void HltFunc(int *procimg, Instruction *cmd, char *exeSrt);


#endif //LAB1_ARCHLAB_EXEC_H
