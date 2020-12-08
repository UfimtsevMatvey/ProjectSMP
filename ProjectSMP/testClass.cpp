#pragma once
#include "testClass.h"
#include <iostream>
#include <bitset>
//#include "core.h"



void debugger::debugMode(class core &C)
{
    printState(C);
    return;
}

/*void debugger::debugMode(class core &C)
{
    std::cout << "instr = \t" << std::bitset<64>(C.instr) << std::endl;

    std::cout << "aluTypeInst = \t" << std::bitset<8>(C.aluTypeInst.priv) << std::endl;
    std::cout << "mulTypeInst = \t" << std::bitset<8>(C.mulTypeInst.priv) << std::endl;
    std::cout << "memTypeInst = \t" << std::bitset<8>(C.memTypeInst.priv) << std::endl;
    std::cout << "ctTypeInst = \t" << std::bitset<8>(C.ctTypeInst.priv) << std::endl;
    std::cout << "sysTypeInst = \t" << std::bitset<8>(C.sysTypeInst.priv) << std::endl;

    std::cout << "flags = \t" << std::bitset<64>(C.FLR) << std::endl;

    for(int i = 0; i < 64; i +=2)
        std::cout << "REG["<<i<<"]\t" << std::bitset<64>(C.gpregs[i]) << " \t REG["<<i + 1<<"] \t" << std::bitset<64>(C.gpregs[i + 1])  << std::endl;
    return;
}*/

void debugger::printState(class core &C)
{
    std::cout << "instr = \t" << std::bitset<64>(C.instr) << std::endl;

    std::cout << "aluTypeInst = \t" << std::bitset<4>(C.aluTypeInst.opcode) << std::endl;
    std::cout << "aluTypeInst Rd = \t" << std::bitset<6>(C.aluTypeInst.Rd) << std::endl;
    std::cout << "aluTypeInst Rn = \t" << std::bitset<6>(C.aluTypeInst.Rn) << std::endl;
    std::cout << "aluTypeInst Rm = \t" << std::bitset<6>(C.aluTypeInst.Rm) << std::endl;
    std::cout << "aluTypeInst Ra = \t" << std::bitset<6>(C.aluTypeInst.Ra) << std::endl;
    std::cout << "aluTypeInst imm32 = \t" << std::bitset<32>(C.aluTypeInst.imm32) << std::endl;
    std::cout << "aluTypeInst I = \t" << std::bitset<1>(C.aluTypeInst.I) << std::endl;
    std::cout << "mulTypeInst = \t" << std::bitset<4>(C.mulTypeInst.opcode) << std::endl;
    std::cout << "memTypeInst = \t" << std::bitset<4>(C.memTypeInst.opcode) << std::endl;
    std::cout << "ctTypeInst = \t" << std::bitset<4>(C.ctTypeInst.opcode) << std::endl;
    std::cout << "sysTypeInst = \t" << std::bitset<4>(C.sysTypeInst.opcode) << std::endl;

    std::cout << "flags = \t" << std::bitset<64>(C.FLR) << std::endl;

    for(int i = 0; i < 64; i +=2)
        std::cout << "REG["<<i<<"]\t" << std::bitset<64>(C.gpregs[i]) << " \t REG["<<i + 1<<"] \t" << std::bitset<64>(C.gpregs[i + 1])  << std::endl;
    return;
}
