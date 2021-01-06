//#pragma once
#include "regf.h"
#ifndef def
   #include "def.h"
#endif
//Likely write and read function will cut
void regf::write(byte N, SMP_word data)
{
	if (N < NREG)
		R[N] = data;
}

void regf::read(byte N, SMP_word& data)
{
	if (N < NREG)
		data = R[N];
	else
		data = 0;
}
regf::regf()
{
	int i = 0;
	for (i = 0; i < NREG; i++)
		R[i] = 0;
}
void regf::operator =(const regf& E)
{
	for (int i = 0; i < NREG; i++)
		R[i] = E.R[i];
}
SMP_word& regf::operator[ ](SMP_word i)
{
	if(i < NREG)
		return R[i];
	else
		return R[0];
	
}
void regf::flush()
{
	for (int i = 0; i < NREG; i++)
		R[i] = 0;
}