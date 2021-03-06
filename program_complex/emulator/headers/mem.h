#pragma once

#include <fstream>

#ifndef def
   #include "def.h"
#endif

#define BUFFERSIZE 1024
#define INVALID 0xFFFFFFFFFFFFFFFF
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
	bool valid;
	SMP_word Nbuffer;
	SMP_word memSize;
	SMP_word* memory;
};