#pragma once
#include "core.h"
#include <iostream>
#include "subfunc.h"
#include "funcCode.h"
#include "opcode.h"
#include "memSizeOper.h"
#include "ctCode.h"
#include "sysCode.h"
#include "flagNum.h"
#ifndef def
   #include "def.h"
#endif

using namespace std;

core::core(SMP_word entry, SMP_word isize, SMP_word dsize, const char* ifile, const char* dfile)
{
	FLR = 0;
	PC = entry;
	initMemory(isize, dsize, ifile, dfile);
}
void core::initMemory(SMP_word isize, SMP_word dsize, const char* fileInst, const char* fileData)
{
	instr_mem.Init(isize, fileInst);
	data_mem.Init(dsize, fileData);
}
void core::test_start(SMP_word testInstr)
{
	{
		//Testing command path
		instr = testInstr;
		decodeInst();
		exec();
		return;
	}

	SMP_word data = 0;
	store2reg(32, 346);
	load2reg(32, data);

	for (SMP_word i = 0; i < 8192; i++) {
		store2memData(i, 0xFFFFFFFFFFAA0000 + i);

		load2memData(i, data);
		std::cout << std::hex << data << std::endl;
	}
	syncDataFile();
}
void core::start()
{
	fetchInstr();
	decodeInst();
	exec();
	flushInstr();
}
void core::decodeInst()
{
	SMP_word opcode;
	opcode = get_field(instr, 7, 10);
	switch(opcode){
		case ALUinstr:{
			init_ALU();
			break;
		}
		case MULinstr:{
			init_MUL();
			break;
		}	
		case wMULinstr:{
			init_MUL();
			break;
		}
		case MEMinstr:{
			init_MEM();
			break;
		}
		case CTinstr:{
			init_CT();
			break;
		}
		case SYSinstr:{
			init_SYS(); 
			break;
		}
	}
}

void core::exec() 
{
	SMP_word opcode = get_field(instr, 7, 10);
	switch(opcode){
		case ALUinstr:{
			alu_exec();
			break;
		}
		case MULinstr:{
			mul_exec();
			break;
		}	
		case wMULinstr:{
			mul_exec();
			break;
		}
		case MEMinstr:{
			mem_exec();
			break;
		}
		case CTinstr:{
			ct_exec();
			break;
		}
		case SYSinstr:{
			sys_exec(); 
			break;
		}
	}
}

void core::alu_exec()
{
	switch(aluTypeInst.func){
		case FUNC_AND: 		AND(); break;
		case FUNC_EOR: 		EOR(); break;
		case FUNC_ORR: 		ORR(); break;
		case FUNC_TST: 		TST(); break;
		case FUNC_TEQ: 		TEQ(); break;
		case FUNC_CMP: 		CMP(); break; 
		case FUNC_CMN: 		CMN(); break;
		case FUNC_ADD: 		ADD(); break;
		case FUNC_SUB: 		SUB(); break;
		case FUNC_ADC: 		ADC(); break;
		case FUNC_RSB: 		RSB(); break;
		case FUNC_SBC: 		SBC(); break;
		case FUNC_MVN: 		MVN(); break;
		case FUNC_LSL: 		LSL(); break;
		case FUNC_ASR: 		ASR(); break;
		case FUNC_RRX: 		RRX(); break;
		case FUNC_ROR: 		ROR(); break;
		case FUNC_BSWP: 	BSWP(); break;
		case FUNC_SWR: 		SWR(); break;
		case FUNC_UADDPB: 	UADDPB(); break;
		case FUNC_UADDPH: 	UADDPH(); break;
		case FUNC_UADDPW: 	UADDPW(); break;
		case FUNC_SADDPB: 	SADDPB(); break;
		case FUNC_SADDPH: 	SADDPH(); break;
		case FUNC_SADDPW: 	SADDPW(); break;
		case FUNC_VUADDB: 	VUADDB(); break;
		case FUNC_VUADDH: 	VUADDH(); break;
		case FUNC_VSADDB: 	VSADDB(); break;
		case FUNC_VSADDH: 	VSADDH(); break;
	}
}
void core::mul_exec()
{
	if(!mulTypeInst.typeOper){
		//Multiply without additional
		if(mulTypeInst.opcode == MULinstr){
			//Unsigned instraction
			MUL();
		}
		else if(mulTypeInst.opcode == wMULinstr){
			//Sign instraction
			if(mulTypeInst.S){
				SMULL();
			}
			else{
				UMULL();
			}
		}
	}
	else{
		//Multiply with additional
		if(mulTypeInst.opcode == MULinstr){
			MLA();
		}
		else if(mulTypeInst.opcode == wMULinstr){
			//Sign mul
			if(mulTypeInst.S){
				SMLAL();
			}//unsign mul
			else{
				UMLAL();
			}
		}
	}
}
void core::mem_exec()
{
	if(memTypeInst.typeOper){
		//load
		switch(memTypeInst.sizeOp){
			case BITS64: LDR(); 	break;
			case BITS32: LDRW();	break;
			case BITS16: LDRHW();	break;
			case BITS08: LDRB();	break;
		}
	}
	else{
		//Store
		switch(memTypeInst.sizeOp){
			case BITS64: STR(); 	break;
			case BITS32: STRW();	break;
			case BITS16: STRHW();	break;
			case BITS08: STRB();	break;
		}
	}	
}
void core::ct_exec()
{
	switch(ctTypeInst.typeOper){
		case BL_CODE:		BL();		break;
		case BO_REG_CODE:	BO_REG();	break;
		case BO_IMM_CODE:	BO_IMM();	break;
		case B_REG_CODE:	B_REG();	break;
		case B_IMM_CODE:	B_IMM();	break;
		case RET_CODE:		RET(); 		break;
		case XRET_CODE: 	XRET(); 	break;
	}
}
void core::sys_exec()
{
	switch(sysTypeInst.typeOper){
		case INSY_CODE:	INSY(); break;
		case IN_CODE: 	IN(); 	break;
		case OUTSY_CODE:OUTSY();break;
		case OUT_CODE: 	OUT(); 	break;
		case SFL_CODE: 	SFL(); 	break;
		case LFL_CODE: 	LFL(); 	break;
		case SMF_CODE: 	SMF(); 	break;
		case SINT_CODE:	SINT(); break;
		case BINT_CODE:	BINT(); break;
		case UINT_CODE: UINT(); break;
		case CINT_CODE: CINT(); break;
		case INT_CODE: 	INT(); 	break;

	}
}

void core::init_ALU()
{
	aluTypeInst.priv = get_field(instr, 0, 1);
	aluTypeInst.cond = get_field(instr, 2, 6);
	aluTypeInst.opcode = get_field(instr, 7, 10);
	aluTypeInst.I = get_bit(instr, 11);
	aluTypeInst.S = get_bit(instr, 12);
	aluTypeInst.func = get_field(instr, 13, 17);
	aluTypeInst.Rn = get_field(instr, 19, 24);
	aluTypeInst.Rd = get_field(instr, 25, 30);
	aluTypeInst.Rm = get_field(instr, 31, 36);
	aluTypeInst.Ra = get_field(instr, 37, 42);
	aluTypeInst.imm16 = get_field(instr, 43, 58);
	aluTypeInst.imm32 = get_field(instr, 31, 62);
}
void core::init_MUL()
{
	mulTypeInst.priv = get_field(instr, 0, 1);
	mulTypeInst.cond = get_field(instr, 2, 6);
	mulTypeInst.opcode = get_field(instr, 7, 10);
	mulTypeInst.typeOper = get_bit(instr, 11);
	mulTypeInst.S = get_bit(instr, 12);
	mulTypeInst.TO = get_bit(instr, 12);
	mulTypeInst.Ra = get_field(instr, 13, 18);
	mulTypeInst.Rn = get_field(instr, 19, 24);
	mulTypeInst.Rd = get_field(instr, 25, 30);
	mulTypeInst.Rm = get_field(instr, 31, 36);
	mulTypeInst.imm32 = get_field(instr, 31, 62);
}
void core::init_MEM()
{
	memTypeInst.priv = get_field(instr, 0, 1);
	memTypeInst.cond = get_field(instr, 2, 6);
	memTypeInst.opcode = get_field(instr, 7, 10);
	memTypeInst.typeOper = get_bit(instr, 11);
	memTypeInst.sizeOp = get_field(instr, 12, 13);
	memTypeInst.Rn = get_field(instr, 19, 24);
	memTypeInst.Rd = get_field(instr, 25, 30);
	memTypeInst.scale = get_field(instr, 14, 18);
	memTypeInst.offset = get_field(instr, 31, 62);
}
void core::init_CT()
{
	ctTypeInst.priv = get_field(instr, 0, 1);
	ctTypeInst.cond = get_field(instr, 2, 6);
	ctTypeInst.opcode = get_field(instr, 7, 10);
	ctTypeInst.typeOper = get_field(instr, 11, 14);
	ctTypeInst.R = get_field(instr, 19, 24);
	ctTypeInst.imm48 = get_field(instr, 15, 62);
}
void core::init_SYS()
{
	sysTypeInst.priv = get_field(instr, 0, 1);
	sysTypeInst.cond = get_field(instr, 2, 6);
	sysTypeInst.opcode = get_field(instr, 7, 10);
	sysTypeInst.typeOper = get_field(instr, 11, 14);
	sysTypeInst.port = get_field(instr, 15, 18);
	sysTypeInst.Rn = get_field(instr, 19, 24);
	sysTypeInst.Rd = get_field(instr, 19, 24);
	sysTypeInst.I = get_bit(instr, 31);
	sysTypeInst.inum = get_field(instr, 32, 37);
}
void core::setAALUflag(SMP_word res, SMP_word oper1, SMP_word oper2, SMP_word care)
{
	bit64 bres;
	bit64 boper1;
	bit64 boper2;

	bres.u = res;
	boper1.u = oper1;
	boper2.u = oper2;

	
	int64_t soper1 = boper1.s;
	int64_t soper2 = boper2.s;

	soper1 = signExtword2dword(soper1);
	soper2 = signExtword2dword(soper2);
	int64_t sres = soper1 + soper2;
	uint128_t sum = oper1 + oper2;
	int128_t ssum = soper1 + soper2;
	if(res == 0)		setFlag(Z);//Z - flag
	else				resetFlag(Z);

	if(sum > MAGICNUMBER)	setFlag(C);
	else 					resetFlag(C);

	if(sres < 0){
		setFlag(N);
	}
	else{
		resetFlag(N);
	}
	if(ssum > (static_cast<int128_t>(1) << 64)){
		setFlag(V);
	}
	else{
		resetFlag(V);
	}
}

void core::setLALUflag(SMP_word res)
{
	if(res == 0)		setFlag(Z);//Z - flag
	else				resetFlag(Z);
}
void core::setFlag(int n)
{
	SMP_word temp = 1;
	temp = temp << 8 * sizeof(SMP_word) - n - 1;
	FLR = FLR | temp;
}

void core::resetFlag(int n)
{
	SMP_word temp = 1;
	temp = temp << 8 * sizeof(SMP_word) - n - 1;
	temp = ~temp;
	FLR = FLR & temp;
}

void core::resetFLR()
{
	FLR = 0;
}
void core::resetINR()
{
	INR = 0;
}
void core::resetPC()
{
	PC = 0;
}
void core::flushInstr() 
{
	aluTypeInst.flush();
	mulTypeInst.flush();
	memTypeInst.flush();
	ctTypeInst.flush();
	sysTypeInst.flush();
}
void core::reset() 
{
	gpregs.flush();
	idgers.flush();
	resetFLR();
	resetINR();
	flushInstr();
	resetPC();
}
void core::syncDataFile() 
{
	data_mem.syncFile();
}
void core::fetchInstr()
{
	getIntr(PC, instr);
}

void core::load2reg(byte addr, SMP_word& data)
{
	gpregs.read(addr, data);
}
void core::store2reg(byte addr, SMP_word data)
{
	gpregs.write(addr, data);
}
void core::load2memData(SMP_word addr, SMP_word& data)
{
	data_mem.load(addr, data);
}
void core::store2memData(SMP_word addr, SMP_word data)
{
	data_mem.store(addr, data);
}
void core::getIntr(SMP_word ip, SMP_word& instr)
{
	instr_mem.load(ip, instr);
}
void core::AND() 
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] & oper2;
	gpregs[Rd] = res;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::EOR() 
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] ^ oper2;
	gpregs[Rd] = res;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::ORR()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] | oper2;
	gpregs[Rd] = res;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::TST()
{
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] & oper2;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::TEQ()
{
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] ^ oper2;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::CMP()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word oper1 = gpregs[Rd];
	SMP_word oper2;
	SMP_word addoper2;
	bit64 boper1;
	bit64 boper2;

	int64_t soper1;
	int64_t soper2;
	int64_t sres;
	SMP_word res;
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

	soper1 = signExtword2dword(soper1);
	soper2 = signExtword2dword(soper2);
	addoper2 = ~oper2 + static_cast<uint64_t>(1);
	res = oper1 + addoper2;
	sres = soper1 - soper2;
	if(aluTypeInst.S)	setAALUflag(res, oper1, addoper2, 0);
	PC += 8;
	return;
}
void core::CMN()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word oper1 = gpregs[Rd];
	SMP_word oper2;

	bit64 boper1;
	bit64 boper2;

	int64_t soper1;
	int64_t soper2;
	int64_t sres;

	SMP_word res;
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

	soper1 = signExtword2dword(soper1);
	soper2 = signExtword2dword(soper2);
	res = oper1 + oper2;
	sres = soper1 + soper2;
	if(aluTypeInst.S)	setAALUflag(res, oper1, oper2, 0);
	PC += 8;
	return;
}
void core::ADD()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;

	bit64 boper1;
	bit64 boper2;

	int64_t soper1;
	int64_t soper2;
	int64_t sres;

	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

	soper1 = signExtword2dword(soper1);
	soper2 = signExtword2dword(soper2);
	res = oper1 + oper2;
	sres = soper1 + soper2;
	gpregs[Rd] = oper1 + oper2;
	if(aluTypeInst.S)	setAALUflag(res, oper1, oper2, 0);
	PC += 8;
	return;
}
void core::SUB()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;
	SMP_word addoper2;
	SMP_word res;

	bit64 boper1;
	bit64 boper2;

	int64_t soper1;
	int64_t soper2;
	int64_t sres;

	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

	soper1 = signExtword2dword(soper1);
	soper2 = signExtword2dword(soper2);
	addoper2 = ~oper2 + static_cast<uint64_t>(1);
	res = oper1 + addoper2;
	sres = soper1 - soper2;
	gpregs[Rd] = oper1 + (~oper2) + static_cast<uint64_t>(1);
	if(aluTypeInst.S)	setAALUflag(res, oper1, addoper2, 0);
	PC += 8;
	return;
}
void core::ADC()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;
	SMP_word care = get_bit(FLR, 3) ? static_cast<uint64_t>(1) : static_cast<uint64_t>(0);

	bit64 boper1;
	bit64 boper2;
	
	uint64_t soper1;
	uint64_t soper2;
	uint64_t sres;

	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

	res = oper1 + oper2 + care;
	sres = soper1 + soper2 + care;
	gpregs[Rd] = oper1 + oper2 + care;
	if(aluTypeInst.S)	setAALUflag(res, oper1, oper2, care);
	PC += 8;
	return;
}
void core::RSB()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2 = 0;
	SMP_word addoper2 = 0;
	SMP_word care = 0;
	SMP_word res = 0;

	bit64 boper1;
	bit64 boper2;

	uint64_t soper1;
	uint64_t soper2;
	uint64_t sres;

	if(aluTypeInst.cond != 0b1111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

	soper1 = signExtword2dword(soper1);
	soper2 = signExtword2dword(soper2);
	addoper2 = ~oper1 + static_cast<uint64_t>(1) + care;
	res = oper2 + addoper2;
	sres = -soper1 + soper2;
	gpregs[Rd] = (~oper1) + oper2 + static_cast<uint64_t>(1);
	if(aluTypeInst.S)	setAALUflag(res, oper2, addoper2, 0);
	PC += 8;
	return;
}
void core::SBC()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2 = 0;
	SMP_word addoper2 = 0;
	SMP_word care = get_bit(FLR, 3) ? static_cast<uint64_t>(1) : static_cast<uint64_t>(0);

	bit64 boper1;
	bit64 boper2;

	int64_t sres;
	int64_t soper1;
	int64_t soper2;

	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

	addoper2 = ~oper2 + static_cast<uint64_t>(1) + care;
	res = oper1 + addoper2;
	sres = soper1 - soper2 + care;
	gpregs[Rd] = oper1 + addoper2;
	if(aluTypeInst.S)	setAALUflag(res, oper1, addoper2, care);
	PC += 8;
	return;
}
void core::MVN()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	bit64 boper1;
	boper1.u = oper1;

	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	res = ~oper1;
	gpregs[Rd] = res;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::LSL()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = oper1 << oper2;
	gpregs[Rd] = res;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::LSR()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;

	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = oper1 >> oper2;
	gpregs[Rd] = res;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::ASR()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;
	SMP_word care = get_bit(FLR, 3) ? static_cast<uint64_t>(1) : static_cast<uint64_t>(0);

	bit64 bres;
	bit64 boper1;
	bit64 boper2;

	int64_t sres;
	int64_t soper1;
	int64_t soper2;
	
	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	
	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

	soper1 = signExtword2dword(soper1);
	soper2 = signExtword2dword(soper2);
	sres = soper1 >> soper2;
	bres.s = sres;
	gpregs[Rd] = bres.u;
	if(aluTypeInst.S){
		setLALUflag(res);
		if(sres < 0) setFlag(N);
		else resetFlag(N);
	}
	PC += 8;
	return;
}
void core::RRX()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	oper2 = oper2 & 0x000000000000003F;//Only 6 bit in shifh operand

	SMP_word temp1 = (get_bit(FLR, 3) ? static_cast<uint64_t>(1) : static_cast<uint64_t>(0)) << 63;
	SMP_word temp2;
	for(int i = 0; i < oper2; i++){
		temp2 = (get_bit(oper1, 63) ? static_cast<uint64_t>(1) : static_cast<uint64_t>(0)) << 63;
		oper1 = oper1 >> 1;
		oper1 = oper1 | temp1;
		temp1 = temp2;
	}
	if(temp1) 	setFlag(C);
	else 		resetFlag(C);
	gpregs[Rd] = res;


	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::ROR()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;
	SMP_word res;

	bit64 bres;
	bit64 boper1;
	bit64 boper2;

	int64_t sres;
	int64_t soper1;
	int64_t soper2;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	oper2 = oper2 & 0x000000000000003F;//Only 6 bit in shifh operand
	bres.u = res;
	boper1.u = oper1;
	boper2.u = oper2;

	sres = bres.s;
	soper1 = boper1.s;
	soper2 = boper2.s;

	soper1 = signExtword2dword(soper1);
	soper2 = signExtword2dword(soper2);
	SMP_word temp;
	for(int i = 0; i < soper2; i++){
		temp = get_bit(res, 0) << 63;
		oper1 = oper1 >> 1;
		oper1 = oper1 | temp;
	}

	gpregs[Rd] = res;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::BSWP()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word res = 0;
	SMP_word oper = gpregs[Rd];
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	asm volatile(
		"MOV rax, %1		\n\t"
    	"BSWAP rax			\n\t"
		"MOV %0, rax		\n\t"
   		: "=r" (res)
   		: "r" (oper));
	PC += 8;
	return;
}
void core::SWR()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	SMP_word temp = gpregs[Rd];
	gpregs[Rd] = gpregs[Rn];
	gpregs[Rn] = temp;
	PC += 8;
	return;
}

//SIMD

void core::UADDPB()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;

	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	asm volatile(
		"MOVD mm0, %0				\n\t"
		"MOVD mm1, %1				\n\t"
    	"PADDUSB mm1, mm0			\n\t"
		"MOVQ %2, mm1				\n\t"
    	: "=r" (res)
    	: "r" (oper1), "r" (oper2)); 

	gpregs[Rd] = res;
	PC += 8;
	return;
}
void core::UADDPH()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;

	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	asm volatile(
		"MOVD mm0, %1				\n\t"
		"MOVD mm1, %2				\n\t"
    	"PADDUSW mm1, mm0			\n\t"
		"MOVQ %0, mm1				\n\t"
    	: "=r" (res)
    	: "r" (oper1), "r" (oper2)); 

	gpregs[Rd] = res;
	PC += 8;
	return;
}
void core::UADDPW()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;

	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	asm volatile(
		"MOVD xmm0, %1				\n\t"
		"MOVD xmm1, %2				\n\t"
    	"PADDD xmm1, xmm0			\n\t"
		"MOVQ %0, xmm1				\n\t"
    	: "=r" (res)
    	: "r" (oper1), "r" (oper2)); 

	gpregs[Rd] = res;
	PC += 8;
	return;
}

void core::SADDPB()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;

	bit64 boper1;
	bit64 boper2;

	int64_t soper1;
	int64_t soper2;
	int64_t sres;

	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	boper1.u = oper1;
	boper2.u = oper2;
	soper1 = boper1.s;
	soper2 = boper2.s;
	asm volatile(
		"MOVD mm0, %1 				\n\t"
		"MOVD mm1, %2 				\n\t"
    	"PADDSB mm1, mm0	 		\n\t"
		"MOVQ %0, mm1				\n\t"
    	: "=r" (sres)
    	: "r" (soper1), "r" (soper2)); 

	gpregs[Rd] = sres;
	PC += 8;
	return;
}
void core::SADDPH()
{	
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;

	bit64 boper1;
	bit64 boper2;

	uint64_t soper1;
	uint64_t soper2;
	uint64_t sres;

	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	boper1.u = oper1;
	boper2.u = oper2;
	soper1 = boper1.s;
	soper2 = boper2.s;
	asm volatile(
		"MOVD mm0, %1				\n\t"
		"MOVD mm1, %2				\n\t"
    	"PADDSW mm1, mm0			\n\t"
		"MOVQ %0, mm1				\n\t"
    	: "=r" (sres)
    	: "r" (soper1), "r" (soper2)); 

	gpregs[Rd] = sres;
	PC += 8;
	return;
}
void core::SADDPW()
{
	UADDPW();
}
//{Rd, Rn} = {Rm, Rm2} + imm8
void core::VUADDB()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word Rm1 = aluTypeInst.Rm;
	SMP_word Rm2 = aluTypeInst.Ra;

	SMP_word imm8 = aluTypeInst.imm32 & 0xFF;
	SMP_word OperH = gpregs[Rm1];
	SMP_word OperL = gpregs[Rm2];
	ddwords res;
	res.h = 0;
	res.l = 0;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	
	asm volatile(
		"MOVQ xmm2, %0				\n\t"//init registers xmm2 (imm8) and xmm3 (Rm1)
		"MOVQ xmm3, %1				\n\t"//Only low byte in xmm2 and xmm3 used
		"VPBROADCASTB xmm0, xmm2	\n\t"//Brodcasting low byte to all registers
		"VPBROADCASTQ xmm1, xmm3	\n\t"
		"MOVQ xmm2, %2				\n\t"//init xmm2 (Rm2)
		"PSLLQ xmm1, 64				\n\t"//Left shift Rm1 on half xmm size
		"POR xmm1, xmm2				\n\t"//High part of xmm1 is Rm1, low part of xmm1 is Rm2
    	"PADDUSB xmm1, xmm0			\n\t"//Calculate sum.
		"MOVQ r14, xmm1				\n\t"//Store resalt to 128-bit variable res 
		"PSRLDQ xmm1, 8				\n\t"
		"MOVQ r15, xmm1				\n\t"
		"MOV %0, r14				\n\t"
		"MOV %1, r15				\n\t" 	
		: "=r" (res.l), "=r" (res.h)
    	: "r" (imm8), "r" (OperH), "r" (OperL));

	gpregs[Rd] = res.h;
	gpregs[Rn] = res.l;
	PC += 8;
	return;
}
//{Rd, Rn} = {Rm, Rm2} + imm16
void core::VUADDH()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word Rm1 = aluTypeInst.Rm;
	SMP_word Rm2 = aluTypeInst.Ra;

	SMP_word imm16 = aluTypeInst.imm32 & 0xFFFF;
	SMP_word OperH = gpregs[Rm1];
	SMP_word OperL = gpregs[Rm2];
	ddwords res;
	res.h = 0;
	res.l = 0;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	
	asm volatile(
		"MOVQ xmm2, %2				\n\t"
		"MOVQ xmm3, %3				\n\t"
		"VPBROADCASTW xmm0, xmm2	\n\t"
		"VPBROADCASTQ xmm1, xmm3	\n\t"
		"VMOVQ xmm2, %4				\n\t"
		"PSLLDQ xmm1, 8				\n\t"
		"POR xmm1, xmm2				\n\t"
    	"PADDUSB xmm1, xmm0			\n\t"
		"MOVQ r14, xmm1				\n\t"
		"PSRLDQ xmm1, 8				\n\t"
		"MOVQ r15, xmm1				\n\t"
		"MOV %0, r14				\n\t"
		"MOV %1, r15				\n\t"
		: "=r" (res.l), "=r" (res.h)
    	: "r" (imm16), "r" (OperH), "r" (OperL));
	gpregs[Rd] = res.h;
	gpregs[Rn] = res.l;
	PC += 8;
	return;
}
//{Rd, Rn} = {Rm, Rm2} + imm8 (Signed)
void core::VSADDB()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word Rm1 = aluTypeInst.Rm;
	SMP_word Rm2 = aluTypeInst.Ra;

	SMP_word imm8 = aluTypeInst.imm32 & 0xFF;
	SMP_word OperH = gpregs[Rm1];
	SMP_word OperL = gpregs[Rm2];
	ddwords res;
	res.h = 0;
	res.l = 0;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	
	asm volatile(
		"MOVQ xmm2, %2				\n\t"
		"MOVQ xmm3, %3				\n\t"
		"VPBROADCASTB xmm0, xmm2	\n\t"
		"VPBROADCASTQ xmm1, xmm3	\n\t"
		"MOVQ xmm2, %4				\n\t"
		"PSLLDQ xmm1, 8				\n\t"
		"POR xmm1, xmm2				\n\t"
		"PADDSB xmm1, xmm0			\n\t"
		"MOVQ r14, xmm1				\n\t"
		"PSRLDQ xmm1, 8				\n\t"
		"MOVQ r15, xmm1				\n\t"
		"MOV %0, r14				\n\t"
		"MOV %1, r15				\n\t"
		: "=r" (res.l), "=r" (res.h)
    	: "r" (imm8), "r" (OperH), "r" (OperL));

	gpregs[Rd] = res.h;
	gpregs[Rn] = res.l;
	PC += 8;
	return;
}
//{Rd, Rn} = {Rm1, Rm2} + imm16 (Signed)
void core::VSADDH()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word Rm1 = aluTypeInst.Rm;
	SMP_word Rm2 = aluTypeInst.Ra;

	SMP_word imm16 = aluTypeInst.imm32 & 0xFFFF;
	SMP_word OperH = gpregs[Rm1];
	SMP_word OperL = gpregs[Rm2];
	ddwords res;
	res.h = 0;
	res.l = 0;
	if(aluTypeInst.cond != 0b11111)
		if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	
	asm volatile(
		"MOVQ xmm2, %2				\n\t"
		"MOVQ xmm3, %3				\n\t"
		"VPBROADCASTW xmm0, xmm2	\n\t"
		"VPBROADCASTQ xmm1, xmm3	\n\t"
		"MOVQ xmm2, %4				\n\t"
		"PSLLDQ xmm1, 8				\n\t"
		"POR xmm1, xmm2				\n\t"
    	"PADDSW xmm1, xmm0			\n\t"
		"MOVQ r14, xmm1				\n\t"
		"PSRLDQ xmm1, 8				\n\t"
		"MOVQ r15, xmm1				\n\t"
		"MOV %0, r14				\n\t"
		"MOV %1, r15				\n\t"
    	: "=r" (res.l), "=r" (res.h)
    	: "r" (imm16), "r" (OperH), "r" (OperL));

	gpregs[Rd] = res.h;
	gpregs[Rn] = res.l;
	PC += 8;
	return;
}

//Multipli instractions

void core::MUL()
{
	SMP_word Rd = mulTypeInst.Rd;
	SMP_word Rn = mulTypeInst.Rn;
	SMP_word Rm = mulTypeInst.Rm;
	SMP_word oper1 = 0;
	SMP_word oper2 = 0;
	SMP_word res = 0;
	if(mulTypeInst.cond != 0b11111){
		if(mulTypeInst.cond != get_field(FLR, 3, 6)) {
			return;//do Nothink, if conditional is not true
		}
	}
	if(mulTypeInst.TO){
		oper2 = mulTypeInst.imm32;
	}
	else{
		oper2 = gpregs[Rm];
	}
	oper1 = gpregs[Rn];
	res = oper1 * oper2;
	if(res == 0) setFlag(Z);
	else resetFlag(Z);
	gpregs[Rd] = res;
	PC += 8;
	return;
}
void core::MLA()
{
	SMP_word Rd = mulTypeInst.Rd;
	SMP_word Rn = mulTypeInst.Rn;
	SMP_word Rm = mulTypeInst.Rm;
	SMP_word Ra = mulTypeInst.Ra;
	SMP_word oper1 = 0;
	SMP_word oper2 = 0;
	SMP_word operA = 0;
	SMP_word res = 0;
	if(mulTypeInst.cond != 0b11111){
		if(mulTypeInst.cond != get_field(FLR, 3, 6)) {
			return;//do Nothink, if conditional is not true
		}
	}
	oper1 = gpregs[Rn];
	oper2 = gpregs[Rm];
	operA = gpregs[Ra];
	res = oper1 * oper2 + operA;
	gpregs[Rd] = res;
	PC += 8;
	return;
}
void core::UMULL()
{
	SMP_word Rd = mulTypeInst.Rd;
	SMP_word Rn = mulTypeInst.Rn;
	SMP_word Rm = mulTypeInst.Rm;
	SMP_word Ra = mulTypeInst.Ra;

	bit128 dd;
	uint128_t ddoper1;
	uint128_t ddoper2;
	uint128_t ddres;

	if(mulTypeInst.cond != 0b11111){
		if(mulTypeInst.cond != get_field(FLR, 3, 6)) {
			return;//do Nothink, if conditional is not true
		}
	}
	ddoper1 = gpregs[Rm];
	ddoper2 = gpregs[Ra];
	ddres = ddoper1 * ddoper2;
	dd.dw = ddres;
	gpregs[Rd] = dd.dsu.h;
	gpregs[Rd] = dd.dsu.l;
	PC += 8;
	return;
}
void core::UMLAL()
{
	SMP_word Rd = mulTypeInst.Rd;
	SMP_word Rn = mulTypeInst.Rn;
	SMP_word Rm = mulTypeInst.Rm;
	SMP_word Ra = mulTypeInst.Ra;

	bit128 dd;
	uint128_t ddoper1;
	uint128_t ddoper2;
	uint128_t ddres;

	if(mulTypeInst.cond != 0b11111){
		if(mulTypeInst.cond != get_field(FLR, 3, 6)) {
			return;//do Nothink, if conditional is not true
		}
	}
	ddoper1 = gpregs[Rn];
	ddoper2 = gpregs[Rm];
	ddres = ddoper1 * ddoper2;
	dd.dw = ddres;
	gpregs[Rd] = dd.dsu.h + gpregs[Rd];
	gpregs[Ra] = dd.dsu.l + gpregs[Ra];
	PC += 8;
	return;
}
void core::SMULL()
{
	SMP_word Rd = mulTypeInst.Rd;
	SMP_word Rm = mulTypeInst.Rm;
	SMP_word Rn = mulTypeInst.Rn;
	SMP_word Ra = mulTypeInst.Ra;

	bit64 dw;
	bit128 dd;
	int128_t ddoper1;
	int128_t ddoper2;
	int128_t ddres;

	if(mulTypeInst.cond != 0b11111){
		if(mulTypeInst.cond != get_field(FLR, 3, 6)) {
			return;//do Nothink, if conditional is not true
		}
	}
	dw.u = gpregs[Rm];
	ddoper1 = static_cast<int128_t>(dw.s);
	dw.u = gpregs[Rn];
	ddoper2 = static_cast<int128_t>(dw.s);

	ddres = ddoper1 * ddoper2;
	dd.dw = ddres;
	dw.s = dd.dss.h; //to unsigned 128 bits integer
	gpregs[Rd] = dw.u;
	dw.s = dd.dss.l;
	gpregs[Ra] = dw.s;
	PC += 8;
	return;
}
void core::SMLAL()
{
	SMP_word Rd = mulTypeInst.Rd;
	SMP_word Rm = mulTypeInst.Rm;
	SMP_word Rn = mulTypeInst.Rn;
	SMP_word Ra = mulTypeInst.Ra;

	bit64 dw;
	bit128 dd;
	int128_t ddoper1;
	int128_t ddoper2;
	int128_t acc;
	int128_t ddres;

	if(mulTypeInst.cond != 0b11111){
		if(mulTypeInst.cond != get_field(FLR, 3, 6)) {
			return;//do Nothink, if conditional is not true
		}
	}

	dw.u = gpregs[Rd];
	acc = static_cast<int128_t>(dw.s);

	dw.u = gpregs[Rm];
	ddoper1 = static_cast<int128_t>(dw.s);
	dw.u = gpregs[Rn];
	ddoper2 = static_cast<int128_t>(dw.s);

	ddres = ddoper1 * ddoper2 + acc;
	dd.dw = ddres;
	dw.s = dd.dss.h; //to unsigned 128 bits integer
	gpregs[Rd] = dw.u;
	dw.s = dd.dss.l;
	gpregs[Ra] = dw.s;
	PC += 8;
	return;
}

//Mem instractions

void core::STR()
{
	PC += 8;
}
void core::LDR()
{
	PC += 8;
}

void core::STRW()
{
	PC += 8;
}
void core::LDRW()
{
	PC += 8;
}
void core::STRHW()
{
	PC += 8;
}
void core::LDRHW()
{
	PC += 8;
}
void core::STRB()
{
	PC += 8;
}
void core::LDRB()
{
	PC += 8;
}

//Branch instractions

void core::BL()
{

}//Save ip on reg0
void core::BO_REG() 
{

}
void core::BO_IMM() 
{

}
void core::B_REG() 
{

}
void core::B_IMM() 
{

}
void core::RET() 
{

}
void core::XRET() 
{

}

//System instractions

void core::INSY()
{
	PC += 8;
}
void core::IN()
{
	PC += 8;
}

void core::OUTSY()
{
	PC += 8;
}
void core::OUT()
{
	PC += 8;
}

void core::SFL()
{
	PC += 8;
}
void core::LFL()
{
	PC += 8;
}
void core::SMF()
{
	PC += 8;
}
void core::SINT()
{
	PC += 8;
}

void core::BINT()
{
	PC += 8;
}
void core::UINT()
{
	PC += 8;
}
void core::CINT()
{
	PC += 8;
}
void core::INT()
{
	PC += 8;
}

void ALU_instr::flush()
{
	priv = 0;
	cond = 0;
	opcode = 0;
	I = false;
	S = false;
	func = 0;
	Rn = 0;
	Rd = 0;
	Rm = 0;
	Ra = 0;
	imm16 = 0;
	imm32 = 0;
}
void MUL_instr::flush()
{
	priv = 0;
	cond = 0;
	opcode = 0;
	typeOper = false; 
	S = false; 
	TO = false;
	Ra = 0;
	Rn = 0;
	Rd = 0;
	Rm = 0;
	imm32 = 0;
}
void MEM_instr::flush()
{
	priv = 0;
	cond = 0;
	opcode = 0;
	typeOper = false;
	sizeOp = 0;
	Rn = 0;
	Rd = 0;
	scale = 0;
	offset = 0;
}
void CT_instr::flush()
{
	priv = 0; 
	cond = 0;
	opcode = 0;
	typeOper = 0;
	R = 0;
	imm48 = 0;
}
void SYS_instr::flush()
{
	priv = 0;
	cond = 0;
	opcode = 0;
	typeOper = 0;
	port = 0;
	Rn = 0;
	Rd = 0;
	I = false;
	inum = 0;
}