/*
 * Author: Christian Soto
 * Class: Proj04_FullAdder.java
 * Purpose: The purpose of this class is to add two boolean inputs
 *          a and b and an additonal carryIn input.  After addition, it will output two outputs,
 *          the sum and a carry out. It will do this operation
 *          using the prevous classes AND, OR, NOT, and XOR only.
 */

public class Proj03_FullAdder extends Proj03_AdderBase{

	//Instance variables
	private Proj03_HalfAdder x, y;
	private Proj03_BinaryBase z;

	//constructor
	public Proj03_FullAdder(){

		//Intialize x,y, and z to two HalfAdder objects and an OR object
		x = new Proj03_HalfAdder();
		y = new Proj03_HalfAdder();
		z = new Proj03_OR();
	}//construuctor

        /*
         * Method: execute()
         * Purpose: The purpose of this method is to take three input boolean values, a, b, and carryIn
         *          and add them by using HalfAdder class. Then we store the outputs to
         *          out and carryOut. We first perform HalfAdder on one object, and then store the carryOut, and
	 *          the output to out.  Then we input the carryIn and the outfrom the first HalfAdder and execute
         *          HalfAdder once more. Then our final step is storing the sum of the two HalfAdders and the carryOut.
         * Parameters: NONE
         */

	public void execute(){

		//first we copy variables for the first half adder input and we ignore the carryIn this time
		x.a = a;
		x.b = b;

		//execu8te half adder on x
		x.execute();

		//next, we copy carryIn from carryIn to y.a and the other is the output of the first halfadder x.out into y.b
		y.a = carryIn;
		y.b = x.out;

		//we now execute halfadder on y and store the output into out.
		y.execute();
		out = y.out;

		//next we get the carry the carryOut from both the Half adder outputs and store them into z.a and z.b
		z.a = x.carryOut;
		z.b = y.carryOut;

		//now that we have our carryOut outputs, we perform OR on them and store the output into carryOut
		z.execute();
		carryOut = z.out;

	}//execute

}//Full adder class
