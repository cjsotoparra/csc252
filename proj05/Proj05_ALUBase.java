public class Proj05_ALUBase
{
	// inputs
	public boolean a[], b[];

	public boolean bNegate;
	public boolean aluOp[];

	// outputs
	public boolean out[];

	// methods which you must override!
	public void execute() {};


	// ----- UTILITY FUNCTIONS -----
	// Feel free to ignore anything below this line; these are just the
	// constructor, toString(), etc.


	public Proj05_ALUBase()
	{
		a     = new boolean[32];
		b     = new boolean[32];

		aluOp = new boolean[2];

		out   = new boolean[32];
	}
}

