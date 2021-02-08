//#pragma once
#include "headers/testClass.h"
#include "headers/opcode.h"
#include <iostream>
#include <bitset>
#include "headers/debug_cmd.h"
#include "headers/core_Mode.h"

void debugger::debugMode(class core &C, int mode, int dbgparam)
{
    std::cout << "instr = \t" << std::bitset<64>(C.instr) << std::endl;
    for(int i = 0; i < 64; i +=2)
        std::cout << "REG["<<i<<"]\t" << std::bitset<64>(C.gpregs[i]) << " \t REG["<<i + 1<<"] \t" << std::bitset<64>(C.gpregs[i + 1])  << std::endl;
    if(mode == DEBUGMODE){
		printState(C, dbgparam);
	}
	else if(mode == STEPMODE){
		userControl(mode, dbgparam, C);
	}
}
void debugger::printState(class core &C, int dbgparam)
{
    switch(dbgparam){
    	case ALUinstr:  printState_alu(C);  return;
    	case MULinstr:  printState_mul(C);  return;
    	case wMULinstr: printState_mul(C);  return;
    	case MEMinstr:  printState_mem(C);  return;
    	case CTinstr:   printState_ct(C);   return;
    	case SYSinstr:  printState_sys(C);  return;
    	default:        printState_Error(C);return;
    }
}
void debugger::printState_Error(class core &C)
{
    std::cout << "Error dbg code." << std::endl;
    return;
}

void debugger::printState_alu(class core &C)
{
	std::cout << "aluTypeInst.priv = \t" << std::bitset<2>(C.aluTypeInst.priv) << std::endl;
	std::cout << "aluTypeInst.cond = \t" << std::bitset<5>(C.aluTypeInst.cond) << std::endl;
	std::cout << "aluTypeInst.opcode = \t" << std::bitset<4>(C.aluTypeInst.opcode) << std::endl;
	std::cout << "aluTypeInst.I = \t" << std::bitset<1>(C.aluTypeInst.I) << std::endl;
	std::cout << "aluTypeInst.S = \t" << std::bitset<1>(C.aluTypeInst.S) << std::endl;
	std::cout << "aluTypeInst.func = \t" << std::bitset<5>(C.aluTypeInst.func) << std::endl;
	std::cout << "aluTypeInst.Rn = \t" << std::bitset<6>(C.aluTypeInst.Rn) << std::endl;
	std::cout << "aluTypeInst.Rd = \t" << std::bitset<6>(C.aluTypeInst.Rd) << std::endl;
	std::cout << "aluTypeInst.Rm = \t" << std::bitset<6>(C.aluTypeInst.Rm) << std::endl;
	std::cout << "aluTypeInst.Ra = \t" << std::bitset<6>(C.aluTypeInst.Ra) << std::endl;
	std::cout << "aluTypeInst.imm16 = \t" << std::bitset<16>(C.aluTypeInst.imm16) << std::endl;
	std::cout << "aluTypeInst.imm32 = \t" << std::bitset<32>(C.aluTypeInst.imm32) << std::endl;
    return;
}
void debugger::printState_mul(class core &C)
{
	std::cout << "mulTypeInst.priv = \t" << std::bitset<2>(C.mulTypeInst.priv) << std::endl;
	std::cout << "mulTypeInst.cond = \t" << std::bitset<5>(C.mulTypeInst.cond) << std::endl;
	std::cout << "mulTypeInst.opcode = \t" << std::bitset<4>(C.mulTypeInst.opcode) << std::endl;
	std::cout << "mulTypeInst.typeOper = \t" << std::bitset<1>(C.mulTypeInst.typeOper) << std::endl;
	std::cout << "mulTypeInst.S = \t" << std::bitset<1>(C.mulTypeInst.S) << std::endl;
	std::cout << "mulTypeInst.TO = \t" << std::bitset<1>(C.mulTypeInst.TO) << std::endl;
	std::cout << "mulTypeInst.Ra = \t" << std::bitset<6>(C.mulTypeInst.Ra) << std::endl;
	std::cout << "mulTypeInst.Rn = \t" << std::bitset<6>(C.mulTypeInst.Rn) << std::endl;
	std::cout << "mulTypeInst.Rd = \t" << std::bitset<6>(C.mulTypeInst.Rd) << std::endl;
	std::cout << "mulTypeInst.Rm = \t" << std::bitset<6>(C.mulTypeInst.Rm) << std::endl;
	std::cout << "mulTypeInst.imm32 = \t" << std::bitset<32>(C.mulTypeInst.imm32) << std::endl;
    return;
}

void debugger::printState_mem(class core &C)
{
	std::cout << "memTypeInst.priv = \t" << std::bitset<2>(C.memTypeInst.priv) << std::endl;
	std::cout << "memTypeInst.cond = \t" << std::bitset<5>(C.memTypeInst.cond) << std::endl;
	std::cout << "memTypeInst.opcode = \t" << std::bitset<4>(C.memTypeInst.opcode) << std::endl;
	std::cout << "memTypeInst.typeOper = \t" << std::bitset<1>(C.memTypeInst.typeOper) << std::endl;
	std::cout << "memTypeInst.sizeOp = \t" << std::bitset<2>(C.memTypeInst.sizeOp) << std::endl;
	std::cout << "memTypeInst.Rn = \t" << std::bitset<6>(C.memTypeInst.Rn) << std::endl;
	std::cout << "memTypeInst.Rd = \t" << std::bitset<6>(C.memTypeInst.Rd) << std::endl;
	std::cout << "memTypeInst.scale = \t" << std::bitset<5>(C.memTypeInst.scale) << std::endl;
    std::cout << "memTypeInst.offset = \t" << std::bitset<32>(C.memTypeInst.offset) << std::endl;
    return;
}

void debugger::printState_ct(class core &C)
{
	std::cout << "ctTypeInst.priv = \t" << std::bitset<2>(C.ctTypeInst.priv) << std::endl;
	std::cout << "ctTypeInst.cond = \t" << std::bitset<5>(C.ctTypeInst.cond) << std::endl;
	std::cout << "ctTypeInst.opcode = \t" << std::bitset<4>(C.ctTypeInst.opcode) << std::endl;
	std::cout << "ctTypeInst.typeOper = \t" << std::bitset<4>(C.ctTypeInst.typeOper) << std::endl;
	std::cout << "ctTypeInst.R = \t" << std::bitset<6>(C.ctTypeInst.R) << std::endl;
    std::cout << "ctTypeInst.imm48 = \t" << std::bitset<48>(C.ctTypeInst.imm48) << std::endl;
    return;
}
void debugger::printState_sys(class core &C)
{
	std::cout << "sysTypeInst.priv = \t" << std::bitset<2>(C.sysTypeInst.priv) << std::endl;
	std::cout << "sysTypeInst.cond = \t" << std::bitset<5>(C.sysTypeInst.cond) << std::endl;
	std::cout << "sysTypeInst.opcode = \t" << std::bitset<4>(C.sysTypeInst.opcode) << std::endl;
	std::cout << "sysTypeInst.typeOper = \t" << std::bitset<4>(C.sysTypeInst.typeOper) << std::endl;
	std::cout << "sysTypeInst.port = \t" << std::bitset<6>(C.sysTypeInst.port) << std::endl;
	std::cout << "sysTypeInst.Rn = \t" << std::bitset<6>(C.sysTypeInst.Rn) << std::endl;
	std::cout << "sysTypeInst.Rd = \t" << std::bitset<6>(C.sysTypeInst.Rd) << std::endl;
	std::cout << "sysTypeInst.I = \t" << std::bitset<1>(C.sysTypeInst.I) << std::endl;
    std::cout << "sysTypeInst.inum = \t" << std::bitset<6>(C.sysTypeInst.inum) << std::endl;
    return;
}
void debugger::userControl(int mode, int dbgparam, class core &C)
{
	int command;
	std::cout << ">>";
	std::cin >> command;
	switch(command){
		case NULLCMD:	return;
		case PRTCMD:	printState(C, dbgparam); return;
		default: return;
	}
}