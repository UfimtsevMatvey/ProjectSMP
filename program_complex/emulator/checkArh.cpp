#include <cstdint>
#include "headers/checkArh.h"
/*
    return false if CPU is supported and true else.
*/
bool checkArh()
{
    int prop = 0;
    asm volatile(
		"MOV EAX, 0x7	        \n\t"
        "XOR ECX, ECX           \n\t"
        "CPUID                  \n\t"
        "AND EBX, 0x20          \n\t"
        "MOV %0, EBX            \n\t"
    	: "=r" (prop));
    return (prop != 0x20);
}