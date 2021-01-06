#include <iostream>
#include <array>
#include "core.h"
#include "tests.h"
#include "testClass.h"
#include "checkArh.h"


using namespace std;

int main(int argv, char* argc[])
{
	if(checkArh() == 0){
		cout << "CPU is not avalible" << endl;
		return 1;
	}
	char filenameInstr[] = "./imem.dat";
	char filenameData[] = "./dmem.dat";

	byte gpr = NREG;
	byte idr = NREG;
	SMP_word data_size = DMSIZE;
	SMP_word instr_size = IMSIZE;
	SMP_word entry = 0;
	
	core MasterCore(entry, instr_size, data_size, filenameInstr, filenameData);
	debugger CoreDebug;
	CoreDebug.v = 0;
	while (true)
	{
		MasterCore.test_start(static_cast<uint64_t>(SADD_TEST_INSTR_0));
		CoreDebug.debugMode(MasterCore);
		MasterCore.test_start(static_cast<uint64_t>(SADD_TEST_INSTR_1));
		CoreDebug.debugMode(MasterCore);
		MasterCore.test_start(static_cast<uint64_t>(SADD_TEST_INSTR_2));
		CoreDebug.debugMode(MasterCore);
		MasterCore.test_start(static_cast<uint64_t>(SADD_TEST_INSTR_3));
		CoreDebug.debugMode(MasterCore);
		MasterCore.test_start(static_cast<uint64_t>(BSWP_TEST_INSTR_4));
		CoreDebug.debugMode(MasterCore);
		MasterCore.test_start(static_cast<uint64_t>(RRX_TEST_INSTR_5));
		CoreDebug.debugMode(MasterCore);
		MasterCore.test_start(static_cast<uint64_t>(VSADDH_TEST_INSTR_8));
		CoreDebug.debugMode(MasterCore);
		if (true)
			break;
	}
	return 0;
}