/*File: proj.c
 *Author: Christian Soto
 *Purpose:  The purpose of this file is to take in an struct and the a and b variables
 *          and store them into the out integer.  And also indicate whether overflow
 *          or carryout occured.
 */

#include <stdio.h>
#include "proj01.h"

void execute_add(Proj01Data *obj){

    //varaibles that will be used
    int i = 0;
    int bit;
    int bit2;

      //set the structs variables to 0 to start
      obj->carryOut = 0;
      obj->out = 0;
      obj->overflow = 0;

   //Iterate through the bits in the integer and use similiar boolean
   // logic with bitwise arthmetic to mask bytes from the integers 
   //and then set the out integer with manupilating the bytes.
   for(i = 0; i <32 ; i++){

      //extract bits or mask
      bit = (obj->a >> i) & 1;
      bit2 = (obj->b >> i) & 1;

      //apply boolean logic
      if(bit==1 && bit2==1 && obj->carryOut == 0){
            obj->carryOut = 1;

      }else if(bit==1 && bit2==1 && obj->carryOut == 1){
            obj->carryOut = 1;
            obj->out = obj->out | (0x1 << i);

      }else if(bit==0 && bit2==0 && obj->carryOut == 0){
            obj->carryOut = 0;

      }else if(bit==0 && bit2==0 && obj->carryOut == 1){
            obj->carryOut = 0;
	    obj->out = obj->out | (0x1 << i);

      }else if(bit==1 && bit2==0 && obj->carryOut == 0){
            obj->carryOut = 0;
	    obj->out = obj->out | (0x1 << i);

      }else if(bit==1 && bit2==0 && obj->carryOut == 1){
            obj->carryOut = 1;

      }else if(bit==0 && bit2==1 && obj->carryOut == 0){
            obj->carryOut = 0;
	    obj->out = obj->out | (0x1 << i);

      }else if(bit==0 && bit2==1 && obj->carryOut == 1){
            obj->carryOut = 1;

      }else{

      }//if else

   }//for loop

   //set bits again to get ready to check for overflow
     bit = (obj->a >> 31) & 1;
     bit2 = (obj->b >> 31)& 1;
     int bit3 = (obj->out >> 31) & 1;

   //check for overflow
   if( bit == 1 && bit2== 1 && bit3 == 0){
       obj->overflow = 1;

   }else if (bit == 0 && bit2 == 0 && bit3 == 1){
       obj->overflow = 1;

   }else{

   }//overflow check


}//add
