#include <iostream>
#include <array>
#include "core.h"
using namespace std;

int main(int argv, char* argc[])
{
	char filenameInstr[] = "C:\\Users\\Matvey\\source\\repos\\ProjectSMP\\x64\\Debug\\imem.dat";
	char filenameData[] = "C:\\Users\\Matvey\\source\\repos\\ProjectSMP\\x64\\Debug\\dmem.dat";

	byte gpr = NREG;
	byte idr = NREG;
	SMP_word data_size = DMSIZE;
	SMP_word instr_size = IMSIZE;
	SMP_word entry = 0;

	//Иницаализация ядра
	core MasterCore(entry, instr_size, data_size, filenameInstr, filenameData);

	
	/*
	Нужно иметь отладочный режим работы ядра.

	Идея состоит в том, чтобы организовать главный цикл, 
	в котором будет происходить считывание очередной инструкции, и ее исполнение.
	Все что связанно с декодированием и исполнением, должно быть в классе "Core".

	Объекты класса Память, внешние по отношению к Ядру.
	*/
	while (true)
	{
		MasterCore.start();
		if (true)
			break;
	}
	return EXIT_SUCCESS;
}