#pragma once
#ifndef def
   #include "def.h"
#endif
SMP_word get_field(SMP_word a, int l, int h);
bool get_bit(SMP_word a, int n);
int64_t signExtword2dword(int64_t a);