public class Proj05_MUX_4by1Base
{
	// inputs
	public boolean control[];
	public boolean in[];

	// outputs
	public boolean out;

	// methods which you must override!
	public void execute() {};


	// ----- UTILITY FUNCTIONS -----
	// Feel free to ignore anything below this line; these are just the
	// constructor, toString(), etc.


	public Proj05_MUX_4by1Base()
	{
		control = new boolean[2];
		in      = new boolean[4];
	}
}

