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
	PC = entry;
	initMemory(isize, dsize, ifile, dfile);
}
void core::initMemory(SMP_word isize, SMP_word dsize, const char* fileInst, const char* fileData)
{//Инициализация памяти.
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
	}
	//Тестовый код

	//Чтение / запись в регистровый файл
	SMP_word data = 0;
	store2reg(32, 346);
	load2reg(32, data);

	//Чтение / запись в память

	for (SMP_word i = 0; i < 8192; i++) {
		store2memData(i, 0xFFFFFFFFFFAA0000 + i);

		load2memData(i, data);
		std::cout << std::hex << data << std::endl;
	}
	syncDataFile();
}
void core::start()
{
	fetchInstr();//Выборка следующей инструкции
	decodeInst();//Декодирование инструкции
	exec();//Исполнение инструкции
	flushInstr();//Очистка дескрипторов инструкции
}
void core::decodeInst()
{
	SMP_word tinstr = instr;
	SMP_word opcode;
	opcode = get_field(instr, 2, 6);
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
	SMP_word opcode = get_field(instr, 2, 6);
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
		case FUNC_AND: AND(); break;
		case FUNC_EOR: EOR(); break;
		case FUNC_ORR: ORR(); break;
		case FUNC_TST: TST(); break;
		case FUNC_TEQ: TEQ(); break;
		case FUNC_CMP: CMP(); break; 
		case FUNC_CMN: CMN(); break;
		case FUNC_ADD: ADD(); break;
		case FUNC_SUB: SUB(); break;
		case FUNC_ADC: ADC(); break;
		case FUNC_RSB: RSB(); break;
		case FUNC_SBC: SBC(); break;
		case FUNC_MVN: MVN(); break;
		case FUNC_LSL: LSL(); break;
		case FUNC_ASR: ASR(); break;
		case FUNC_RRX: RRX(); break;
		case FUNC_ROR: ROR(); break;
		case FUNC_BSWP: BSWP(); break;
		case FUNC_SWR: SWR(); break;
		case FUNC_UADDPB: UADDPB(); break;
		case FUNC_UADDPH: UADDPH(); break;
		case FUNC_UADDPW: UADDPW(); break;
		case FUNC_SADDPB: SADDPB(); break;
		case FUNC_SADDPH: SADDPH(); break;
		case FUNC_SADDPW: SADDPW(); break;
		case FUNC_VADDPB: VADDPB(); break;
		case FUNC_VADDPH: VADDPH(); break;
		case FUNC_VSADDB: VSADDB(); break;
		case FUNC_VSADDH: VSADDH(); break;
	}
}
void core::mul_exec()
{
	if(mulTypeInst.typeOper){
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
		if(mulTypeInst.S){
			SMLAL();
		}
		else{
			UMLAL();
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


	int64_t sres = bres.s;
	int64_t soper1 = boper1.s;
	int64_t soper2 = boper2.s;
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
	if(ssum > (1 << 64)){
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
	temp = temp << n;
	FLR = FLR | temp;
}

void core::resetFlag(int n)
{
	SMP_word temp = 1;
	temp = temp << n;
	temp = ~temp;
	FLR = FLR & temp;
}

void core::resetFLR()
{
	FLR = 0;
}

void core::flushInstr() 
{
}
void core::reset() 
{
	gpregs.flush();
	idgers.flush();
	FLR = 0;
	INR = 0;
	flushInstr();
	PC = 0;
}
void core::syncDataFile() 
{//Синхронизация памяти с файлом памяти.
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

//How to use functors???
void core::templateALU()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper2;
	SMP_word res;

	if(aluTypeInst.cond != get_field(FLR, 3, 6)) //do Nothink, if conditional is not true
		return;

	if(aluTypeInst.I){
		oper2 = gpregs[aluTypeInst.Rm];
	}
	else{
		oper2 = aluTypeInst.imm32;
	}
	res = gpregs[Rn] + oper2;
	gpregs[Rd] = res;
	if(aluTypeInst.S){
		if(res == 0)	setFlag(Z);//Z - flag
		else			resetFlag(Z);
		if(res >= 0) 	setFlag(C);
		else 			resetFlag(C);
		resetFlag(N);
		resetFlag(V);
	}
	PC += 8;
	return;
	
}


void core::AND() 
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] + oper2;
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
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
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
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] & oper2;
	gpregs[Rd] = res;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::TST()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] & oper2;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::TEQ()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper2;
	SMP_word res;
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	res = gpregs[Rn] ^ oper2;
	if(aluTypeInst.S)	setLALUflag(res);
	PC += 8;
	return;
}
void core::CMP()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rd];
	SMP_word oper2;
	SMP_word addoper2;
	bit64 bres;
	bit64 boper1;
	bit64 boper2;

	int64_t soper1;
	int64_t soper2;
	int64_t sres;
	SMP_word res;
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

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
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word oper1 = gpregs[Rd];
	SMP_word oper2;

	bit64 bres;
	bit64 boper1;
	bit64 boper2;

	int64_t soper1;
	int64_t soper2;
	int64_t sres;

	SMP_word res;
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

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

	bit64 bres;
	bit64 boper1;
	bit64 boper2;

	int64_t soper1;
	int64_t soper2;
	int64_t sres;

	SMP_word res;
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

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

	bit64 bres;
	bit64 boper1;
	bit64 boper2;

	int64_t soper1;
	int64_t soper2;
	int64_t sres;

	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

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

	bit64 bres;
	bit64 boper1;
	bit64 boper2;
	
	uint64_t soper1;
	uint64_t soper2;
	uint64_t sres;

	SMP_word res;
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
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
	SMP_word oper2;
	SMP_word addoper2;
	SMP_word care;
	SMP_word res;

	bit64 bres;
	bit64 boper1;
	bit64 boper2;

	uint64_t soper1;
	uint64_t soper2;
	uint64_t sres;

	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

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
	SMP_word oper2;
	SMP_word addoper2;
	SMP_word care = get_bit(FLR, 3) ? static_cast<uint64_t>(1) : static_cast<uint64_t>(0);

	bit64 bres;
	bit64 boper1;
	bit64 boper2;

	int64_t sres;
	int64_t soper1;
	int64_t soper2;

	SMP_word res;
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
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
	SMP_word care = get_bit(FLR, 3) ? static_cast<uint64_t>(1) : static_cast<uint64_t>(0);
	bit64 boper1;
	boper1.u = oper1;
	uint64_t soper1 = boper1.s;

	uint64_t sres;
	SMP_word res;
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
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
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
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
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
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;
	
	boper1.u = oper1;
	boper2.u = oper2;
	
	soper1 = boper1.s;
	soper2 = boper2.s;

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
	SMP_word care = get_bit(FLR, 3) ? static_cast<uint64_t>(1) : static_cast<uint64_t>(0);
	SMP_word res;

	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	SMP_word temp1 = get_bit(FLR, 3) << 63;
	SMP_word temp2;
	setFlag(C);
	for(int i = 0; i < oper2; i++){
		temp2 = get_bit(res, 0) << 63;
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
	SMP_word care = get_bit(FLR, 3) ? static_cast<uint64_t>(1) : static_cast<uint64_t>(0);
	SMP_word res;

	bit64 bres;
	bit64 boper1;
	bit64 boper2;

	int64_t sres;
	int64_t soper1;
	int64_t soper2;

	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	if(aluTypeInst.I)	oper2 = gpregs[aluTypeInst.Rm];
	else 				oper2 = aluTypeInst.imm32;

	bres.u = res;
	boper1.u = oper1;
	boper2.u = oper2;

	sres = bres.s;
	soper1 = boper1.s;
	soper2 = boper2.s;

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
	SMP_word res;
	SMP_word oper = gpregs[Rd];
	if(aluTypeInst.cond != get_field(FLR, 3, 6)) return;//do Nothink, if conditional is not true
	__asm__ ("bswap  %%rax"
                             :"=a"(oper)
                             :"a"(res)
                             );
	PC += 8;
	return;
}
void core::SWR()
{
	SMP_word Rd = aluTypeInst.Rd;
	SMP_word Rn = aluTypeInst.Rn;
	SMP_word res;
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
	PC += 8;
}
void core::UADDPH()
{
	PC += 8;
}
void core::UADDPW()
{
	PC += 8;
}

void core::SADDPB()
{
	PC += 8;
}
void core::SADDPH()
{
	PC += 8;
}
void core::SADDPW()
{
	PC += 8;
}


void core::VADDPB()
{
	PC += 8;
}
void core::VADDPH()
{
	PC += 8;
}
void core::VSADDB()
{
	PC += 8;
}
void core::VSADDH()
{
	PC += 8;
}

//Multipli instractions

void core::MUL()
{
	PC += 8;
}
void core::MLA()
{
	PC += 8;
}
void core::UMULL()
{
	PC += 8;
}
void core::UMLAL()
{
	PC += 8;
}
void core::SMULL()
{
	PC += 8;
}
void core::SMLAL()
{
	PC += 8;
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

