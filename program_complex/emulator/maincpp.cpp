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
	char mode_code;
	int mode;
	int ni;
	if(cmd_line(argv, argc, &filenameInstr, &filenameData, &cmode, &mode_code, &ni))
		return 0;
	std::cout << cmode << std::endl;
	std::cout << mode_code << std::endl;


	switch (mode_code)
	{
	case 'h':
		std::cout << "Use -r"" mode for standart emulating" << std::endl;//run
        std::cout << "Use -d mode for debug print emulating" << std::endl;//debug
        std::cout << "Use -s mode for step by step emulating" << std::endl;//step by step
		std::cout << "Use -a for ignore check AVX2" << std::endl;
		std::cout << "Use -h for print this message" << std::endl;
		break;
	case 'a':
		std::cout << "Check AVX2 instaraction set ignore" << std::endl;
		break;
	default:
		break;
	}
	if(checkArh() && mode_code != 'a'){
		std::cout << "Your CPU is not supported." << std::endl;
		std::cout << "Your CPU should be support AVX2 instruction set." << std::endl;
		std::cout << "Program is ended with return code: 1." << std::endl;
		return 1;
	}
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
			//return 0;
			break;
	}
	SMP_word data_size = DMSIZE;
	SMP_word instr_size = IMSIZE;
	SMP_word entry = 0;
	//init core
	core master_core(entry, instr_size, data_size, filenameInstr, filenameData);
	//start core emulating
	if(master_core.start(ni, mode)) return 1;
	return 0;
}