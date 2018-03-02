#include <stdio.h>
#include <memory.h>

#include "proj09.h"
#include "proj09_test_commonCode.h"



int main()
{
	CPUMemory cpuState;
	  memset(&cpuState, 0, sizeof(cpuState));

	cpuState.instMemory[0x40] = ADD(T_REG(0), S_REG(3),S_REG(4));

	cpuState.pc = 0x0100;

	// fill in the registers and data memory with 
	int i;
	for (i=1; i<32; i++)
		cpuState.regs[i] = 0x01010101 * i;
	for (i=1; i<sizeof(cpuState.dataMemory); i+=4)
		cpuState.dataMemory[i/4] = 0x00010001 * i;

	execute_singleCycleCPU(&cpuState, 1);
	return 0;
}


