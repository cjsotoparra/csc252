public class Test_06_ADD_overflow_carryOut
{
	public static void main(String[] args)
	{
		Proj01 p = new Proj01();

		// because I'm lazy, I'll only set the bits which are true;
		// we know that the rest will default to false.
		p.a[31] = true;

		p.b[31] = true;

		p.execute_add();

		System.out.printf("  ");
		print_bits(p.a);
		System.out.println();

		System.out.printf("+ ");
		print_bits(p.b);
		System.out.println();

		System.out.println("----------------------------------");

		System.out.printf("  ");
		print_bits(p.out);
		System.out.println();

		System.out.println();

		System.out.printf("  carryOut = %c\n", bit(p.carryOut));

		System.out.printf("  overflow = %c\n", bit(p.overflow));
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

	public static char bit(boolean b)
	{
		if (b)
			return '1';
		else
			return '0';
	}
}

