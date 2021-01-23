#include <cstdint>
#include "checkArh.h"
uint32_t checkArh()
{
    int res = 0;
    asm volatile(
		"MOV EAX, 0x1	        \n\t"
        "XOR ECX, ECX           \n\t"
        "CPUID                  \n\t"
        "MOV EAX, 1             \n\t"
        "SHL EAX, 28            \n\t"
        "AND ECX, EAX           \n\t"
        "MOV %0, ECX            \n\t"
    	: "=r" (res));
    return res;
}