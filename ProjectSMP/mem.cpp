//#pragma once
#include "headers/mem.h"
#include <iostream>
#include <fstream>
#include <string>
#include "headers/def.h"

mem::mem()
{//init memory
}
mem::~mem()
{
	delete memory;
}
void mem::Init(SMP_word size, const char* filename)
{
	//��������� ��������� ������ ��� �������
	Nbuffer = INVALID;
	bufferSize = BUFFERSIZE;
	memSize = size;
	memory = new SMP_word[bufferSize]; //Fucking brakets

	//�������� ����� ��� ������/������
	mFileName = filename;
	//openFile();
}
void mem::openFile()
{
	memFile.open(mFileName, std::ios::binary | std::ios::in | std::ios::out);
}
void mem::closeFile()
{
	memFile.close();
}
void mem::syncFile()
{
	saveBuffer(bufferSize, bufferSize * Nbuffer);
}
void mem::load(SMP_word addr, SMP_word& data)
{
	SMP_word Baddr = addr / bufferSize;

	if (memory == nullptr){//���� ������ ��� �� ����������
		if (memSize > addr){
			Nbuffer = addr / bufferSize;
			buffering(bufferSize, Nbuffer * bufferSize);//�������� � ������ ���� �� �����.
		}
	}
	else{
		if (memSize > addr){
			if (Baddr == Nbuffer) { // ������ �������� ��� � ������
				data = memory[addr - Nbuffer * bufferSize];
			}
			else{//���� ������� �������� � ������ ���, �� ��������� ��������������� ���� �� �����.
				if (valid) {
					Nbuffer = Baddr;
					buffering(bufferSize, Baddr * bufferSize);
					data = memory[addr - Nbuffer * bufferSize];
				}
				else{
					//���������� � ����, �������� ��������� �������
					if (Nbuffer != INVALID) {
						saveBuffer(bufferSize, Nbuffer * bufferSize);
					}
					Nbuffer = Baddr;
					buffering(bufferSize, Baddr * bufferSize);
					data = memory[addr - Nbuffer * bufferSize];
					valid = true;
				}
			}
		}
	}
}
void mem::store(SMP_word addr, SMP_word data)
{
	SMP_word Baddr = addr / bufferSize;
	if (memSize > addr){
		if (Baddr == Nbuffer) {
			memory[addr - Nbuffer * bufferSize] = data;
			valid = false;
		}
		else{
			if (valid) {
				buffering(bufferSize, Baddr * bufferSize);
				memory[addr - Nbuffer * bufferSize] = data;
				valid = false;
			}
			else{
				//���������� � ����, �������� ��������� �������
				if (Nbuffer != INVALID) {
					saveBuffer(bufferSize, Nbuffer * bufferSize);
				}
				Nbuffer = Baddr;
				buffering(bufferSize, Baddr * bufferSize);
				memory[addr - Nbuffer * bufferSize] = data;
				valid = false;
			}
		}
	}
}

void mem::buffering(SMP_word bsize, SMP_word entry)
{
	valid = true;
	openFile();
	if (memFile.is_open()) {
		memFile.seekg(8 * entry, std::ios::beg);
		memFile.read(reinterpret_cast<char*>(memory), sizeof(SMP_word) * bsize);
		closeFile();
	}
}
void mem::saveBuffer(SMP_word bsize, SMP_word entry) 
{
	openFile();
	if (memFile.is_open()) {
		memFile.seekg(8 * entry, std::ios::beg);
		memFile.write(reinterpret_cast<char*>(memory), sizeof(SMP_word) * bsize);
		closeFile();
	}
}