/*File: proj09.c
 *Author: Christian Soto
 *Purpose:  The purpose of this program is to demstarte how a full working cpu 
 *          operates by using different instructions.  This program is broken up into
 *          different pecies where we first get the nescessary bits to work with.  And
 *          Then implementation will begins.
 */


#include <stdio.h>
#include "proj09.h"

WORD getInstruction(CPUMemory* state){

       WORD counter = state->pc/4;
       return state->instMemory[counter];
}//getInstruction

void execute_CPUControl(WORD instruction, CPUControl* controlOut){

       //set control bits
       controlOut->opcode = (instruction & 0xFC000000) >> 26;
       controlOut->rs = (instruction & 0x03E00000) >> 21;
       controlOut->rt = (instruction & 0x001F0000) >> 16;
       controlOut->rd = (instruction & 0x0000F800) >> 11;
       controlOut->shamt = (instruction & 0x000007C0) >> 6;
       controlOut->funct = instruction & 0x0000003F;
       controlOut->imm16 = instruction & 0x0000FFFF;
       controlOut->imm32 = signExtend16to32(controlOut->imm16);
       controlOut->address = instruction & 0x03FFFFFF;
       controlOut->err= 0;

       //check the opcode
       if(controlOut->opcode !=0){

                //check to see if its addi
                if(controlOut->opcode == 8){

                         controlOut->ALUsrc = 1;

                         controlOut->ALU.bNegate = 0;
                         controlOut->ALU.op = 2;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 0;
                         controlOut->regWrite = 1;

                         controlOut->branch = 0;
                         controlOut->jump = 0;

                //check to see if its addiu
                }else if(controlOut->opcode == 9){

                         controlOut->ALUsrc = 1;

                         controlOut->ALU.bNegate = 0;
                         controlOut->ALU.op = 2;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 0;
                         controlOut->regWrite = 1;

                         controlOut->branch = 0;
                         controlOut->jump = 0;

                //check to see if it's slti
                }else if(controlOut->opcode == 10){

                         controlOut->ALUsrc = 1;

                         controlOut->ALU.bNegate = 1;
                         controlOut->ALU.op = 3;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 0;
                         controlOut->regWrite = 1;

                         controlOut->branch = 0;
                         controlOut->jump = 0;
                //check to see lw
                }else if(controlOut->opcode == 35){

                         controlOut->ALUsrc = 1;

                         controlOut->ALU.bNegate = 0;
                         controlOut->ALU.op = 2;

                         controlOut->memRead = 1;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 1;

                         controlOut->regDst = 0;
                         controlOut->regWrite = 1;

                         controlOut->branch = 0;
                         controlOut->jump = 0;

                //check to see if its sw
                }else if(controlOut->opcode == 43){

                         controlOut->ALUsrc = 1;

                         controlOut->ALU.bNegate = 0;
                         controlOut->ALU.op = 2;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 1;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 0;
                         controlOut->regWrite = 0;

                         controlOut->branch = 0;
                         controlOut->jump = 0;

                //check to see if its beq
                }else if(controlOut->opcode == 4){

                         controlOut->ALUsrc = 0;

                         controlOut->ALU.bNegate = 1;
                         controlOut->ALU.op = 2;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 0;
                         controlOut->regWrite = 0;

                         controlOut->branch = 1;
                         controlOut->jump = 0;

                //check to see if its j
                }else if(controlOut->opcode == 2){

                          controlOut->ALUsrc = 0;

                         controlOut->ALU.bNegate = 0;
                         controlOut->ALU.op = 0;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 0;
                         controlOut->regWrite = 0;

                         controlOut->branch = 0;
                         controlOut->jump = 1;

		//check to see if it's jal
		}else if(controlOut->opcode == 3){

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

		 //check to see if its bne
                }else if(controlOut->opcode == 5){

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
                }else{

                        //invalid opcode, set error and values to 0
                        controlOut->err = 1;
                }

       //check to see if it's a valid funct code
       }else{

             //check to see if it's add
             if(controlOut->funct == 32){

                         controlOut->ALUsrc = 0;

                         controlOut->ALU.bNegate = 0;
                         controlOut->ALU.op = 2;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 1;
                         controlOut->regWrite = 1;

                         controlOut->branch = 0;
                         controlOut->jump = 0;

             //check to see if it's addu
             }else if(controlOut->funct == 33){

                         controlOut->ALUsrc = 0;

                         controlOut->ALU.bNegate = 0;
                         controlOut->ALU.op = 2;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 1;
                         controlOut->regWrite = 1;

                         controlOut->branch = 0;
                         controlOut->jump = 0;

             //check to see if it's sub
             }else if(controlOut->funct == 34){


                         controlOut->ALUsrc = 0;

                         controlOut->ALU.bNegate = 1;
                         controlOut->ALU.op = 2;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 1;
                         controlOut->regWrite = 1;

                         controlOut->branch = 0;
                         controlOut->jump = 0;

             //check to see if it's subu
             }else if(controlOut->funct == 35){

                         controlOut->ALUsrc = 0;

                         controlOut->ALU.bNegate = 1;
                         controlOut->ALU.op = 2;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 1;
                         controlOut->regWrite = 1;

                         controlOut->branch = 0;
                         controlOut->jump = 0;

             //check to see if it's and
             }else if(controlOut->funct == 36){

                         controlOut->ALUsrc = 0;

                         controlOut->ALU.bNegate = 0;
                         controlOut->ALU.op = 0;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 1;
                         controlOut->regWrite = 1;

                         controlOut->branch = 0;
                         controlOut->jump = 0;

             //check to see if it's or
             }else if(controlOut->funct == 37){

                         controlOut->ALUsrc = 0;

                         controlOut->ALU.bNegate = 0;
                         controlOut->ALU.op = 1;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 1;
                         controlOut->regWrite = 1;

                         controlOut->branch = 0;
                         controlOut->jump = 0;

             //check to see if it's slt
             }else if(controlOut->funct == 42){

                         controlOut->ALUsrc = 0;

                         controlOut->ALU.bNegate = 1;
                         controlOut->ALU.op = 3;

                         controlOut->memRead = 0;
                         controlOut->memWrite = 0;
                         controlOut->memToReg = 0;

                         controlOut->regDst = 1;
                         controlOut->regWrite = 1;

                         controlOut->branch = 0;
                         controlOut->jump = 0;

             //else it's an error
             }else {

                        controlOut->err == 1;
             }//else if for funct

       }//else if 1

}//execute_CPUControl

WORD getALUinput1(CPUControl* controlIn, WORD *regs){

       return regs[controlIn->rs];
}//getALUinput

WORD getALUinput2(CPUControl* controlIn, WORD *regs){

	if(controlIn->ALUsrc==1){
                controlIn->imm32 = signExtend16to32(controlIn->imm16);
		return controlIn->imm32;
	}

		return regs[controlIn->rt];
}//getALUinput

void execute_ALU(WORD input1, WORD input2, int aluOp, int bNegate, ALUResult* aluResultOut){

	if(aluOp == 2 && bNegate == 0){
                aluResultOut->result =input1 + input2;
        }else if (aluOp == 2 && bNegate ==1){
                aluResultOut->result = input1 - input2;
        }else if(aluOp == 0){

		aluResultOut->result = input1 & input2;
	}else if(aluOp == 1){

		aluResultOut->result = input1 | input2;
	}else if(aluOp == 3 && bNegate == 1){

		if(input1< input2){
			aluResultOut->result = 1;
			aluResultOut->zero = 0;
		}else{
			aluResultOut->result = 0;
			 aluResultOut->zero = 1;
		}

	}else{

        }

}

void execute_MEM(CPUControl *controlIn, ALUResult *aluResultIn, WORD rtVal, WORD *memory, MemResult *resultOut){

	if(controlIn->memRead==1){
		resultOut->readVal = memory[aluResultIn->result/4];
	}else{

		resultOut->readVal = 0;
	}

	if(controlIn->memWrite==1){
		resultOut->readVal = 0;
		memory = controlIn->rs + controlIn->imm32;
	}

}

WORD getNewPC(CPUControl *control, int aluzero, WORD oldPC){

	//TODO
	return oldPC;
}

void execute_updateRegs(CPUControl* controlIN, ALUResult* aluResultIn, MemResult* memResultIn, WORD* regs){

	//TODO
}
