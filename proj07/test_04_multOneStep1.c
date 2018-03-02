
#include <stdio.h>
#include <memory.h>

#include "proj07.h"



void printf_binary_then_decimal_u64(char *prefix, unsigned long val);

int main()
{
	// this is the input data: update these to change the testcase.
	int a = 79;
	int b = 37;


	MultOneStepData start, step1, step2, step3;
	  memset(&start, 0, sizeof(start));
	  memset(&step1, 0, sizeof(step1));
	  memset(&step2, 0, sizeof(step2));
	  memset(&step3, 0, sizeof(step3));

	start.multiplicand = a;
	start.multiplier   = b;
	start.result       = 0;

	execute_multOneStep(&start, &step1);
	execute_multOneStep(&step1, &step2);
	execute_multOneStep(&step2, &step3);

	printf_binary_then_decimal_u64("                 a", a);
	printf_binary_then_decimal_u64("                 b", b);

	printf("\n");
	printf_binary_then_decimal_u64("start.multiplicand", start.multiplicand);
	printf_binary_then_decimal_u64("start.multiplier  ", start.multiplier);
	printf_binary_then_decimal_u64("start.result      ", start.result);

	printf("\n");
	printf_binary_then_decimal_u64("step1.multiplicand", step1.multiplicand);
	printf_binary_then_decimal_u64("step1.multiplier  ", step1.multiplier);
	printf_binary_then_decimal_u64("step1.result      ", step1.result);

	printf("\n");
	printf_binary_then_decimal_u64("step2.multiplicand", step2.multiplicand);
	printf_binary_then_decimal_u64("step2.multiplier  ", step2.multiplier);
	printf_binary_then_decimal_u64("step2.result      ", step2.result);

	printf("\n");
	printf_binary_then_decimal_u64("step3.multiplicand", step3.multiplicand);
	printf_binary_then_decimal_u64("step3.multiplier  ", step3.multiplier);
	printf_binary_then_decimal_u64("step3.result      ", step3.result);

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

