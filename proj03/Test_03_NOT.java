public class Test_03_NOT
{
	public static void main(String[] args)
	{
		Proj03_BinaryBase p = new Proj03_NOT();

		p.a = false;
		p.execute();
		System.out.printf("~%5b = %5b\n", p.a, p.out);

		p.a = true;
		p.execute();
		System.out.printf("~%5b = %5b\n", p.a, p.out);
	}
}

