#pragma once
#include "core.h"

class debugger
{
public:
	void debugMode(class core &C);
	void debugMode();
	int v;
private:
	void printState(class core &C);
};