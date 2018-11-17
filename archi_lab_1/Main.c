#include "Auxiliary.h"
#include "Exec.h"

int main(int argc, char *argv[]) {
    bool failed = false;
    String memFilePath, traceFilePath, sramFilePath;
    char exeStr[512];
    int procImage[9] = { 0 }; // procimage[0-7] are regs 0-7. procimage[8]=pc
    Instruction inst;
    FILE *fp;

    if (argc < 2) {
        failed = true;
        printf("ISS error: the input arguments are incorrect\n");
        printf("invoke the program as follow: <exe> <memFilePath.bin>\n");
        return failed;
    }
    memFilePath = argv[1];
    /*Init memory*/
    failed = MemoryParsing(memFilePath);
    if (failed == true) {
        return failed;
    }
    traceFilePath = (char*)malloc(sizeof("trace.txt"));
    sramFilePath = (char*)malloc(sizeof("sram_out.txt"));
    if (traceFilePath == NULL || sramFilePath == NULL) {
        failed = true;
        printf("Error occured, exiting\n");
        return failed;
    }
    strncpy(traceFilePath, "trace.txt",10);
    strncpy(sramFilePath, "sram_out.txt",13);
    /*Resetting the files in case they are already exist*/
    fp = fopen(traceFilePath, "w");
    if (fp==NULL){
        fprintf("couldnt open file < %s >\n", traceFilePath);
        failed = true;
        return failed;
    }
    fclose(fp);
    fp = fopen(sramFilePath, "w");
    if (fp==NULL){
        fprintf("couldnt open file < %s >\n", sramFilePath);
        failed = true;
        return failed;
    }
    fclose(fp);
    /*this function starts the program execution: execute the commands and print trace.*/
    failed=ExecFlow(procImage, &inst, exeStr,traceFilePath);
    if (failed == true) {
        return failed;
    }
    /*Memory output*/
    failed = SramMemDump(sramFilePath);
    return failed;
}