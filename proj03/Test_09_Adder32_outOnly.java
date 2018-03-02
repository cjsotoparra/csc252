public class Test_09_Adder32_outOnly
{
	public static void main(String[] args)
	{
		Proj03_Adder32Base p = new Proj03_Adder32();

		// These are the same bits as we testing in Project 1,
		// testcase 3.
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

		p.b[ 2] = true;
		p.b[ 3] = true;
		p.b[ 5] = true;
		p.b[ 7] = true;
		p.b[11] = true;
		p.b[13] = true;
		p.b[17] = true;
		p.b[19] = true;
		p.b[23] = true;
		p.b[29] = true;
		p.b[31] = true;

		p.execute();

		System.out.println("Binary:");
		printf_binary     ("    ", p.a);
		printf_binary     ("  + ", p.b);
		System.out.println(" -------------------------------------------");
		printf_binary     ("    ", p.out);
	}

	public static void printf_binary(String prefix, boolean[] arr)
	{
		int i;

		System.out.printf("%s", prefix);

		for (i=arr.length-1; i>=0; i--)
		{
			System.out.printf("%d", (arr[i]?1:0));

			if (i%4 == 0 && i != 0)
				System.out.printf(" ");
		}

		System.out.printf("\n");
	}
}

