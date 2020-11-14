
#include "regf.h"
#ifndef def
   #include "def.h"
#endif
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
{//Инициализация регистрового файла
	int i = 0;
	for (i = 0; i < NREG; i++)
		R[i] = 0;
}
void regf::operator =(const regf& E)
{
	for (int i = 0; i < NREG; i++)
		R[i] = E.R[i];
}
void regf::flush()
{
	for (int i = 0; i < NREG; i++)
		R[i] = 0;
}