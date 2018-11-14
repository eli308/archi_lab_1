
#include "Auxiliary.h"

int main(int argc, char *argv[]) {
	bool failed = false;
	String memFilePath, traceFilePath, sramFilePath;
	char exeStr[512];
	int procImage[9] = { 0 }; // procimage[0-7] are regs 0-7. procimage[8]=pc reg
	int inst_num = 0;
	Instruction inst;

	if (argc < 2) {
		failed = true;
		printf("ISS error: the input arguments are incorrect\n");
		printf("ivoke the program as follow: exe <memFilePath.bin>\n");
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
	
	//procImage=InitProcImage();  changed procimag to an array of int.

	//failed = SimulatorHandler();



	failed = SramMemDump(sramFilePath);
	return failed;
}