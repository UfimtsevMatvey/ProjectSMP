#pragma once
#include "def.h"
#include "regf.h"
#include "mem.h"
struct Idescriptor
{
	uint8_t cond;
	uint8_t opcode;
	bool I;
	bool S;
	bool flagR;
	uint8_t func;
	uint8_t R0;
	uint8_t R1;
	uint8_t R2;
	uint8_t R3;
	uint8_t port;

	uint32_t offset;
	uint64_t scale;

	uint8_t imm8;
	uint16_t imm16;
	uint32_t imm32;
	uint64_t imm48;
};
class core
{
public:
	core(SMP_word entry, SMP_word isize, SMP_word dsize, const char* ifile, const char* dfile);
	
	void test_start();

	void start();
	//функция, принимающая инструкцию для декодирований и исполнения
	//Она должна определить какую функцию, и с какими параметрами вызвать.

private:
	void fetchInstr();
	void decodeInst();
	void exec();
	  
	void initMemory(SMP_word isize, SMP_word dsize, const char* fileInst, const char* fileData);

	void reset();
	void flushInstr();
	void load2reg(byte addr, SMP_word& data);
	void store2reg(byte addr, SMP_word data);

	void load2memData(SMP_word addr, SMP_word& data);
	void store2memData(SMP_word addr, SMP_word data);
	void getIntr(SMP_word ip, SMP_word& instr);
	void syncDataFile();

	SMP_word instr;
	Idescriptor descInst;
	regf gpregs;	//Регистры общего назначения
	regf idgers;	//Регистры адресов обработчиков исключений

	reg PC;			//Указатель следующей инструкции

	reg INR; //Регистр флагов прерываний
	reg FLR; //Регистр флагов

	mem instr_mem;
	mem data_mem;

	SMP_word flgs;	//Регистр флагов
	//Остальные регистры, хранящие архитектурное состояние
	//Функции, соответствующие инструкциям.
	//ALU
	void EOR();
	void ORR();
	void TST();
	void TEQ();
	void CMP();
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


	void VADDPB();
	void VADDPH();
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

	void STR();
	void LDR();

	void STRW();
	void LDRW();

	void STRB();
	void LDRB();

	//Branch instractions

	void BL();//Save ip on reg0
	void BO();
	void B();
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