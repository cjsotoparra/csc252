/*
 * Author: Christian Soto
 * Class: Proj04_Adder32.java
 * Purpose: The purpose of this class is to add an array of boolean input by
 *          using HalfAdder, FullAdder, and XOR objects.  The first array postion
 *	    will be the only that will be added using HalfAdder object, it will set
 *          the carryOut variable so that the other array inputs will be added using
 *          FullAdder object.  Then it will check for overflow using the XOR object.
 */

public class Proj03_Adder32 extends Proj03_Adder32Base{

	//instatnce vatriables
	private Proj03_HalfAdder x;
	private Proj03_FullAdder y;
        private Proj03_BinaryBase over;

	//Constructor
	public Proj03_Adder32(){

		//Intailize and create HalfAdder, FullAdder, and an XOR object
		x = new Proj03_HalfAdder();
		y = new Proj03_FullAdder();
                over = new Proj03_XOR();
	}//contructor

        /*
         * Method: execute()
         * Purpose: The purpose of this method is to add an array of boolean values.  The first step
	 *	    is to use the HalfAdder object at a[0] and b[0].  Once we have stored the result
	 *          the HalfAdder into out[0], we then move on to the rest of the array and use the
	 *          FullAdder for adding the rest and getting the carryOut as well, while storing the
	 *	    result into the out array. Once the addition is over, we check for overflow using
  	 *	    the XOR object and storing the output into the overflow variable.
         * Parameters: NONE
         */

	public void execute(){

		//First we set out variabels to perform half adder on the fisrt
		//position of the array
		x.a = a[0];
		x.b = b[0];

		//then we execute and store the result into out and intialize the carryOut as well
		x.execute();
		out[0] = x.out;
		carryOut = x.carryOut;

		//now we start looping and perform Full adder through the rest of the array using a for loop
		for(int i=1; i < a.length; i++){

			//set varaibles for full adder and
			y.a = a[i];
			y.b = b[i];
			y.carryIn = carryOut;

			//execture fullAdder on y and then store the result into out[i] and set carryOut again
			y.execute();
			out[i] = y.out;
			carryOut = y.carryOut;
		}//for loop

		//check for overflow by XORing y.carryIn and carryOut
                over.a = carryOut;
                over.b = y.carryIn;

                //execute XOR on over and save it in the overflow variable
                over.execute();
                overflow = over.out;

	}//execute

}//Adder32 class
