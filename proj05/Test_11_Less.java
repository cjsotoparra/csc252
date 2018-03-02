public class Test_11_Less
{
	public static void main(String[] args)
	{
		Proj05_ALUBase alu = new Proj05_ALU();

		// These are the same bits as we testing in Project 1,
		// testcase 3.
		alu.a[ 0] = true;
		alu.a[ 1] = true;
		alu.a[ 2] = true;
		alu.a[ 3] = true;
		alu.a[ 6] = true;
		alu.a[ 7] = true;
		alu.a[ 8] = true;
		alu.a[10] = true;
		alu.a[16] = true;
		alu.a[19] = true;
		alu.a[31] = true;

		alu.b[ 2] = true;
		alu.b[ 3] = true;
		alu.b[ 5] = true;
		alu.b[ 7] = true;
		alu.b[11] = true;
		alu.b[13] = true;
		alu.b[17] = true;
		alu.b[19] = true;
		alu.b[23] = true;
		alu.b[29] = true;
		alu.b[31] = true;

		alu.bNegate = true;
		alu.aluOp[1] = true; alu.aluOp[0] = true;

		alu.execute();

		printf_binary    ("    ", alu.a);
		printf_binary    ("  < ", alu.b);
		System.out.printf(" -------------------------------------------\n");
		printf_binary    ("    ", alu.out);
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

