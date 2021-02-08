#include <iostream>
#include <array>
#include "headers/core.h"
#include "headers/tests.h"
#include "headers/testClass.h"
#include "headers/checkArh.h"
#include "headers/core_Mode.h"

using namespace std;

int main(int argv, char* argc[])
{
	const char* filenameInstr;
	const char* filenameData;

	if(checkArh() != 0x20){
		cout << "Your CPU is not supported." << endl;
		cout << "Your CPU should be support AVX2 instruction set." << endl;
		cout << "Program is ended with return code: 1." << endl;
		return 1;
	}

	if(argv == 3){
		filenameInstr = argc[1];
		filenameData = argc[2];
	}
	else if(argv == 2){
		filenameInstr = argc[1];
		filenameData = "./dmem.dat";
	}
	else if(argv == 1){
		filenameInstr = "../test_gen/test.smpasm.bin";
		filenameData = "./dmem.dat";
	}
//	byte gpr = NREG;
//	byte idr = NREG;
	SMP_word data_size = DMSIZE;
	SMP_word instr_size = IMSIZE;
	SMP_word entry = 0;
	
	core MasterCore(entry, instr_size, data_size, filenameInstr, filenameData);
	MasterCore.start(37, DEBUGMODE);
/*
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
	}*/
	return 0;
}