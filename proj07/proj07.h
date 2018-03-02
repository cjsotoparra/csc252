#ifndef __PROJ_07_H__INCLUDED__
#define __PROJ_07_H__INCLUDED__


typedef struct MultOneStepData
{
	// all of these fields are *STATE* variables - they represent
	// registers that change over time.  So we will pass you *TWO*
	// pointers: a pointer to the old struct (which you must not
	// change) and a pointer to new struct (which you do).

	// unsigned long is 64 bits.  (We double-check this at the
	// beginning of the testcase.  I wish that C had well-defined,
	// standard types for some bit sizes!  Every project that uses
	// C comes up with its own typedefs.  Sigh.)

	unsigned long multiplicand, multiplier;
	unsigned long result;
} MultOneStepData;


typedef struct MultData
{
	// inputs (32 bit)
	unsigned int a,b;

	// output (64 bit)
	unsigned long out;
} MultData;



// function prototypes
int  CLA_calcGenerate (int bitNum, int a,int b);
int  CLA_calcPropagate(int bitNum, int a,int b);
int  CLA_calcSuperGenerate (int nibbleNum, int generate, int propagate);
int  CLA_calcSuperPropagate(int nibbleNum, int generate, int propagate);
int  CLA_calcNibbleCarryIn(int nibbleNum,
                           int superGenerate, int superPropagate,
                           int carryIn);
int  CLA_calcBitCarryIn(int bitNum,
                        int nibbleCarryIn,
                        int generate, int propagate);

void execute_multOneStep(MultOneStepData *before, MultOneStepData *after);
void execute_mult       (MultData*);


#endif

