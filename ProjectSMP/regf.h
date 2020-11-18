#pragma once
#ifndef def
   #include "def.h"
#endif
class regf
{
public:
	regf();
	void operator =(const regf& E);
	void flush();
	void write(byte N, SMP_word data);
	void read(byte N, SMP_word& data);
	SMP_word& operator[](SMP_word i);
private:
	SMP_word R[NREG];
};