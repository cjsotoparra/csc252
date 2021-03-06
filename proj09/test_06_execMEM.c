#include <stdio.h>
#include <memory.h>

#include "proj09.h"
#include "proj09_test_commonCode.h"


int main()
{
	CPUMemory state;
	  memset(&state, 0, sizeof(state));

	/* this contains all of the instructions from tests 02 and 03 */
	state.instMemory[  0] =  ADD(S_REG(0), S_REG(1),S_REG(2));
	state.instMemory[  1] =  SUB(S_REG(3), S_REG(4),S_REG(5));
	state.instMemory[  2] = ADDI(T_REG(2), T_REG(3), -1);
	state.instMemory[  3] = ADDI(T_REG(4), T_REG(5), 16);
	state.instMemory[  4] =  ADDU( 1,  0, 2);
	state.instMemory[  5] =  SUBU( 3,  4, 5);
	state.instMemory[  6] = ADDIU( 6,  7,0x1234);
	state.instMemory[  7] =   AND( 9, 10,11);
	state.instMemory[  8] =    OR(12, 13,14);
//	state.instMemory[  9] =  ANDI(15, 16,0x5678);
//	state.instMemory[ 10] =   ORI(18, 19,0x9abc);
	state.instMemory[ 11] =   SLT(21, 22,23);
	state.instMemory[ 12] =  SLTI(24, 25,-1);
	state.instMemory[ 13] =    LW(26,  0,104);
	state.instMemory[ 14] =    SW(29,  0,108);
	state.instMemory[ 15] =   BEQ(1,0, 0x0104);
	state.instMemory[ 16] =     J(0x01234567);
	state.instMemory[ 17] =     J(0x03ffffff);

	/* fill in all of the registers, so that we can figure out if we're
	 * reading the right values.
	 */
	int i;
	for (i=0; i<32; i++)
		state.regs[i] = 0x01010101 * i;

	/* fill in the memory slots, similarly. */
	for (i=0; i<sizeof(state.dataMemory); i+=4)
		state.dataMemory[i/4] = 0x00010001 * i;


	for (state.pc = 0x0000; state.pc < 0x1000; state.pc += 4)
	{
		/* save the original state, to see if the student changes it */
		CPUMemory stateOrig;
		memcpy(&stateOrig, &state, sizeof(state));

		WORD inst = getInstruction(&state);

		CPUControl control, controlSave;
		  memset(&control,     0, sizeof(control));
		  memset(&controlSave, 0, sizeof(controlSave));

		ALUResult aluResult, aluResultSave;
		  memset(&aluResult,     0, sizeof(aluResult));
		  memset(&aluResultSave, 0, sizeof(aluResultSave));

		if (inst != 0)
		{
			execute_CPUControl(inst, &control);

			if (control.err)
			{
				printf("execute_CPUControl() set err=1 with opcode=0x%02x funct=0x%02x at PC 0x%08x\n",
				       control.opcode, control.funct,
				       state.pc);
				continue;
			}

			/* save a second copy of the control, to detect later
			 * modifications.
			 */
			memcpy(&controlSave, &control, sizeof(control));


			/* dump out the information to the user */
			dumpPCInstruction( state.pc, inst);
			dumpControl      (&control);

			WORD alu1 = getALUinput1(&control, state.regs);
			WORD alu2 = getALUinput2(&control, state.regs);

			execute_ALU(alu1,alu2,
			            control.ALU.op, control.ALU.bNegate,
			            &aluResult);

			/* save a second copy of the ALU Result, to detect
			 * later modifications.
			 */
			memcpy(&aluResultSave, &aluResult, sizeof(aluResult));


			MemResult memResult;
			  memset(&memResult, 0, sizeof(memResult));

			WORD rtVal = state.regs[control.rt];
			execute_MEM(&control, &aluResult, rtVal,
			             state.dataMemory,
			            &memResult);

			printf("  memResult.readVal=0x%04x_%04x\n",
			       (memResult.readVal >> 16) & 0xffff,
			        memResult.readVal        & 0xffff);

			for (i=0; i<sizeof(state.dataMemory)/sizeof(state.dataMemory[0]); i++)
			if (state.dataMemory[i] != stateOrig.dataMemory[i])
			{
				WORD addr = i*4;
				WORD old  = stateOrig.dataMemory[i];
				WORD new  = state    .dataMemory[i];

				printf("  MEM CHANGED.  Addr: 0x%04x_%04x  Was: 0x%04x_%04x Now: 0x%04x_%04x\n",
				       (addr >> 16) & 0xffff, addr & 0xffff,
				       (old  >> 16) & 0xffff, old  & 0xffff,
				       (new  >> 16) & 0xffff, new  & 0xffff);
			}

			printf("\n");
		}

		

		/* was the state struct modified? */
		if (memcmp(&control, &controlSave, sizeof(control)-3*sizeof(WORD)) != 0 ||
		    memcmp(&aluResult, &aluResultSave, sizeof(aluResult)) != 0)
		{
			printf("ERROR: At PC=0x%08x, the 'control' and/or 'aluResult' structs were modified.\n", stateOrig.pc);
		}
	}

	return 0;
}

