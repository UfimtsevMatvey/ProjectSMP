#include "checkArh.h"
int checkArh()
{
    int res = 0;
    asm volatile(
		"MOV EAX, 0x00000007	\n\t"
        "CPUID                  \n\t"
        "AND EBX, 0x10010000    \n\t"
        "MOV %0, EBX            \n\t"
    	: "=r" (res));
    return res;
}