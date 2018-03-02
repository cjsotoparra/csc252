public class Test_04_NOT
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

		p.execute_NOT();

		for (int i=0; i<32; i++)
		{
			System.out.printf("%02d: ~%c = %c\n",
			                  i,
			                  TF(p.a[i]),
			                  TF(p.out[i]));
		}
	}

	public static char TF(boolean b)
	{
		if (b)
			return 'T';
		else
			return 'F';
	}
}

