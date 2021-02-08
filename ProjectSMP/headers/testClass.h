#pragma once
#include "core.h"

class debugger
{
public:
	void debugMode(class core &C, int dbgparam, int mode);
	int v;
private:
	void userControl(int mode, int dbgparam, class core &C);
	void printState(class core &C, int dbgparam);
	void printState_alu(class core &C);
	void printState_mul(class core &C);
	void printState_mem(class core &C);
	void printState_ct(class core &C);
	void printState_sys(class core &C);
	void printState_Error(class core &C);
};