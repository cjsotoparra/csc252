#include "proj07.h"

int CLA_calcGenerate (int bitNum, int a, int b){

           //gi(bitwise AND)
           int bita = (a >> bitNum); //extract bit from a
           int bitb = (b >> bitNum); //extract bit from b

           //Perfrom bitwise AND
           int bitAND = bita && bitb;

           //return the value
           return bitAND;
}

int CLA_calcPropagate(int bitNum, int a, int b){

           //pi(bitwise OR)
           int bita = (a >> bitNum) && 1; //extract bit from a
           int bitb = (b >> bitNum) && 1;//extract bit from b

           //Perfrom bitwise AND
           int bitAND = bita || bitb;

           //return the value
           return bitAND;
}
