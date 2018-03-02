#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "proj11.h"
#include "proj11_test_commonCode.h"


int main()
{
	int i;

#define COUNT 25
	IF_ID  ifid [COUNT];
	ID_EX  idex [COUNT];
	EX_MEM exmem[COUNT];
	MEM_WB memwb[COUNT];

#define MEM_SIZE (16*1024)
	WORD dataMemory[MEM_SIZE];

	/* this contains all of the instructions from tests 02 and 03 */
	ifid[ 0].instruction = ADD(S_REG(0),  S_REG(1), S_REG(2));
	ifid[ 1].instruction = SUB(S_REG(3),  S_REG(4), S_REG(5));
	ifid[ 2].instruction = ADDI(T_REG(2), T_REG(3), -1);
	ifid[ 3].instruction = ADDI(T_REG(4), T_REG(5), 16);
	ifid[ 4].instruction =  ADDU( 1,  0, 2);
	ifid[ 5].instruction =  SUBU( 3,  4, 5);
	ifid[ 6].instruction = ADDIU( 6,  7,0x1234);
	ifid[ 7].instruction =   AND( 9, 10,11);
	ifid[ 8].instruction =    OR(12, 13,14);
	ifid[ 9].instruction =  ANDI(15, 16,0x5678);
	ifid[10].instruction =   ORI(18, 19,0x9abc);
	ifid[11].instruction =   SLT(21, 22,23);
	ifid[12].instruction =  SLTI(24, 25,-1);
	ifid[13].instruction =    LW(26,  0,104);
	ifid[14].instruction =    SW(29,  0,108);
	ifid[15].instruction =   BEQ( 8, 9, 0x8104);
	ifid[16].instruction =   BEQ( 8,10, 0xc010);
	ifid[17].instruction =   BNE(10,11, 0xf000);
	ifid[18].instruction =   BNE(10,12, 0x9000);
	ifid[19].instruction =     J(0x01234567);
	ifid[20].instruction =     J(0x03ffffff);
	ifid[21].instruction =   JAL(0x07654321);
	ifid[22].instruction =   JAL(0x0000000f);
	ifid[23].instruction =    JR(29);
	ifid[24].instruction =    JR(16);

	/* assign random program counters.  Or rather, pseudorandom, using
	 * a fixed seed
	 */
	srand(0x44442046);
	for (i=0; i<COUNT; i++)
		ifid[i].pc = rand() & 0xfffffffc;

	/* we need some dummy register values.  None are actually modified
	 * by this test, since no instruction gets to the WB phase.
	 */
	WORD regs[34];
	for (i=0; i<34; i++)
		regs[i] = 0x01010101 * i;

	/* fill in the data memory, since we now are also running the MEM
	 * phase.
	 */
	for (i=0; i<sizeof(dataMemory); i+=4)
		dataMemory[i/4] = (0xf << 28) | (0x00010001 * i);


	/* test the ID and EX phases for all instructions.  In all cases, we
	 * just run isolated instructions (as if they were a single-cycle
	 * processor).
	 */
	for (i=0; i<COUNT; i++)
	{
		Test_ID (&ifid [i], regs, &idex[i], NULL,NULL);
		Test_EX (&idex [i], &exmem[i], NULL,NULL);
		Test_MEM(&exmem[i], dataMemory, MEM_SIZE, &memwb[i]);
	}

	return 0;
}

