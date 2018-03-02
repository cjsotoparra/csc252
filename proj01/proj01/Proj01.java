/*
 * File:    Proj01.java
 * Authors: Christian Soto
 *
 * Purpose: This clas extends the Proj01_Base class.  The purpose is 
 *	    to create methods for the Proj01_Base class.  These methods
 *          are execute_add(), which will add 2 arrays. execute_NOT(),
 *          which will negate array a, execute_AND, which will aplly and 
 *          logic based on truth tables, and execute_OR as well, and then
 *          execute_2sComplement(), which will take the 2s complement of
 *          arrray a
 */


public class Proj01 extends Proj01_Base{

     public void execute_add(){

        //start with carryOut as false
        carryOut = false;

        //itertate through the whole array and see which condition applies
	for(int i = 0; i<32; i++){

		if(a[i]==true && b[i]==true && carryOut == false){
			out[i]=false;
			carryOut = true;

		} else if(a[i]==true && b[i]==true && carryOut == true){

			out[i]=true;
			carryOut = true;

		}else if(a[i]==false && b[i]==false && carryOut == false){

                        out[i]=false;
                        carryOut = false;
                }else if(a[i]==false && b[i]==false && carryOut == true){

                        out[i]=true;
			carryOut=false;

		}else if(a[i]==true && b[i]==false && carryOut == false){

                        out[i]=true;
                        carryOut = false;

                }else if(a[i]==true && b[i]==false && carryOut == true){

                        out[i]=false;
                        carryOut=true;

		}else if(a[i]==false && b[i]==true && carryOut == false){

                        out[i]=true;
                        carryOut = false;

		}else if(a[i]==false && b[i]==true && carryOut == true){

                        out[i]=false;
                        carryOut=true;

		}else{

		}//else if statement
	}//for loop


	//check for overflow
	if(a[31]==true && b[31]==true && out[31]==false){
		overflow = true;
	}else if(a[31]==false && b[31] == false && out[31]==true){
		overflow = true;
	}else{
	//	overflow =false;
	}//overflow check

     }//add

     public void execute_AND(){

	/*iterate through the arrays of a and b and apply "AND" logic and
          store the result in out.

          a      b    out
          0  &&  0 -> 0
          0  &&  1 -> 0
          1  &&  0 -> 0
          1  &&  1 -> 1
        */

	 for(int i = a.length-1; i>=0; i--){

                if(a[i]== false && b[i]==false){
                        out[i]=false;

                } else if(a[i]==false && b[i]==true){
                        out[i] = false;

                } else if(a[i]== true && b[i] == false){
                        out[i]=false;

                }else if (a[i]==true && b[i] == true){
                        out[i]=true;
                } else{

                }//else if statmeent

        }//for loop


     }//and

     public void execute_OR(){

	/*iterate through the arrays of a and b and apply "or" logic and 
	  store the result in out.

	  a      b    out
	  0  ||  0 -> 0
	  0  ||  1 -> 1
	  1  ||  0 -> 1
          1  ||  1 -> 1
	*/

	for(int i = 31; i>=0; i--){

		if(a[i]== false && b[i]==false){
			out[i]=false;

		} else if(a[i]==true && b[i]==true){
			out[i] = true;

		} else if(a[i]== false && b[i] == true){
			out[i]=true;

		}else if(a[i] == true && b[i] == false){
			out[i]=true;
		}else{

                }//else if statmeent

	}//for loop

     }//OR

     public void execute_NOT(){

	 /*iterate through the array of a and apply "NOT" logic and
          store the result in out.

          a        out
          0  NOT -> 1
          1  NOT -> 0
          */


       for(int i = a.length-1; i>=0; i--){

           if(a[i]==false){

              out[i]=true;

           } else {

             out[i]=false;

           }//if else statement
       }//for loop

     }//NOT

     public void execute_2sComplement(){

	/*create a new sub-class object and then copy the a array into the class's a array.
	  Then we call the execute_NOT() to negate the a array.  We intialize the 
	  class's b array and set the last one to true.  Then we call add execute_add()
	  on the new object.  Then we copy the values to the out array. */

	Proj01 arr1 = new Proj01 ();

         for(int j = 0 ; j<32 ; j++){
             arr1.a[j] = a[j];
         }

         //negate the array
         arr1.execute_NOT();

         //copy the arr1.out to the arr1.a
         for(int h = 0 ; h<32 ; h++){
             arr1.a[h] = arr1.out[h];
         }

         //intialize all values of array arr1.b
         for(int i = 0; i<31 ; i++){
             arr1.b[i] = false;
         }

         //set the last one to true
         arr1.b[0] = true;

         //and now execute_add()
         arr1.execute_add();

         //copy this output to array out
         for(int k = 0; k<32 ; k++){
                out[k] = arr1.out[k];
         }

     }//2sCompletement

}//class Proj01
