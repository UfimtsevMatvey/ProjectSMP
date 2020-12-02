#include "testClass.h"

void tests::testbanchALU()
{
    if(testAND()){
        print("AND error\n");
    }
	if(testEOR()){
        print("EOR error\n");
    }
	if(testORR()){
        print("ORR error\n");
    }
	if(testTST()){
        print("TST error\n");
    }
	if(testTEQ()){
        print("TEQ error\n");
    }
	if(testCMP()){
        print("CMP error\n");
    }
	if(testCMN()){
        print("CMN error\n");
    }
	if(testADD()){
        print("ADD error\n");
    }
	if(testSUB){
        print("SUB error\n");
    }
	if(testADC()){
        print("ADC error\n");
    }
	if(testRSB()){
        print("RSB error\n");
    }
	if(testSBC()){
        print("SBC error\n");
    }
	if(testMVN()){
        print("MVN error\n");
    }
	if(testLSL()){
        print("LSL error\n");
    }
	if(testLSR()){
        print("LSR error\n");
    }
	if(testASR()){
        print("ASR error\n");
    }
	if(testRRX()){
        print("RRX error\n");
    }
	if(testROR()){
        print("ROR error\n");
    }
	if(testBSWP()){
        print("BSWP error\n");
    }
	if(testSWR()){
        print("SWR error\n");
    }
	//SIMD
	if(testUADDPB()){
        print("UADDPB error\n");
    }
	if(testUADDPH()){
        print("UADDPH error\n");
    }
	if(testUADDPW()){
        print("UADDPW error\n");
    }

	if(testSADDPB()){
        print("SADDPB error\n");
    }
	if(testSADDPH()){
        print("SADDPH error\n");
    }
	if(testSADDPW()){
        print("SADDPW error\n");
    }

	if(testVUADDB()){
        print("VUADDB error\n");
    }
	if(testVUADDH()){
        print("VUADDH error\n");
    }
	if(testVSADDB()){
        print("VSADDB error\n");
    }
	if(testVSADDH()){
        print("VSADDH error\n");
    }
}
void tests::testbanchMUL()
{
    if(testMUL()){

    }
	if(testMLA()){

    }
	if(testUMULL()){

    }
	if(testUMLAL()){

    }
	if(testSMULL()){

    }
	if(testSMLAL()){

    }
}
void tests::testbanchMEM();
{
    if(testSTR()){

    }
	if(testLDR()){

    }
	if(testSTRW()){

    }
	if(testLDRW()){

    }
	if(testSTRHW()){

    }
	if(testLDRHW()){

    }
	if(testSTRB()){

    }
	if(testLDRB()){
        
    }
}
void tests::testbanchCT()
{
    if(testBL()){}
	if(testBO_IMM()){}
	if(testBO_REG()){}
	if(testB_IMM()){}
	if(testB_REG()){}
	if(testRET()){}
	if(testXRET()){}
}
void tests::tests::testbanchSYS()
{
    if(testINSY()){}
	if(testIN()){}

	if(testOUTSY()){}
	if(testOUT()){}

	if(testSFL()){}
	if(testLFL()){}
	if(testSMF()){}
	if(testSINT()){}

	if(testBINT()){}
	if(testUINT()){}
	if(testCINT()){}
	if(testINT()){}
}
void tests::memoryTest()
{

}
void tests::testAND()
{

}
void tests::testEOR()
{

}
void tests::testORR()
{

}
void tests::testTST()
{
    
}
void tests::testTEQ()
{
    
}
void tests::testCMP()
{
    
}
void tests::testCMN()
{
    
}
void tests::testADD()
{
    
}
void tests::testSUB()
{
    
}
void tests::testADC()
{
    
}
void tests::testRSB()
{
    
}
void tests::testSBC()
{
    
}
void tests::testMVN()
{
    
}
void tests::testLSL()
{
    
}
void tests::testLSR()
{
    
}
void tests::testASR()
{
    
}
void tests::testRRX()
{
    
}
void tests::testROR()
{
    
}
void tests::testBSWP()
{
    
}
void tests::testSWR()
{
    
}
//SIMD
void tests::testUADDPB()
{
    
}
void tests::testUADDPH()
{
    
}
void tests::testUADDPW()
{
    
}
void tests::testSADDPB()
{
    
}
void tests::testSADDPH()
{
    
}
void tests::testSADDPW()
{
    
}

void tests::testVUADDB()
{
    
}
void tests::testVUADDH()
{
    
}
void tests::testVSADDB()
{
    
}
void tests::testVSADDH()
{
    
}
//Multipli instractions

void tests::testMUL()
{
    
}
void tests::testMLA()
{
    
}
void tests::testUMULL()
{
    
}
void tests::testUMLAL()
{
    
}
void tests::testSMULL()
{
    
}
void tests::testSMLAL()
{
    
}
//Mem instractions

void tests::testSTR()
{
    
}
void tests::testLDR()
{
    
}
void tests::testSTRW()
{
    
}
void tests::testLDRW()
{
    
}
void tests::testSTRHW()
{
    
}
void tests::testLDRHW()
{
    
}

void tests::testSTRB()
{
    
}
void tests::testLDRB()
{
    
}

//Branch instractions

void tests::testBL()
{
    
}//Save ip on reg0
void tests::testBO_IMM()
{
    
}
void tests::testBO_REG()
{
    
}
void tests::testB_IMM()
{
    
}
void tests::testB_REG()
{
    
}
void tests::testRET()
{
    
}
void tests::testXRET()
{
    
}
//System instractions

void tests::testINSY()
{
    
}
void tests::testIN()
{
    
}

void tests::testOUTSY()
{
    
}
void tests::testOUT()
{
    
}

void tests::testSFL()
{
    
}
void tests::testLFL()
{
    
}
void tests::testSMF()
{
    
}
void tests::testSINT()
{
    
}

void tests::testBINT()
{
    
}
void tests::testUINT()
{
    
}
void tests::testCINT()
{
    
}
void tests::testINT()
{
    
}