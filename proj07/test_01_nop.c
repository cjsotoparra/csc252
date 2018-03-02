
#include <stdio.h>
#include <memory.h>

#include "proj07.h"



int main()
{
	// sanity check that the sizes of the types are correct
	if (sizeof(int) != 4)
		printf("ERROR: sizeof(int) is %d, but it ought to be 4!\n", (int)sizeof(int));
	if (sizeof(long) != 8)
		printf("ERROR: sizeof(long) is %d, but it ought to be 8!\n", (int)sizeof(long));


	printf("This testcase simply calls each function in turn, with dummy arguments.  To pass this, implement all of the required stubs, so that your code will link.  You don't have to do anything with the arguments - just don't crash, and you will pass this testcase.\n");

	CLA_calcGenerate (0,0,0);
	CLA_calcPropagate(0,0,0);

	CLA_calcSuperGenerate (0,0,0);
	CLA_calcSuperPropagate(0,0,0);

	CLA_calcNibbleCarryIn(0,0,0,0);
	CLA_calcBitCarryIn   (0,0,0,0);

	printf("TESTCASE PASSED.\n");

	return 0;
}

void printf_binary(char *prefix, int val)
{
	int i;

	printf("%s", prefix);

	for (i=31; i>=0; i--)
	{
		printf("%d", (val >> i) & 0x1);

		if (i%4 == 0 && i != 0)
			printf(" ");
	}

	printf("\n");
}

