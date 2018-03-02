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

	thing = roy(thing,      9);
	thing = roy(thing,    258);
	thing = roy(thing,-899058);
	thing = roy(thing,   -997);
	thing = roy(thing,      8);
	thing = roy(thing,     75);
	thing = roy(thing,      0);
	thing = roy(thing,     -4);
	thing = roy(thing,    100);
	thing = roy(thing,    814);

	vaarsuvius(thing, 10);
	vaarsuvius(thing, 11);
	vaarsuvius(thing, 12);
	vaarsuvius(thing, 13);
	vaarsuvius(thing, 14);
	vaarsuvius(thing, 15);
	vaarsuvius(thing, 16);
	vaarsuvius(thing, 17);
	vaarsuvius(thing, 18);
	vaarsuvius(thing, 19);
}


