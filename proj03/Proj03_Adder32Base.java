public class Proj03_Adder32Base
{
	// inputs
	public boolean a[],b[];

	// outputs
	public boolean out[];
	public boolean carryOut, overflow;

	// methods which you must override!
	void execute() {};


	// ----- UTILITY FUNCTIONS -----
	// Feel free to ignore anything below this line; these are just the
	// constructor, toString(), etc.


	public Proj03_Adder32Base()
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


