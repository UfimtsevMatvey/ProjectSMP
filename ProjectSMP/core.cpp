#include "def.h"
#include "core.h"
#include <iostream>

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
void core::test_start()
{
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
	flushInstr();//Очистка дескриптора инструкции
}
void core::decodeInst()
{

}
void core::exec() 
{

}
void core::flushInstr() 
{
	descInst.cond = 0;
	descInst.flagR = false;
	descInst.func = 0;
	descInst.I = false;
	descInst.imm16 = 0;
	descInst.imm32 = 0;
	descInst.imm48 = 0;
	descInst.imm8 = 0;
	descInst.offset = 0;
	descInst.scale = 0;
	descInst.opcode = 0;
	descInst.port = 0;
	descInst.R0 = 0;
	descInst.R1 = 0;
	descInst.R2 = 0;
	descInst.R3 = 0;
	descInst.S = false;
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