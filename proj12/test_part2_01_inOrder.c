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

	thing = roy(thing,  123);
	thing = roy(thing,  456);
	thing = roy(thing,  789);
	thing = roy(thing, 1024);

	durkon(thing);
}


