public class Test_01_AND
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

		p.execute_AND();

		for (int i=0; i<32; i++)
		{
			System.out.printf("%02d: %c & %c = %c\n",
			                  i,
			                  TF(p.a[i]), TF(p.b[i]),
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

