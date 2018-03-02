public class Test_03_ALUElement
{
	public static void main(String[] args)
	{
		Proj05_ALUElementBase elem = new Proj05_ALUElement();

		for (int i=0; i<128; i++)
		{
			elem.aluOp[1] = b(i,6);
			elem.aluOp[0] = b(i,5);
			elem.bInvert  = b(i,4);
			elem.carryIn  = b(i,3);
			elem.a        = b(i,2);
			elem.b        = b(i,1);
			elem.less     = b(i,0);

			elem.addOut = elem.carryOut = elem.result = false;

			elem.execute_internals();
			elem.execute_genResult();

			System.out.printf("aluOp=%d%d bInvert=%d carryIn=%d a=%d b=%d less=%d => addOut=%d carryOut=%d => result=%d\n",
			                  d(elem.aluOp[1]), d(elem.aluOp[0]), d(elem.bInvert),
                                          d(elem.carryIn), d(elem.a), d(elem.b),
			                  d(elem.less),
			                  d(elem.addOut), d(elem.carryOut), d(elem.result));
		}
	}

	public static boolean b(int i, int bit)
	{
		return ((i >> bit) & 0x1) == 1;
	}

	public static int d(boolean b)
	{
		return b ? 1:0;
	}
}

