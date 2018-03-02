
#include <stdio.h>
#include <memory.h>

#include "proj07.h"



void printf_binary_then_decimal_u64(char *prefix, unsigned long val);

int main()
{
	// this is the input data: update these to change the testcase.
	int a = 1999999999;	// 2 billion minus one
	int b = a;

	MultData data;
	  data.a   = a;
	  data.b   = b;
	  data.out = 0;

	execute_mult(&data);

	printf_binary_then_decimal_u64("       a", a);
	printf_binary_then_decimal_u64("       b", b);

	printf("\n");
	printf_binary_then_decimal_u64("data.a  ", data.a);
	printf_binary_then_decimal_u64("data.b  ", data.b);
	printf_binary_then_decimal_u64("data.out", data.out);

	return 0;
}



void printf_binary_then_decimal_u64(char *prefix, unsigned long val)
{
	int i;

	printf("%s = %20ld = ", prefix, val);

	for (i=63; i>=0; i--)
	{
		printf("%ld", (val >> i) & 0x1);

		if (i%4 == 0 && i != 0)
			printf(" ");
	}

	printf("\n");
}

