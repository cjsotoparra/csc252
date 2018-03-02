public class Test_06_Add
{
	public static void main(String[] args)
	{
		Proj05_ALUBase alu = new Proj05_ALU();

		alu.a[31] = alu.b[31] = true;

		alu.bNegate = false;
		alu.aluOp[1] = true; alu.aluOp[0] = false;

		alu.execute();

		printf_binary    ("    ", alu.a);
		printf_binary    ("  + ", alu.b);
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

