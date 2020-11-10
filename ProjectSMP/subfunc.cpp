#pragma once
#include "def.h"

SMP_word get_field(SMP_word a, int l, int h) 
{
	SMP_word res = a;
	SMP_word size = sizeof(SMP_word);
	SMP_word temp = h - size;
	res = res << temp;
	temp += l;
	res = res >> temp;
	return res;
}
