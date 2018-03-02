/*
 * Author: Christian Soto
 * Class: Proj04_HalfAdder.java
 * Purpose: The purpose of this class is to add two boolean inputs
 *	    a and b.  After addition, it will output two ourputs,
 *	    the sum and a carry out. It will do this operation
 *	    using the prevous classes AND, OR, NOT, and XOR only.
 */

public class Proj03_HalfAdder extends Proj03_AdderBase{

	//Instance Variables
        private Proj03_BinaryBase x, y, z;

        //constructor
        public Proj03_HalfAdder(){

	      //instance variables intialized. One is AND and the other XOR
              x = new Proj03_AND();
              y = new Proj03_XOR();
        }//contructor

        /*
         * Method: execute()
         * Purpose: The purpose of this method is to take two input boolean values, a and b
         *          and add them by apply XOR logic to them. Then we store the output to
	 *	    out. After that, we copy the variables into the AND gate and apply AND
	 *	    logic and store the result into carryOut.
         * Parameters: NONE
         */

        public void execute(){

          //copy our variables for the XOR gate
          y.a = a;
          y.b = b;

          //execute XOR on y
          y.execute();

         //copy our variables for the AND gate
         x.a = a;
         x.b = b;

         //execute AND on x
         x.execute();

         //copy the output into our output variable
         out = y.out;

         //get the carry out
         carryOut = x.out;

        }//execute

}//halfAdder
