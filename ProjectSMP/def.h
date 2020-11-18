#pragma once
#include <cstdint>
#include <vector>
#define NREG 64
#define IMSIZE 8192
#define DMSIZE 8192
#define MAGICNUMBER 0xFFFFFFFFFFFFFFFF
typedef uint64_t SMP_word;
typedef uint64_t reg;
typedef uint32_t word;
typedef uint16_t half_word;
typedef uint8_t byte;

typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;


union bit64{
    uint64_t u;
    int64_t s;
};