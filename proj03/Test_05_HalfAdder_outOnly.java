public class Test_05_HalfAdder_outOnly
{
	public static void main(String[] args)
	{
		Proj03_AdderBase p = new Proj03_HalfAdder();

		for (int i=0; i<8; i++)
		{
			p.a       = ((i & 0x4) != 0);
			p.b       = ((i & 0x2) != 0);

			// half adders are supposed to ignore carryIn.  But
			// we test it to *CONFIRM* that your half adder is
			// ignoring it as it should!
			p.carryIn = ((i & 0x1) != 0);

			p.execute();

			System.out.printf("%5b + %5b = %5b\n", p.a, p.b, p.out);
		}
	}
}

