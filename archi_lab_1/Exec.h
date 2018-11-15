#pragma once
#ifndef EXEC_H
#define EXEC_H

void ExecFlow(int *procimg, Instruction *inst, char *exeStr);
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

#endif
