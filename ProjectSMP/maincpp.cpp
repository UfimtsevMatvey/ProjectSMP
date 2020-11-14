#include <iostream>
#include <array>
#include "core.h"
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

	//������������� ����
	core MasterCore(entry, instr_size, data_size, filenameInstr, filenameData);

	
	/*
	����� ����� ���������� ����� ������ ����.

	���� ������� � ���, ����� ������������ ������� ����, 
	� ������� ����� ����������� ���������� ��������� ����������, � �� ����������.
	��� ��� �������� � �������������� � �����������, ������ ���� � ������ "Core".

	������� ������ ������, ������� �� ��������� � ����.
	*/
	while (true)
	{
		MasterCore.test_start();
		if (true)
			break;
	}
	return 0;
}