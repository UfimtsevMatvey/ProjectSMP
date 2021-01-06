//#pragma once
#include "core.h"
#include <iostream>
#include "subfunc.h"
#include "funcCode.h"
#include "opcode.h"
#include "memSizeOper.h"
#include "ctCode.h"
#include "sysCode.h"
#include "flagNum.h"
#include "condNum.h"
#include "errorCode.h"
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
void core::start(int n)
{
	int i = 0;
	while(i < n){
		PC = preFetch();
		fetchInstr();
		decodeInst();
		exec();
		flushInstr();
		i++;
	}
}
int core::preFetch()
{
	if(INR == 0) return PC;
	else switch(INR){
		case 0x1: return idgers[0];
		case 0x2: return idgers[1];
		case 0x4: return idgers[2];
		case 0x8: return idgers[3];
		case 0x10: return idgers[4];
		case 0x20: return idgers[5];
		case 0x40: return idgers[6];
		case 0x80: return idgers[7];
		case 0x100: return idgers[8];
		case 0x200: return idgers[9];
		case 0x400: return idgers[10];
		case 0x800: return idgers[11];
		case 0x1000: return idgers[12];
		case 0x2000: return idgers[13];
		case 0x4000: return idgers[14];
		case 0x8000: return idgers[15];
		case 0x10000: return idgers[16];
		case 0x20000: return idgers[17];
		case 0x40000: return idgers[18];
		case 0x80000: return idgers[19];
		case 0x100000: return idgers[20];
		case 0x200000: return idgers[21];
		case 0x400000: return idgers[22];
		case 0x800000: return idgers[23];
		case 0x1000000: return idgers[24];
		case 0x2000000: return idgers[25];
		case 0x4000000: return idgers[26];
		case 0x8000000: return idgers[27];
		case 0x10000000: return idgers[28];
		case 0x20000000: return idgers[29];
		case 0x40000000: return idgers[30];
		case 0x80000000: return idgers[31];
		case 0x100000000: return idgers[32];
		case 0x200000000: return idgers[33];
		case 0x400000000: return idgers[34];
		case 0x800000000: return idgers[35];
		case 0x1000000000: return idgers[36];
		case 0x2000000000: return idgers[37];
		case 0x4000000000: return idgers[38];
		case 0x8000000000: return idgers[39];
		case 0x10000000000: return idgers[40];
		case 0x20000000000: return idgers[41];
		case 0x40000000000: return idgers[42];
		case 0x80000000000: return idgers[43];
		case 0x100000000000: return idgers[44];
		case 0x200000000000: return idgers[45];
		case 0x400000000000: return idgers[46];
		case 0x800000000000: return idgers[47];
		case 0x1000000000000: return idgers[48];
		case 0x2000000000000: return idgers[49];
		case 0x4000000000000: return idgers[50];
		case 0x8000000000000: return idgers[51];
		case 0x10000000000000: return idgers[52];
		case 0x20000000000000: return idgers[53];
		case 0x40000000000000: return idgers[54];
		case 0x80000000000000: return idgers[55];
		case 0x100000000000000: return idgers[56];
		case 0x200000000000000: return idgers[57];
		case 0x400000000000000: return idgers[58];
		case 0x800000000000000: return idgers[59];
		case 0x1000000000000000: return idgers[60];
		case 0x2000000000000000: return idgers[61];
		case 0x4000000000000000: return idgers[62];
		case 0x8000000000000000: return idgers[63];
		default: return 0;	
	}
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
void core::setALUflag(uint128_t eres, SMP_word oper1, SMP_word oper2, SMP_word care)
{
	bit128 t;
	SMP_word res;
	SMP_word poper1;
	SMP_word poper2;
	int64_t sres;
	bool oV;
	bool Cr;
	bool Y; //Care to sign position 
	//Convert to SMP_word
	t.dw = eres;
	res = t.dsu.l;
	sres = t.dss.l;
	Cr = ((0x1000000000000000 & eres) != 0);

	poper1 = 0x7FFFFFFFFFFFFFFF & oper1;
	poper2 = 0x7FFFFFFFFFFFFFFF & oper2;

	Y = ((poper1 + poper2 + care) & 0x8000000000000000) != 0;
	oV = Y ^ Cr;
	if(res == 0) 	setFlag(Z);
	else 			resetFlag(Z);
	if(sres < 0)	setFlag(N);
	else			resetFlag(N);
	if(Cr)			setFlag(C);
	else			resetFlag(C);
	if(oV) 			setFlag(V);
	else			resetFlag(V);
}

void core::setALUflag(SMP_word res)
{
	if(res == 0)		setFlag(Z);//Z - flag
	else				resetFlag(Z);
}
void core::setFlag(int n)
{
	SMP_word temp = 1;
	temp = temp << (8 * sizeof(SMP_word) - n - 1);
	FLR = FLR | temp;
}

void core::resetFlag(int n)
{
	SMP_word temp = 1;
	temp = temp << (8 * sizeof(SMP_word) - n - 1);
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] & oper2;
	gpregs[Rd] = res;
	if(aluTypeInst.S)	setALUflag(res);
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] ^ oper2;
	gpregs[Rd] = res;
	if(aluTypeInst.S)	setALUflag(res);
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] | oper2;
	gpregs[Rd] = res;
	if(aluTypeInst.S)	setALUflag(res);
	PC += 8;
	return;
}
void core::TST()
{
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] & oper2;
	if(aluTypeInst.S)	setALUflag(res);
	PC += 8;
	return;
}
void core::TEQ()
{
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] ^ oper2;
	if(aluTypeInst.S)	setALUflag(res);
	PC += 8;
	return;
}
void core::CMP()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word oper1 = gpregs[Rd];
	SMP_word oper2;
	SMP_word addoper2;
	uint128_t eres;
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	addoper2 = ~oper2 + static_cast<uint64_t>(1);
	eres = static_cast<uint128_t>(oper1) + static_cast<uint128_t>(addoper2);
	if(aluTypeInst.S)	setALUflag(eres, oper1, addoper2, 0);
	PC += 8;
	return;
}
void core::CMN()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word oper1 = gpregs[Rd];
	SMP_word oper2;
	uint128_t eres;
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	eres = static_cast<uint128_t>(oper1) + static_cast<uint128_t>(oper2);
	if(aluTypeInst.S)	setALUflag(eres, oper1, oper2, 0);
	PC += 8;
	return;
}
void core::ADD()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;

	SMP_word res;
	uint128_t eres;
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = oper1 + oper2;
	eres = static_cast<uint128_t>(oper1) + static_cast<uint128_t>(oper2);
	if(aluTypeInst.S)	setALUflag(eres, oper1, oper2, 0);
	gpregs[Rd] = res;
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
	uint128_t eres;
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	addoper2 = ~oper2 + static_cast<uint64_t>(1);
	res = oper1 + addoper2;
	eres = static_cast<uint128_t>(oper1) + static_cast<uint128_t>(addoper2);
	if(aluTypeInst.S)	setALUflag(eres, oper1, addoper2, 0);
	gpregs[Rd] = res;
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

	SMP_word res;
	uint128_t eres;
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	res = oper1 + oper2 + care;
	eres = static_cast<uint128_t>(oper1) + static_cast<uint128_t>(oper2) + static_cast<uint128_t>(care); 
	if(aluTypeInst.S)	setALUflag(eres, oper1, oper2, care);
	gpregs[Rd] = res;
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
	uint128_t eres;
	if(aluTypeInst.cond != 0b1111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	addoper2 = ~oper1 + static_cast<uint64_t>(1) + care;
	res = oper2 + addoper2;
	eres = static_cast<uint128_t>(oper1) + static_cast<uint128_t>(addoper2);
	if(aluTypeInst.S)	setALUflag(eres, oper1, addoper2, 0);
	gpregs[Rd] = res;
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

	SMP_word res;
	uint128_t eres;
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	addoper2 = ~oper2 + static_cast<uint64_t>(1) + care;
	res = oper1 + addoper2;
	eres = static_cast<uint128_t>(oper1) + static_cast<uint128_t>(addoper2);
	if(aluTypeInst.S)	setALUflag(eres, oper1, addoper2, 0);
	gpregs[Rd] = res;
	PC += 8;
	return;
}
void core::MVN()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];

	SMP_word res;
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	res = ~oper1;
	gpregs[Rd] = res;
	if(aluTypeInst.S)	setALUflag(res);
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = oper1 << oper2;
	if(aluTypeInst.S)	setALUflag(res);
	gpregs[Rd] = res;
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = oper1 >> oper2;
	if(aluTypeInst.S)	setALUflag(res);
	gpregs[Rd] = res;
	PC += 8;
	return;
}
void core::ASR()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;
	//SMP_word care = get_bit(FLR, 3) ? static_cast<uint64_t>(1) : static_cast<uint64_t>(0);

	bit64 bres;
	bit64 boper1;
	bit64 boper2;

	int64_t sres;
	int64_t soper1;
	int64_t soper2;
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
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
		setALUflag(sres);
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
	SMP_word Cf;
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	oper2 = oper2 & 0x000000000000003F;//Only 6 bit in shifh operand

	Cf = (get_bit(FLR, 3) ? static_cast<uint64_t>(1) : static_cast<uint64_t>(0));
	// rewrite with asm inline
	asm volatile(
		"MOV r10, %2	\n\t"
		"MOV r11, %3	\n\t"
		"MOV r12, %4	\n\t"
		"RCR r12, 1		\n\t"		//Set CF for correct executing RCR instraction
		"MOV rcx, r11	\n\t"
		"_nRRX:			\n\t"
    	"RCR r10, 1		\n\t"
		"LOOP _nRRX		\n\t"
		"XOR r12, r12	\n\t"
		"RCL r12, 1		\n\t" 		//Get new value for Cf flag
		"MOV %0, r10	\n\t"
		"MOV %1, r12	\n\t"
   		: "=r" (res), "=r" (Cf)
   		: "r" (oper1), "r" (oper2), "r" (Cf));

	if(Cf == 1) setFlag(C);
	else 		resetFlag(C);
	gpregs[Rd] = res;
	setALUflag(res);
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
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	oper2 = oper2 & 0x000000000000003F;//Only 6 bit in shifh operand
	// rewrite with asm inline
	asm volatile(
		"MOV r10, %1	\n\t"
		"MOV r11, %2	\n\t"
		"MOV rcx, r11	\n\t"
		"_nROR:			\n\t"
    	"ROR r10, 1		\n\t"
		"LOOP _nROR		\n\t"
		"MOV %0, r10	\n\t"
   		: "=r" (res)
   		: "r" (oper1), "r" (oper2));
	setALUflag(res);
	gpregs[Rd] = res;
	PC += 8;
	return;
}
void core::BSWP()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word res = 0;
	SMP_word oper = gpregs[Rd];
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
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
	setALUflag(res);
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
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
	setALUflag(res);
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
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
	setALUflag(res);
	PC += 8;
	return;
}

void core::SADDPB()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rn];
	SMP_word oper2;

	bit64 temp;

	int64_t soper1;
	int64_t soper2;
	int64_t sres;

	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	if(!aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	temp.u = oper1;
	soper1 = temp.s;
	temp.u = oper2;
	soper2 = temp.s;
	asm volatile(
		"MOVD mm0, %1 				\n\t"
		"MOVD mm1, %2 				\n\t"
    	"PADDSB mm1, mm0	 		\n\t"
		"MOVQ %0, mm1				\n\t"
    	: "=r" (sres)
    	: "r" (soper1), "r" (soper2)); 

	temp.s = sres;
	gpregs[Rd] = temp.u;
	setALUflag(temp.u);
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
	if(aluTypeInst.cond != 0b11111)
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
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
	setALUflag(sres);
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	
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
	setALUflag(res.h | res.l);
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	
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
	setALUflag(res.h | res.l);
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	
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
	setALUflag(res.h | res.l);
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
		if(!cmp_cond(aluTypeInst.cond)) return;//do Nothink, if conditional is not true
	
	asm volatile(
		"MOVQ xmm2, %2				\n\t"
		"MOVQ xmm3, %3				\n\t"
		"VPBROADCASTW xmm0, xmm2	\n \t"
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
	setALUflag(res.h | res.l);
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
		if(!cmp_cond(mulTypeInst.cond)) {
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
	setALUflag(res);
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
		if(!cmp_cond(mulTypeInst.cond)) {
			return;//do Nothink, if conditional is not true
		}
	}
	oper1 = gpregs[Rn];
	oper2 = gpregs[Rm];
	operA = gpregs[Ra];
	res = oper1 * oper2 + operA;
	gpregs[Rd] = res;
	setALUflag(res);
	PC += 8;
	return;
}
void core::UMULL()
{
	SMP_word Rd = mulTypeInst.Rd;
	//SMP_word Rn = mulTypeInst.Rn;
	SMP_word Rm = mulTypeInst.Rm;
	SMP_word Ra = mulTypeInst.Ra;

	bit128 dd;
	uint128_t ddoper1;
	uint128_t ddoper2;
	uint128_t ddres;

	if(mulTypeInst.cond != 0b11111){
		if(!cmp_cond(mulTypeInst.cond)) {
			return;//do Nothink, if conditional is not true
		}
	}
	ddoper1 = static_cast<uint128_t>(gpregs[Rm]);
	ddoper2 = static_cast<uint128_t>(gpregs[Ra]);
	ddres = ddoper1 * ddoper2;
	//cast to 2dword
	dd.dw = ddres;
	gpregs[Rd] = dd.dsu.h;
	gpregs[Rd] = dd.dsu.l;
	setALUflag(dd.dsu.h | dd.dsu.l);
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
	uint128_t ddoperA;
	uint128_t ddres;

	if(mulTypeInst.cond != 0b11111){
		if(!cmp_cond(mulTypeInst.cond)) {
			return;//do Nothink, if conditional is not true
		}
	}
	dd.dsu.h = gpregs[Rd];
	dd.dsu.l = gpregs[Ra];
	ddoperA = dd.dw;

	ddoper1 = static_cast<uint128_t>(gpregs[Rn]);
	ddoper2 = static_cast<uint128_t>(gpregs[Rm]);
	ddres = ddoper1 * ddoper2 + ddoperA;
	dd.dw = ddres;
	gpregs[Rd] = dd.dsu.h;
	gpregs[Ra] = dd.dsu.l;
	setALUflag(dd.dsu.h | dd.dsu.l);
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
		if(!cmp_cond(mulTypeInst.cond)) {
			return;//do Nothink, if conditional is not true
		}
	}
	//Sign cast (because sign extention)
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
	setALUflag(dw.s);
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
	int128_t ddoperA;
	int128_t ddres;

	if(mulTypeInst.cond != 0b11111){
		if(!cmp_cond(mulTypeInst.cond)) {
			return;//do Nothink, if conditional is not true
		}
	}

	dw.u = gpregs[Rd];
	ddoperA = static_cast<int128_t>(dw.s);

	dw.u = gpregs[Rm];
	ddoper1 = static_cast<int128_t>(dw.s);
	dw.u = gpregs[Rn];
	ddoper2 = static_cast<int128_t>(dw.s);

	ddres = ddoper1 * ddoper2 + ddoperA;
	dd.dw = ddres;
	dw.s = dd.dss.h; //to unsigned 128 bits integer
	gpregs[Rd] = dw.u;
	dw.s = dd.dss.l;
	gpregs[Ra] = dw.s;
	setALUflag(dw.s);
	PC += 8;
	return;
}

//Mem instractions
/*General memory operation.
	retValueMask using for masking data from/for memory, and return loaded value
*/
void core::genMEM(SMP_word* retValueMask)
{
	SMP_word Rd = memTypeInst.Rd;
	SMP_word Rn = memTypeInst.Rn;

	SMP_word offset = memTypeInst.offset;
	SMP_word scale = memTypeInst.scale;
	byte addr = static_cast<byte>(offset + scale * gpregs[Rn]);
	SMP_word value = gpregs[Rd];
	if(memTypeInst.cond != 0b11111){
		if(!cmp_cond(memTypeInst.cond)) {
			return;//do Nothink, if conditional is not true
		}
	}
	if(memTypeInst.typeOper) {
		load2reg(addr, value);
		*retValueMask = value & *retValueMask;
		return;
	}
	else{
		value = value & *retValueMask;
		store2reg(addr, value);
		return;
	}	
}
void core::STR()
{
	SMP_word temp = MASK64;
	genMEM(&temp);
	PC += 8;
}
void core::LDR()
{
	SMP_word temp = MASK64;
	genMEM(&temp);
	gpregs[memTypeInst.Rd] = temp;
	PC += 8;
}

void core::STRW()
{
	SMP_word temp = MASK32;
	genMEM(&temp);
	PC += 8;
}
void core::LDRW()
{
	SMP_word temp = MASK32;
	genMEM(&temp);
	gpregs[memTypeInst.Rd] = temp;
	PC += 8;
}
void core::STRHW()
{
	SMP_word temp = MASK16;
	genMEM(&temp);
	PC += 8;
}
void core::LDRHW()
{
	SMP_word temp = MASK16;
	genMEM(&temp);
	gpregs[memTypeInst.Rd] = temp;
	PC += 8;
}
void core::STRB()
{
	SMP_word temp = MASK8;
	genMEM(&temp);
	PC += 8;
}
void core::LDRB()
{
	SMP_word temp = MASK8;
	genMEM(&temp);
	gpregs[memTypeInst.Rd] = temp;
	PC += 8;
}

//Branch instractions

void core::BL()
{
	SMP_word imm = ctTypeInst.imm48;
	imm = imm & (0xFFFFFFFF);
	imm = imm << 8;
	gpregs[1] = PC + 8;
	PC = PC + 8 + imm;
}//Save ip on reg0
void core::BO_REG() 
{
	SMP_word Rd = ctTypeInst.R;
	PC = PC + 8 + gpregs[Rd];
}
void core::BO_IMM() 
{
	SMP_word imm = ctTypeInst.imm48;
	imm = imm & (0xFFFFFFFF);
	PC = PC + 8 + (imm << 8);
}
void core::B_REG() 
{
	SMP_word Rd = ctTypeInst.R;
	PC = gpregs[Rd];
}
void core::B_IMM() 
{
	SMP_word imm = ctTypeInst.imm48;
	imm = imm & (0xFFFFFFFF);
	PC = imm << 8;
}
void core::RET() 
{
	PC = gpregs[1];
}
void core::XRET() 
{
	PC = gpregs[2];
}
//System instractions

void core::INSY()
{
	SMP_word Nport = sysTypeInst.port;
	SMP_word Rs = sysTypeInst.Rd;
	switch(Nport){
		case 0: port0 = gpregs[Rs];
				port0wait = 1;
				while(port0wait == 1);
				break;
		case 1: port1 = gpregs[Rs];
				port1wait = 1;
				while(port1wait == 1);
				break;
		case 2: port2 = gpregs[Rs];
				port2wait = 1;
				while(port2wait == 1);
				break;
		case 3: port3 = gpregs[Rs];
				port3wait = 1;
				while(port3wait == 1);
				break;
		default: ErrorCode = ILLEGALPORT; break;
	}
	PC += 8;
}
void core::IN()
{
	SMP_word Nport = sysTypeInst.port;
	SMP_word Rs = sysTypeInst.Rd;
	switch(Nport){
		case 0: port0 = gpregs[Rs];
				break;
		case 1: port1 = gpregs[Rs];
				break;
		case 2: port2 = gpregs[Rs];
				break;
		case 3: port3 = gpregs[Rs];
				break;
		default: ErrorCode = ILLEGALPORT; break;
	}
	PC += 8;
}
void core::OUTSY()
{	
	SMP_word Nport = sysTypeInst.port;
	SMP_word Rd = sysTypeInst.Rd;
	switch(Nport){
		case 0: while(port0ready == 0);
				gpregs[Rd] = port0;
				break;
		case 1: while(port1ready == 0);
				gpregs[Rd] = port1;
				break;
		case 2: while(port2ready == 0);
				gpregs[Rd] = port2;
				break;
		case 3: while(port3ready == 0);
				gpregs[Rd] = port3;
				break;
		default: ErrorCode = ILLEGALPORT; break;
	}
	PC += 8;
}	
void core::OUT()
{	
	SMP_word Nport = sysTypeInst.port;
	SMP_word Rd = sysTypeInst.Rd;
	switch(Nport){
		case 0: if(port0ready == 0){
					setFlag(INVALIDVALUE);
					break;
				}
				gpregs[Rd] = port0;
				break;
		case 1: if(port1ready == 0){
					setFlag(INVALIDVALUE);
					break;
				}
				gpregs[Rd] = port1;
				break;
		case 2: if(port2ready == 0){
					setFlag(INVALIDVALUE);
					break;
				}
				gpregs[Rd] = port2;
				break;
		case 3: if(port3ready == 0){
					setFlag(INVALIDVALUE);
					break;
				}
				gpregs[Rd] = port3;
				break;
		default: ErrorCode = ILLEGALPORT; break;
	}
	PC += 8;
}

void core::SFL()
{
	gpregs[sysTypeInst.Rd] = FLR;
	PC += 8;
}
void core::LFL()
{
	FLR = gpregs[sysTypeInst.Rd];
	PC += 8;
}
void core::SMF()
{
	lowAddr = gpregs[sysTypeInst.Rd];
	highAddr = gpregs[sysTypeInst.Rn];
	PC += 8;
}
void core::SINT()
{
	idgers[sysTypeInst.inum] = gpregs[sysTypeInst.Rd];
	PC += 8;
}

void core::BINT()
{
	setFlag(BLOCKINTR);
	PC += 8;
}
void core::UINT()
{
	resetFlag(BLOCKINTR);
	PC += 8;
}
void core::CINT()
{
	INR = 0;
	PC += 8;
}
void core::INT()
{
	SMP_word temp = 1;
	temp = temp << (8 * sizeof(SMP_word) - sysTypeInst.inum - 1);
	INR = INR | temp;
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
bool core::cmp_cond(SMP_word cond)
{
	bool N_fl = get_bit(FLR, N);
	bool Z_fl = get_bit(FLR, Z);
	bool C_fl = get_bit(FLR, C);
	bool V_fl = get_bit(FLR, V);
	SMP_word SignificantBits = cond & 0x0F;
	switch(SignificantBits){
		case EQ:	return Z_fl;
		case NE:	return !Z_fl;
		case CS:	return C_fl;
		case CC:	return !C_fl;
		case MI:	return N_fl;
		case PL:	return !N_fl;
		case VS:	return V_fl;
		case VC:	return !V_fl;
		case HI:	return (!Z_fl) && C_fl;	
		case LS:	return Z_fl || (!C_fl);
		case GE:	return !(N_fl ^ V_fl);
		case LT:	return N_fl ^ V_fl;
		case GT:	return (!Z_fl) && (!(N_fl ^ V_fl));
		case LE:	return Z_fl || (N_fl ^ V_fl);
		default: 	return false;
	}
}