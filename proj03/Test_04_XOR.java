public class Test_04_XOR
{
	public static void main(String[] args)
	{
		Proj03_BinaryBase p = new Proj03_XOR();

		p.a = false;
		p.b = false;
		p.execute();
		System.out.printf("%5b ^ %5b = %5b\n", p.a, p.b, p.out);

		p.b = true;
		p.execute();
		System.out.printf("%5b ^ %5b = %5b\n", p.a, p.b, p.out);

		p.a =  true;
		p.b = false;
		p.execute();
		System.out.printf("%5b ^ %5b = %5b\n", p.a, p.b, p.out);

		p.b = true;
		p.execute();
		System.out.printf("%5b ^ %5b = %5b\n", p.a, p.b, p.out);
	}
}

