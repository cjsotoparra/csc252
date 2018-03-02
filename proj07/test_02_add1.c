
#include <stdio.h>
#include <memory.h>

#include "proj07.h"



void printf_binary_then_decimal(char *prefix, int val);

int main()
{
	// this is the input data: update these to change the testcase.
	int              a = 0x906f;
	int              b = 0x609f;
	int overallCarryIn = 0;


	// these will be filled in based on the user calls.
	int      generate=0,      propagate=0;
	int superGenerate=0, superPropagate=0;


	// counters for our various for() loops
	int bit,nib;


	printf_binary_then_decimal("             a = ", a);
	printf_binary_then_decimal("             b = ", b);


	// Calculate the generate and propagate bits.  These take as input
	// only the original values.
	//
	// In theory, this code is pretty simple: call the two user functions,
	// and then OR in the resulting bits.  But I added some debug code to
	// check for nonsense retvals.
	for (bit=0; bit<16; bit++)
	{
		int gen  = CLA_calcGenerate (bit, a,b);
		int prop = CLA_calcPropagate(bit, a,b);

		if (gen != 0 && gen != 1)
		{
			printf("ERROR: Invalid retval from user function.  CLA_calcGenerate(%d,%d,%d) returned %d\n", bit, a,b, gen);
			return 1;
		}

		if (prop != 0 && prop != 1)
		{
			printf("ERROR: Invalid retval from user function.  CLA_calcPropagate(%d,%d,%d) returned %d\n", bit, a,b, prop);
			return 1;
		}

		generate  |= (gen  << bit);
		propagate |= (prop << bit);
	}


	printf_binary_then_decimal("      generate = ", generate);
	printf_binary_then_decimal("     propagate = ", propagate);
	printf("\n");


	// Now that we have the generate and propagate bits, we can calculate
	// the super- bits.  This loop only runs 4 times, since there's only
	// 16 bits total.
	for (nib=0; nib<4; nib++)
	{
		int supGen  = CLA_calcSuperGenerate (nib, generate,propagate);
		int supProp = CLA_calcSuperPropagate(nib, generate,propagate);

		if (supGen != 0 && supGen != 1)
		{
			printf("ERROR: Invalid retval from user function.  CLA_calcSuperGenerate(%d,%d,%d) returned %d\n", bit, a,b, supGen);
			return 1;
		}

		if (supProp != 0 && supProp != 1)
		{
			printf("ERROR: Invalid retval from user function.  CLA_calcSuperPropagate(%d,%d,%d) returned %d\n", bit, a,b, supProp);
			return 1;
		}

		superGenerate  |= (supGen  << nib);
		superPropagate |= (supProp << nib);
	}


	printf_binary_then_decimal(" superGenerate = ", superGenerate);
	printf_binary_then_decimal("superPropagate = ", superPropagate);
	printf("\n");


	// Now, we actually perform the addition.  We have nested loops here;
	// we generate the carryIn for each nibble, and then use that as a
	// parameter in 4 bitwise carryIn calculations.  After we have the
	// carryIn for each bit, we'll perform the add - and record it into
	// the result.

	int sum = 0;

	for (nib=0; nib<4; nib++)
	{
		int nibbleCarryIn = CLA_calcNibbleCarryIn(nib,
		                                          superGenerate,
		                                          superPropagate,
		                                          overallCarryIn);

		if (nibbleCarryIn != 0 && nibbleCarryIn != 1)
		{
			printf("ERROR: Invalid retval from user function.  CLA_calcNibbleCarryIn(%d,%d,%d,%d) returned %d\n", nib, superGenerate,superPropagate, overallCarryIn, nibbleCarryIn);
			return 1;
		}

#if 0
		printf("Nibble %d : nibbleCarryIn %d\n", nib, nibbleCarryIn);
#endif

		for (bit=nib*4; bit<nib*4+4; bit++)
		{
			int bitCarryIn = CLA_calcBitCarryIn(bit,
			                                    nibbleCarryIn,
			                                    generate,
			                                    propagate);

			if (bitCarryIn != 0 && bitCarryIn != 1)
			{
				printf("ERROR: Invalid retval from user function.  CLA_calcBitCarryIn(%d,%d,%d,%d) returned %d\n", bit, nibbleCarryIn, generate,propagate, bitCarryIn);
				return 1;
			}

			int aBit = (a >> bit) & 0x1;
			int bBit = (b >> bit) & 0x1;

			int out = (aBit ^ bBit ^ bitCarryIn);

#if 0
			printf("  bit %2d : aBit %d bBit %d bitCarryIn %d : out %d\n", bit, aBit,bBit, bitCarryIn, out);
#endif

			sum |= (out << bit);
		}
	}


	printf_binary_then_decimal("             a = ", a);
	printf_binary_then_decimal("+            b = ", b);
	printf                    ("-----------------------------------\n");
	printf_binary_then_decimal("           sum = ", sum);

	return 0;
}



void printf_binary_then_decimal(char *prefix, int val)
{
	int i;

	printf("%s", prefix);

	for (i=15; i>=0; i--)
	{
		printf("%d", (val >> i) & 0x1);

		if (i%4 == 0 && i != 0)
			printf(" ");
	}

	printf(" %8d\n", val);
}

