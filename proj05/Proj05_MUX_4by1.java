public class Proj05_MUX_4by1 extends Proj05_MUX_4by1Base{


     public Proj05_MUX_4by1(){

     }

     public void execute(){

     //read the 2 control bits first and see where to connect the "in" array
     // to the "out" array

     if(control[0]==false && control[1]==false){
        out = in[0];
     }else if(control[0]==true && control[1]==false){
        out = in[1];
     }else if(control[0]==false && control[1]==true){
        out = in[2];

     }else if(control[0]==true && control[1]==true){
        out = in[3];

     }else {

     }//else if statements

     }//execute



}//Proj05_MUX_4by1 class
