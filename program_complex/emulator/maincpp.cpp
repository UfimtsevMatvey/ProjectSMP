#include <iostream>
#include <array>
#include "headers/core.h"
#include "headers/tests.h"
#include "headers/testClass.h"
#include "headers/checkArh.h"
#include "headers/core_Mode.h"
#include "headers/cmd_line.h"

int main(int argv, char* argc[])
{
	const char* filenameInstr;
	const char* filenameData;
	char cmode;
	int mode;
	int ni;
	if(checkArh()){
		std::cout << "Your CPU is not supported." << std::endl;
		std::cout << "Your CPU should be support AVX2 instruction set." << std::endl;
		std::cout << "Program is ended with return code: 1." << std::endl;
		return 1;
	}
	if(cmd_line(argv, argc, &filenameInstr, &filenameData, &cmode, &ni))
		return 0;
	std::cout << cmode << std::endl;
	switch(cmode){
		case 'r': mode = STDMODE;	break;
		case 'd': mode = DEBUGMODE;	break;
		case 's': mode = STEPMODE;	break;
		default: 
			std::cout << "Unknown mode: " << cmode << std::endl;
            std::cout << "Use -r"" mode for standart emulating" << std::endl;//run
            std::cout << "Use -d mode for debug print emulating" << std::endl;//debug
            std::cout << "Use -s mode for step by step emulating" << std::endl;//step by step
			mode = STDMODE;
			return 0;
	}
	SMP_word data_size = DMSIZE;
	SMP_word instr_size = IMSIZE;
	SMP_word entry = 0;
	
	core master_core(entry, instr_size, data_size, filenameInstr, filenameData);
	master_core.start(ni, mode);

	return 0;
}