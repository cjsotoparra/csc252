#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "proj11.h"
#include "proj11_test_commonCode.h"


int main()
{
	int i;

#define COUNT 10
	IF_ID in [COUNT];
	ID_EX out[COUNT];

	in[0].instruction =   BEQ( 8, 9, 0x8104);
	in[1].instruction =   BEQ( 8,10, 0xc010);
	in[2].instruction =   BNE(10,11, 0xf000);
	in[3].instruction =   BNE(10,12, 0x9000);
	in[4].instruction =     J(0x01234567);
	in[5].instruction =     J(0x03ffffff);
	in[6].instruction =   JAL(0x07654321);
	in[7].instruction =   JAL(0x0000000f);
	in[8].instruction =    JR(29);
	in[9].instruction =    JR(16);

	/* assign random program counters.  Or rather, pseudorandom, using
	 * a fixed seed
	 */
	srand(0x04151633);
	for (i=0; i<COUNT; i++)
		in[i].pc = rand() & 0xfffffffc;


	/* In this testcase, we need to have some equal (and not equal)
	 * registers for testing.
	 */
	WORD regs[34];
	for (i=0; i<34; i++)
		regs[i] = 0x01010101 * i;
	regs[ 8] = regs[ 9] = 1234;
	regs[10] = regs[11] = 5678;

	/* registers 29 and 16 are used for JR instructions */
	regs[29] = 0xf4000204;
	regs[16] = 0xc23f3c18;


	/* test the ID phase for all instructions */
	for (i=0; i<COUNT; i++)
		Test_ID(&in[i], regs, &out[i], NULL,NULL);

	return 0;
}
