#include <cstdint>
#include "checkArh.h"
uint32_t checkArh()
{
    int res = 0;
    asm volatile(
		"MOV EAX, 0x7	        \n\t"
        "XOR ECX, ECX           \n\t"
        "CPUID                  \n\t"
        "AND EBX, 0x20          \n\t"
        "MOV %0, EBX            \n\t"
    	: "=r" (res));
    return res;
}