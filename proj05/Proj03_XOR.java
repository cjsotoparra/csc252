/*
 * Author: Christian Soto
 * Class: Proj04_XOR.java
 * Purpose: The purpose of this class is to apply XOR logic on two
 *          boolean values, a and b.
 */

public class Proj03_XOR extends Proj03_BinaryBase{

	//instacne variables
	private Proj03_BinaryBase x, y, z, answer;

	//constructor
	public Proj03_XOR(){

		//intailize instance variables
		x = new Proj03_AND();
		y = new Proj03_OR ();
		z = new Proj03_NOT();
                answer = new Proj03_AND();

	}//contructor

	public void execute(){

           //copy and execute AND on x.a and x.b
           x.a = a;
           x.b = b;
           x.execute();

           //copy and execute OR on y.b and y.a
           y.a = a;
           y.b = b;
           y.execute();

           //copy nad excute NOT on z.a
           z.a = x.out;
           z.execute();

           //answer will represent (a OR b) and NOT(a AND b)
           answer.a = y.out;
           answer.b = z.out;
           answer.execute();

	   //store the output of answer into out
           out = answer.out;

	}//exeute

}//XOR
