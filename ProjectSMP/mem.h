#pragma once
#include "def.h"
#include <fstream>
#define BUFFERSIZE 1024
#define INVALID 0xFFFFFFFFFFFFFFFF
//Работа с внешними файлами, только через класс  mem.
class mem
{
public:
	mem();
	~mem();
	void Init(SMP_word size, const char* filename);
	void syncFile();
	void load(SMP_word addr, SMP_word& data);
	void store(SMP_word addr, SMP_word data);

private:
	int bufferSize;
	const char* mFileName;
	std::fstream memFile;

	void buffering(SMP_word bsize, SMP_word entry);
	void saveBuffer(SMP_word bsize, SMP_word entry);
	void openFile();
	void closeFile();
	bool valid;//Если true то данные в файле действтельны
	SMP_word Nbuffer;
	SMP_word memSize;
	SMP_word* memory;
};