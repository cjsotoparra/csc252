#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "proj11.h"
#include "proj11_test_commonCode.h"


int main()
{
	int i;

#define COUNT 15
	IF_ID in [COUNT];
	ID_EX out[COUNT];

	in[ 0].instruction = ADD(S_REG(0),  S_REG(1), S_REG(2));
	in[ 1].instruction = SUB(S_REG(3),  S_REG(4), S_REG(5));
	in[ 2].instruction = ADDI(T_REG(2), T_REG(3), -1);
	in[ 3].instruction = ADDI(T_REG(4), T_REG(5), 16);
	in[ 4].instruction =  ADDU( 1,  0, 2);
	in[ 5].instruction =  SUBU( 3,  4, 5);
	in[ 6].instruction = ADDIU( 6,  7,0x1234);
	in[ 7].instruction =   AND( 9, 10,11);
	in[ 8].instruction =    OR(12, 13,14);
	in[ 9].instruction =  ANDI(15, 16,0x5678);
	in[10].instruction =   ORI(18, 19,0x9abc);
	in[11].instruction =   SLT(21, 22,23);
	in[12].instruction =  SLTI(24, 25,-1);
	in[13].instruction =    LW(26,  0,104);
	in[14].instruction =    SW(29,  0,108);

	/* assign random program counters.  Or rather, pseudorandom, using
	 * a fixed seed
	 */
	srand(0x16210415);
	for (i=0; i<COUNT; i++)
		in[i].pc = rand() & 0xfffffffc;

	/* we need some dummy register values.  None are actually modified
	 * by this test.
	 */
	WORD regs[34];
	for (i=0; i<34; i++)
		regs[i] = 0x01010101 * i;


	/* test the ID phase for all instructions */
	for (i=0; i<COUNT; i++)
		Test_ID(&in[i], regs, &out[i], NULL, NULL);

	return 0;
}
