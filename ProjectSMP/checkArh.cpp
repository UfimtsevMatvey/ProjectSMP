#include <cstdint>
#include "checkArh.h"
uint32_t checkArh()
{
    int res = 0;
    asm volatile(
		"MOV EAX, 0x7	        \n\t"
        "XOR ECX, ECX           \n\t"
        "CPUID                  \n\t"
        "MOV EAX, 1             \n\t"
        "SHL EAX, 28            \n\t"
        "MOV ECX, EBX           \n\t"
        "AND ECX, EAX           \n\t"
        "SHL EAX, 12            \n\t"
  //      "AND EBX, EAX           \n\t"
  //      "ADD ECX, EBX            \n\t"
        "MOV %0, EBX            \n\t"
    	: "=r" (res));
    return res;
}