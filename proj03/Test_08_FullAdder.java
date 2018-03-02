public class Test_08_FullAdder
{
	public static void main(String[] args)
	{
		Proj03_AdderBase p = new Proj03_FullAdder();

		for (int i=0; i<8; i++)
		{
			p.a       = ((i & 0x4) != 0);
			p.b       = ((i & 0x2) != 0);
			p.carryIn = ((i & 0x1) != 0);

			p.execute();

			System.out.printf("%5b + %5b + %5b = %5b (carry %5b)\n",
			                  p.a, p.b, p.carryIn,
			                  p.out, p.carryOut);
		}
	}
}

