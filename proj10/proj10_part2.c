/* proj10_part2.c
#
# Authors: Christian Soto
#
# This is the c code that was converted from the mips code.
*/
#include <stdio.h>

void mysteryFunc(int *array, int x){
          int tmp1;
          int tmp2;
          int tmp3;

          int i,j;

          for(i=0; i<x; i++){

		j=0;
		j = j +1;
			while(j < x){
				tmp1= array[j+1];
				tmp2 = array[j+2];

				if(array[j+2] < array[j+1]){

					//swap
                             		tmp3 = array[j];
                             		array[j] = array[j+1];
                             		array[j+1] = tmp3;
				}//if statement

				j++;
             		}//loop2

         }//loop1

}//mystery function
