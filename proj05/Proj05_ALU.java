public class Proj05_ALU extends Proj05_ALUBase{

       //instaance variables
       private Proj05_ALUElement[] bits;

       //constructor
       public Proj05_ALU(){

          bits = new Proj05_ALUElement[32];
          for(int i=0; i<32; i++){
                  bits[i] = new Proj05_ALUElement();

          }//for loop

       }//contructor


       public void execute(){

         boolean currCarry =  false;

         for(int i=0; i<32; i++){

            //set up our inputs for bits
            bits[i].bInvert = bNegate;
            bits[i].carryIn = currCarry;
            bits[i].less = false;
            bits[i].a = a[i];
            bits[i].b = b[i];
            bits[i].aluOp[0] = aluOp[0];
            bits[i].aluOp[1] = aluOp[1];

            bits[i].execute_internals();

            //set our outputs for bits
            currCarry = bits[i].carryOut;
            bits[i].execute_genResult();

            currCarry = bits[i].carryOut;

            out[i] = bits[i].result;

         }//for loop

           //set less
           bits[31].less = (aluOp[0] && aluOp[1])&& bNegate;

       }//execute


}//Proj05_ALU class
