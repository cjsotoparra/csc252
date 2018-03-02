The two additonal instructions that I decided to add to my code were the "jal" instruction and
the "bne" instruction

The control bits for "jal" were the the following:
	controlOut->ALUsrc = 0;

        controlOut->ALU.bNegate = 0;
        controlOut->ALU.op = 0;

        controlOut->memRead = 0;
        controlOut->memWrite = 0;
        controlOut->memToReg = 2;

        controlOut->regDst = 2;
        controlOut->regWrite = 1;

        controlOut->branch = 0;
        controlOut->jump = 1;
This is similiar the "j" instructiona and has the same format as well. some 
differences though, was that the "jal" instruction writes to register and to
the distination.

For the "bne" instruction, the control bits are the following:
	 controlOut->ALUsrc = 0;

         controlOut->ALU.bNegate = 0;
         controlOut->ALU.op = 1;

         controlOut->memRead = 0;
         controlOut->memWrite = 0;
         controlOut->memToReg = 0;

         controlOut->regDst = 0;
         controlOut->regWrite = 0;

         controlOut->branch = 1;
         controlOut->jump = 0;
Thia is similar to the "beq" instruction but it has a different ALU.op code  
and does not have the bNegate but on.

For both of these instructions, I did not need to add anymore code than i
already had or needed to the best of my knowlege.
