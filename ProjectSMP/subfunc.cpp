//#pragma once
#ifndef def
   #include "def.h"
#endif

SMP_word get_field(SMP_word a, int l, int h) 
{
	SMP_word res = a;
	SMP_word size = 8 * sizeof(SMP_word);

	SMP_word rl = size - l - 1;
	SMP_word rh = size - h - 1;

	res = res << (size - rl - 1);
	res = res >> (size - rl - 1 + rh);
	return res;
}
bool get_bit(SMP_word a, int n)
{
	SMP_word temp = 1;
	temp = temp << (8 * sizeof(SMP_word) - n - 1);
	return temp & a;
}

int64_t signExtword2dword(int64_t a)
{
	int64_t temp = a;
	temp = a << 32;
	return temp >> 32;
}