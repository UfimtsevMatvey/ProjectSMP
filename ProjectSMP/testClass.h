class tests
{
public:
    void testbanchALU();
    void testbanchMUL();
    void testbanchCT();
    void testbanchMEM();
    void testbanchSYS();
    void memoryTest();
private:
    bool testAND();
	bool testEOR();
	bool testORR();
	bool testTST();
	bool testTEQ();
	bool testCMP();
	bool testCMN();
	bool testADD();
	bool testSUB();
	bool testADC();
	bool testRSB();
	bool testSBC();
	bool testMVN();
	bool testLSL();
	bool testLSR();
	bool testASR();
	bool testRRX();
	bool testROR();
	bool testBSWP();
	bool testSWR();
	//SIMD

	bool testUADDPB();
	bool testUADDPH();
	bool testUADDPW();

	bool testSADDPB();
	bool testSADDPH();
	bool testSADDPW();


	bool testVUADDB();
	bool testVUADDH();
	bool testVSADDB();
	bool testVSADDH();

	//Multipli instractions

	bool testMUL();
	bool testMLA();
	bool testUMULL();
	bool testUMLAL();
	bool testSMULL();
	bool testSMLAL();

	//Mem instractions

	bool testSTR();
	bool testLDR();

	bool testSTRW();
	bool testLDRW();

	bool testSTRHW();
	bool testLDRHW();

	bool testSTRB();
	bool testLDRB();

	//Branch instractions

	bool testBL();//Save ip on reg0
	bool testBO_IMM();
	bool testBO_REG();
	bool testB_IMM();
	bool testB_REG();
	bool testRET();
	bool testXRET();
	//System instractions

	bool testINSY();
	bool testIN();

	bool testOUTSY();
	bool testOUT();

	bool testSFL();
	bool testLFL();
	bool testSMF();
	bool testSINT();

	bool testBINT();
	bool testUINT();
	bool testCINT();
	bool testINT();
};