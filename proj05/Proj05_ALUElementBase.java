public class Proj05_ALUElementBase
{
	// inputs
	public boolean aluOp[];
	public boolean bInvert;
	public boolean carryIn;

	public boolean a,b;
	public boolean less;

	// outputs
	public boolean addOut, carryOut;   // generated by execute_internals()
	public boolean result;             // generated by execute_genResult()

	// methods which you must override!
	//
	// NOTE NOTE NOTE: There are *two* methods here, see the spec for
	// the difference!
	public void execute_internals() {};
	public void execute_genResult() {};


	// ----- UTILITY FUNCTIONS -----
	// Feel free to ignore anything below this line; these are just the
	// constructor, toString(), etc.


	public Proj05_ALUElementBase()
	{
		aluOp = new boolean[2];
	}
}
