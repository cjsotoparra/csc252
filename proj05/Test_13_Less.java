public class Test_13_Less
{
	public static void main(String[] args)
	{
		Proj05_ALUBase alu = new Proj05_ALU();

		alu.a[0] = alu.b[0] = true;
		alu.a[1] = alu.b[1] = true;
		alu.a[2] = alu.b[2] = true;
		alu.a[3] = alu.b[3] = true;
		alu.a[4] = alu.b[4] = true;
		alu.a[5] = alu.b[5] = true;
		alu.a[6] = alu.b[6] = true;
		alu.a[7] = alu.b[7] = true;

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

