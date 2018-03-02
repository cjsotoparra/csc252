public class Proj05_ALUElement extends Proj05_ALUElementBase{

      //instnce variable
      private Proj05_MUX_4by1 muxV;
      private Proj05_MUX_4by1 muxV2;

      private Proj03_AdderBase half1, half2;
      private Proj03_OR        carryOr;

      //contructor
      public Proj05_ALUElement (){

              muxV = new Proj05_MUX_4by1();
              muxV2 = new Proj05_MUX_4by1();
              half1   = new Proj03_HalfAdder();
	      half2   = new Proj03_HalfAdder();

	      carryOr = new Proj03_OR();

      }//contructor

      public void execute_internals(){

        //check the bInvert first
        muxV2.control[0] = bInvert;

        //check to see if you need to neaget b or not
        muxV2.in[0] = b;
        muxV2.in[1] = !b;

        //set the output of the mux
        muxV2.execute();

         half1.a = a;
	 half1.b = muxV2.out;
	 half1.execute();

	 half2.a = half1.out;
	 half2.b = carryIn;
	 half2.execute();

	 addOut = half2.out;

	 carryOr.a = half1.carryOut;
	 carryOr.b = half2.carryOut;
	 carryOr.execute();


 	 carryOut = carryOr.out;

         muxV.in[0] = a && b;
         muxV.in[1] = a || b;
         muxV.in[2] = half2.out;
         muxV.in[3] = less;

      }//internal

      public void execute_genResult(){

        //set the controls for aluOps
	muxV.control[0] = aluOp[0];
        muxV.control[1] = aluOp[1];

        //exetcute the output
        muxV.execute();

        //put the output of the mux in the result
        result = muxV.out;

      }//genResults

}//Proj05_ALUElement  class
