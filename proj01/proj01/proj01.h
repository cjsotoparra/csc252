#ifndef _PROJ01_H__INCLUDED_
#define _PROJ01_H__INCLUDED_


typedef struct Proj01Data
{
	// inputs
	int a,b;

	// outputs
	int out;

	// output flags
	int carryOut, overflow;
} Proj01Data;


void execute_add(Proj01Data *obj);


#endif

