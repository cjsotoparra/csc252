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
	ID_EX            out  [COUNT];

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
	srand(0x22220415);
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
	{
		// create a ID_EX ahead which is a LW
		ID_EX lwAhead;
		  memset(&lwAhead, 0, sizeof(lwAhead));

		// rs should be ignored, but I intentionally make it 17 ($s1)
		// to see if the student code checks it.
		lwAhead.rs = 17;

		// set the rest of the bits to something appropriate for a LW:
		lwAhead.ALUsrc   = 1;
		lwAhead.ALU.op   = 2;
		lwAhead.memRead  = 1;
		lwAhead.regDst   = 0;    // rt, not rd
		lwAhead.regWrite = 1;


		// TEST 1: set the rt of the LW to the rs field of the
		// instruction (remember, we don't check opcode, just the
		// field)
		lwAhead.rt = (in[i].instruction >> 21) & 0x1f;

		// a stall should happen
		Test_ID(&in[i], regs, &out[i], NULL, &lwAhead);


		// TEST 2: Same, but for the rt field of our instruction
		lwAhead.rt = (in[i].instruction >> 16) & 0x1f;

		// a stall should happen
		Test_ID(&in[i], regs, &out[i], NULL, &lwAhead);
	}

	return 0;
}


