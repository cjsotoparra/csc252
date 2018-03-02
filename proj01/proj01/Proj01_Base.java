public class Proj01_Base
{
	// inputs
	public boolean[] a,b;

	// outputs
	public boolean[] out;
	public boolean   carryOut, overflow;

	// methods which you must override!
	void execute_add() {};
	void execute_AND() {};
	void execute_OR () {};
	void execute_NOT() {};
	void execute_2sComplement() {};


	// ----- UTILITY FUNCTIONS -----
	// Feel free to ignore anything below this line; these are just the
	// constructor, toString(), etc.


	public Proj01_Base()
	{
		a   = new boolean[32];
		b   = new boolean[32];
		out = new boolean[32];
	}

	public String toString()
	{
		return String.format("a=%s b=%s out=%s carryOut=%b overflow=%b",
		       arr2str(a), arr2str(b), arr2str(out),
		       carryOut, overflow);
	}

	public static String arr2str(boolean[] arr)
	{
		String retval  = "{";
		retval += (arr[31]?"1":"0");

		for (int i=30; i>=0; i--)
			retval += "," + (arr[i]?"1":"0");

		retval += "}";
		return retval;
	}
}

