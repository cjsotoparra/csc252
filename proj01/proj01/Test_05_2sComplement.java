public class Test_05_2sComplement
{
	public static void main(String[] args)
	{
		Proj01 p = new Proj01();

		// because I'm lazy, I'll only set the bits which are true;
		// we know that the rest will default to false.
		p.a[ 0] = true;
		p.a[ 1] = true;
		p.a[ 2] = true;
		p.a[ 3] = true;
		p.a[ 6] = true;
		p.a[ 7] = true;
		p.a[ 8] = true;
		p.a[10] = true;
		p.a[16] = true;
		p.a[19] = true;
		p.a[31] = true;

		p.execute_2sComplement();

		System.out.printf(" x = ");
		print_bits(p.a);
		System.out.println();

		System.out.printf("-x = ");
		print_bits(p.out);
		System.out.println();
	}

	public static void print_bits(boolean[] bits)
	{
		for (int i=31; i>=0; i--)
		{
			if (bits[i])
				System.out.print("1");
			else
				System.out.print("0");
		}
	}
}

