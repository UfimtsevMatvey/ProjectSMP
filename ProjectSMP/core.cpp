
#include "core.h"
#include <iostream>
#include "subfunc.h"
#include "funcCode.h"
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
{//������������� ������.
	instr_mem.Init(isize, fileInst);
	data_mem.Init(dsize, fileData);
}
void core::test_start()
{
	//�������� ���

	//������ / ������ � ����������� ����
	SMP_word data = 0;
	store2reg(32, 346);
	load2reg(32, data);

	//������ / ������ � ������

	for (SMP_word i = 0; i < 8192; i++) {
		store2memData(i, 0xFFFFFFFFFFAA0000 + i);

		load2memData(i, data);
		std::cout << std::hex << data << std::endl;
	}
	syncDataFile();
}
void core::start()
{
	fetchInstr();//������� ��������� ����������
	decodeInst();//������������� ����������
	exec();//���������� ����������
	flushInstr();//������� ����������� ����������
}
void core::decodeInst()
{
	SMP_word tinstr = instr;
	SMP_word opcode;
	opcode = get_field(instr, 2, 6);
	switch(opcode){
		case 0b0001:{
			init_ALU();
			break;
		}
		case 0b0010:{
			init_MUL();
			break;
		}	
		case 0b1010:{
			init_MUL();
			break;
		}
		case 0b0011:{
			init_MEM();
			break;
		}
		case 0b0100:{
			init_CT();
			break;
		}
		case 0b0101:{
			init_SYS(); 
			break;
		}
	}
}

void core::exec() 
{
	SMP_word opcode = get_field(instr, 2, 6);
	switch(opcode){
		case 0b0001:{
			alu_exec();
			break;
		}
		case 0b0010:{
			mul_exec();
			break;
		}	
		case 0b1010:{
			mul_exec();
			break;
		}
		case 0b0011:{
			mem_exec();
			break;
		}
		case 0b0100:{
			ct_exec();
			break;
		}
		case 0b0101:{
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

}
void core::mem_exec()
{

}
void core::ct_exec()
{

}
void core::sys_exec()
{

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
{//������������� ������ � ������ ������.
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
	PC += 8;
}
void core::EOR() 
{
	PC += 8;
}
void core::ORR()
{
	PC += 8;
}
void core::TST()
{
	PC += 8;
}
void core::TEQ()
{
	PC += 8;
}
void core::CMP()
{
	PC += 8;
}
void core::CMN()
{
	PC += 8;
}
void core::ADD()
{
	PC += 8;
}
void core::SUB()
{
	PC += 8;
}
void core::ADC()
{
	PC += 8;
}
void core::RSB()
{
	PC += 8;
}
void core::SBC()
{
	PC += 8;
}
void core::MVN()
{
	PC += 8;
}
void core::LSL()
{
	PC += 8;
}
void core::LSR()
{
	PC += 8;
}
void core::ASR()
{
	PC += 8;
}
void core::RRX()
{
	PC += 8;
}
void core::ROR()
{
	PC += 8;
}
void core::BSWP()
{
	PC += 8;
}
void core::SWR()
{
	PC += 8;
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
void core::BO() 
{

}
void core::B() 
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