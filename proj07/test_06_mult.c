
#include <stdio.h>
#include <memory.h>

#include "proj07.h"



void printf_binary_then_decimal(char *prefix, int val);

int main()
{
	// this is the input data: update these to change the testcase.
	int a = 15;
	int b = 3737;

	MultData data;
	  data.a   = a;
	  data.b   = b;
	  data.out = 0;

	execute_mult(&data);

	printf_binary_then_decimal("       a = ", a);
	printf_binary_then_decimal("       b = ", b);

	printf("\n");
	printf_binary_then_decimal("data.a   = ", data.a);
	printf_binary_then_decimal("data.b   = ", data.b);
	printf_binary_then_decimal("data.out = ", data.out);

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

