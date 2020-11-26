#include <iostream>
#include <array>
#include "core.h"
#include "tests.h"

using namespace std;

int main(int argv, char* argc[])
{
	char filenameInstr[] = "./imem.dat";
	char filenameData[] = "./dmem.dat";

	byte gpr = NREG;
	byte idr = NREG;
	SMP_word data_size = DMSIZE;
	SMP_word instr_size = IMSIZE;
	SMP_word entry = 0;
	core MasterCore(entry, instr_size, data_size, filenameInstr, filenameData);
	while (true)
	{
		MasterCore.test_start(static_cast<uint64_t>(SADD_TEST_INSTR_0));
		MasterCore.test_start(static_cast<uint64_t>(SADD_TEST_INSTR_1));
		MasterCore.test_start(static_cast<uint64_t>(SADD_TEST_INSTR_2));
		MasterCore.test_start(static_cast<uint64_t>(SADD_TEST_INSTR_3));
		MasterCore.test_start(static_cast<uint64_t>(BSWP_TEST_INSTR_4));
		MasterCore.test_start(static_cast<uint64_t>(RRX_TEST_INSTR_5));
		MasterCore.test_start(static_cast<uint64_t>(VSADDH_TEST_INSTR_8));
		if (true)
			break;
	}
	return 0;
}