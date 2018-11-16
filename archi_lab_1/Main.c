#include "Auxiliary.h"
#include "Exec.h"

int main(int argc, char *argv[]) {
    bool failed = false;
    String memFilePath, traceFilePath, sramFilePath;
    char exeStr[512];
    int procImage[9] = { 0 }; // procimage[0-7] are regs 0-7. procimage[8]=pc reg
    Instruction inst;

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

    failed=ExecFlow(procImage, &inst, exeStr,traceFilePath); // this functions starts the program execution: execute the commands and print trace.
    if (failed == true) {
        return failed;
    }
    failed = SramMemDump(sramFilePath);
    return failed;
}