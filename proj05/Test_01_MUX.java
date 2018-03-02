public class Test_01_MUX
{
	public static void main(String[] args)
	{
		Proj05_MUX_4by1Base mux = new Proj05_MUX_4by1();

		for (int i=0; i<64; i++)
		{
			mux.control[1] = b(i,5);
			mux.control[0] = b(i,4);
			mux.in[3]      = b(i,3);
			mux.in[2]      = b(i,2);
			mux.in[1]      = b(i,1);
			mux.in[0]      = b(i,0);

			mux.execute();

			System.out.printf("control=%d%d in={%d,%d,%d,%d} out=%d\n",
			                  d(mux.control[1]), d(mux.control[0]),
			                  d(mux.in[0]), d(mux.in[1]),
			                  d(mux.in[2]), d(mux.in[3]),
			                  d(mux.out));
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

