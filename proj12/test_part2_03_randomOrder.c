#include <stdio.h>


typedef struct Proj12ArgType
{
	int                   key;
	struct Proj12ArgType *left;
	struct Proj12ArgType *right;
} Proj12ArgType;



Proj12ArgType *roy       (Proj12ArgType *arg1, int arg2);
void           durkon    (Proj12ArgType *arg1);
void           vaarsuvius(Proj12ArgType *arg1, int arg2);


int main()
{
	Proj12ArgType *thing;

	thing = roy(thing,  -7);
	thing = roy(thing,-288);
	thing = roy(thing,  -6);
	thing = roy(thing,   4);
	thing = roy(thing,-829);
	thing = roy(thing,   0);
	thing = roy(thing,-881);
	thing = roy(thing,   1);
	thing = roy(thing,   3);
	thing = roy(thing,  -8);

	durkon(thing);
}


