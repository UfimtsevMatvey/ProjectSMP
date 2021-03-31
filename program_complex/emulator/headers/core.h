#pragma once

#include "regf.h"
#include "mem.h"
#include "testClass.h"
#include "def.h"
struct ALU_instr
{
	void flush();
	SMP_word priv;
	SMP_word cond;
	SMP_word opcode;
	bool I;
	bool S;//Flag regs
	SMP_word func;
	SMP_word Rn;
	SMP_word Rd;
	SMP_word Rm;
	SMP_word Ra;
	SMP_word imm16;
	SMP_word imm32;
};
struct MUL_instr
{
	void flush();
	SMP_word priv;
	SMP_word cond;
	SMP_word opcode;
	bool typeOper; //Mul or mul with addition
	bool S; //Sign 
	bool TO; //Type of third operand
	SMP_word Ra;
	SMP_word Rn;
	SMP_word Rd;
	SMP_word Rm;
	SMP_word imm32;
};
struct MEM_instr
{
	void flush();
	SMP_word priv;
	SMP_word cond;
	SMP_word opcode;
	bool typeOper; //load or store
	SMP_word sizeOp; //Size of operands
	SMP_word Rn;
	SMP_word Rd;
	SMP_word scale;
	SMP_word offset;
};
struct CT_instr
{
	void flush();
	SMP_word priv;
	SMP_word cond;
	SMP_word opcode;
	SMP_word typeOper; //types of operation
	SMP_word R;//register 
	SMP_word imm48;
};
struct SYS_instr
{
	void flush();
	SMP_word priv;
	SMP_word cond;
	SMP_word opcode;
	SMP_word typeOper; //types of operation
	SMP_word port;
	SMP_word Rn;
	SMP_word Rd;
	bool I; //type of operands
	SMP_word inum; //number of interapt
};
class core
{
	friend class debugger;
public:
	
	SMP_word getPort(int n);
	
	core(SMP_word entry, SMP_word isize, SMP_word dsize, const char* ifile, const char* dfile);
	
	void test_start(SMP_word testInstr);

	int start(int n, int mode);//Number of iteration execute path

private:

	int state;

	SMP_word port0;
	int port0wait;
	int port0ready;

	SMP_word port1;
	int port1wait;
	int port1ready;

	SMP_word port2;
	int port2wait;
	int port2ready;

	SMP_word port3;
	int port3wait;
	int port3ready;

	SMP_word lowBoundAddr;
	SMP_word highBoundAddr;
	

	
	bool cmp_cond(SMP_word cond);
	int getNPC();
	void fetchInstr();
	void decodeInst();
	void init_ALU();
	void init_MUL();
	void init_MEM();
	void init_CT();
	void init_SYS();
	void exec();

	void alu_exec();
	void mul_exec();
	void mem_exec();
	void ct_exec();
	void sys_exec();
	  
	void initMemory(SMP_word isize, SMP_word dsize, const char* fileInst, const char* fileData);

	void reset();
	void flushInstr();
	void load2reg(byte addr, SMP_word& data);
	void store2reg(byte addr, SMP_word data);

	void load2memData(SMP_word addr, SMP_word& data);
	void store2memData(SMP_word addr, SMP_word data);
	void getIntr(SMP_word ip, SMP_word& instr);
	void syncDataFile();

	void setFlag(int n);
	void resetFlag(int n);
	void setINR(int n);

	void resetFLR();
	void resetINR();
	void resetPC();

	SMP_word instr;
	SMP_word typeInstr;

	ALU_instr aluTypeInst;
	MUL_instr mulTypeInst;
	MEM_instr memTypeInst;
	CT_instr ctTypeInst;
	SYS_instr sysTypeInst;

	regf gpregs;//General purpose registers
	regf idgers;//Expeption's handlers address registers

	reg PC;

	reg INR;//Exeption flag register
	reg FLR;//Flag register

	mem instr_mem;
	mem data_mem;

	SMP_word flgs;

	void setALUflag(uint128_t eres, SMP_word oper1, SMP_word oper2, SMP_word care);
	void setALUflag(SMP_word res);

	//ALU
	void AND();
	void EOR();
	void ORR();
	void TST();
	void TEQ();
	void CMP();
	void CMN();
	void ADD();
	void SUB();
	void ADC();
	void RSB();
	void SBC();
	void MVN();
	void LSL();
	void LSR();
	void ASR();
	void RRX();
	void ROR();
	void BSWP();
	void SWR();
	//SIMD

	void UADDPB();
	void UADDPH();
	void UADDPW();

	void SADDPB();
	void SADDPH();
	void SADDPW();


	void VUADDB();
	void VUADDH();
	void VSADDB();
	void VSADDH();

	//Multipli instractions

	void MUL();
	void MLA();
	void UMULL();
	void UMLAL();
	void SMULL();
	void SMLAL();

	//Mem instractions
	void genMEM(SMP_word*);
	void STR();
	void LDR();

	void STRW();
	void LDRW();

	void STRHW();
	void LDRHW();

	void STRB();
	void LDRB();

	//Branch instractions

	void BL();//Save ip on reg0
	void BO_IMM();
	void BO_REG();
	void B_IMM();
	void B_REG();
	void RET();
	void XRET();
	//System instractions

	void INSY();
	void IN();

	void OUTSY();
	void OUT();

	void SFL();
	void LFL();
	void SMF();
	void SINT();

	void BINT();
	void UINT();
	void CINT();
	void INT();

};