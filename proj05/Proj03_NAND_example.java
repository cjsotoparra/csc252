public class Proj03_NAND_example extends Proj03_BinaryBase
{
	private Proj03_BinaryBase and, not;


	public Proj03_NAND_example()
	{
		and = new Proj03_AND();
		not = new Proj03_NOT();
	}

	void execute()
	{
		// copy our inputs to the inputs of the AND gate
		and.a = a;
		and.b = b;

		// make the AND gate calculate the result
		and.execute();

		// copy the output from the AND gate to the input of
		// the NOT gate
		not.a = and.out;

		// execute the NOT gate
		not.execute();

		// copy the output of the NOT gate to our own output
		out = not.out;
	}
}

