
#include <stdio.h>
#include <memory.h>

#include "proj01.h"



void printf_binary(char *prefix, int val);

int main()
{
	// sanity check that the sizes of the types are correct
	if (sizeof(int) != 4)
		printf("ERROR: sizeof(int) is %d, but it ought to be 4!\n", (int)sizeof(int));
	if (sizeof(long) != 8)
		printf("ERROR: sizeof(long) is %d, but it ought to be 8!\n", (int)sizeof(long));


	Proj01Data data;
	  memset(&data, 0, sizeof(data));

	data.a = 0x7FFFFFFF;
	data.b =         10;

	execute_add(&data);

	printf("Decimal:\n");
	printf("    %11d\n", data.a);
	printf("  + %11d\n", data.b);
	printf(" --------------\n");
	printf("    %11d\n", data.out);
	printf("  carryOut=%d\n", data.carryOut);
	printf("  overflow=%d\n", data.overflow);
	printf("\n");

	printf       ("Binary:\n");
	printf_binary("    ", data.a);
	printf_binary("  + ", data.b);
	printf       (" -------------------------------------------\n");
	printf_binary("    ", data.out);

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

