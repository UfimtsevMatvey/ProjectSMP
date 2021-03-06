#pragma once
#include <cstdint>
#include <vector>
#define NREG 64
#define IMSIZE 8192
#define DMSIZE 8192
#define MAGICNUMBER 0xFFFFFFFFFFFFFFFF
#define MASK64 0xFFFFFFFFFFFFFFFF
#define MASK32 0xFFFFFFFF
#define MASK16 0xFFFF
#define MASK8 0xFF

typedef uint64_t SMP_word;
typedef uint64_t reg;
typedef uint32_t word;
typedef uint16_t half_word;
typedef uint8_t byte;

typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;

struct ddwordu{
    SMP_word l;
    SMP_word h;
};

struct ddwords{
    SMP_word l;
    SMP_word h;
};

union bit64{
    uint64_t u;
    int64_t s;
};

union bit128{
    ddwordu dsu;// Low and High part of unsigned SMP word
    ddwords dss;// Low and High part of signed SMP word
    uint128_t dw;
};