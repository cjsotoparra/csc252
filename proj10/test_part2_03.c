#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>



/* there's no header, so we just declare this by hand. */
void mysteryFunc(int *array, int whatIsThisOtherArg);

int main()
{
	int i;

	/* initialize the buffer with random elements.  We want something
	 * which is repeatable but easy to code.  So we hard-code the random
	 * number seed, and then use "random" numbers from there.
	 */
	srand(0xdeadbeef);

	int len = 10 + (rand() % 32);

	int *arr = malloc(sizeof(int) * len);
	if (arr == NULL)
	{
		perror("Could not allocate the input array");
		return 1;
	}

	for (i=0; i<len; i++)
		arr[i] = rand();

	mysteryFunc(arr, len);

	for (int i=0; i<len; i++)
	{
		if (i % 4 == 0)
			printf("%02d:", i);

		printf(" 0x%08x", arr[i]);

		if (i % 4 == 3)
			printf("\n");
	}

	if (i % 4 != 0)
		printf("\n");
}

