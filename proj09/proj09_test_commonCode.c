#include <stdio.h>
#include <memory.h>

#include "proj09.h"
#include "proj09_test_commonCode.h"



void dumpPCInstruction(WORD pc, WORD inst)
{
	printf("PC: 0x%04x_%04x   Instruction: 0x%04x_%04x\n",
	       (pc   >> 16) & 0xffff, pc   & 0xffff,
	       (inst >> 16) & 0xffff, inst & 0xffff);
}

void dumpControl(CPUControl *controlIn)
{
	printf("  --\n");
	printf("  opcode  (6 bits)=0x%02x\n", controlIn->opcode);
	printf("  rs      (5 bits)=0x%02x\n", controlIn->rs);
	printf("  rt      (5 bits)=0x%02x\n", controlIn->rt);
	printf("  rd      (5 bits)=0x%02x\n", controlIn->rd);
	printf("  shamt   (5 bits)=0x%02x\n", controlIn->shamt);
	printf("  funct   (6 bits)=0x%02x\n", controlIn->funct);
	printf("  imm16  (16 bits)=0x     %04x\n", controlIn->imm16);
	printf("  imm32  (32 bits)=0x%04x_%04x\n",
	       (controlIn->imm32 >> 16) & 0xffff, controlIn->imm32   & 0xffff);
	printf("  addr   (26 bits)=0x %03x_%04x\n",
	       (controlIn->address >> 16) & 0xffff, controlIn->address & 0xffff);
	printf("  --\n");
	printf("  err=%d\n", controlIn->err);
	printf("  --\n");
	printf("  ALUsrc     =%d\n", controlIn->ALUsrc);
	printf("  ALU.op     =%d\n", controlIn->ALU.op);
	printf("  ALU.bNegate=%d\n", controlIn->ALU.bNegate);
	printf("  memRead    =%d\n", controlIn->memRead);
	printf("  memWrite   =%d\n", controlIn->memWrite);
	printf("  memToReg   =%d\n", controlIn->memToReg);
	printf("  regDst     =%d\n", controlIn->regDst);
	printf("  regWrite   =%d\n", controlIn->regWrite);
	printf("  branch     =%d\n", controlIn->branch);
	printf("  jump       =%d\n", controlIn->jump);
	printf("\n");
}

void dumpControl_aluInputsOnly(CPUControl *controlIn)
{
	printf("  rs      (5 bits)=0x%02x\n", controlIn->rs);
	printf("  rt      (5 bits)=0x%02x\n", controlIn->rt);
	printf("  imm16  (16 bits)=0x     %04x\n", controlIn->imm16);
	printf("  imm32  (32 bits)=0x%04x_%04x\n",
	       (controlIn->imm32 >> 16) & 0xffff, controlIn->imm32   & 0xffff);
	printf("  ALUsrc     =%d\n", controlIn->ALUsrc);
}

void dumpControl_aluCalcOnly(CPUControl *controlIn)
{
	printf("  rs      (5 bits)=0x%02x\n", controlIn->rs);
	printf("  rt      (5 bits)=0x%02x\n", controlIn->rt);
	printf("  imm16  (16 bits)=0x     %04x\n", controlIn->imm16);
	printf("  imm32  (32 bits)=0x%04x_%04x\n",
	       (controlIn->imm32 >> 16) & 0xffff, controlIn->imm32   & 0xffff);
	printf("  ALUsrc     =%d\n", controlIn->ALUsrc);
	printf("  ALU.op     =%d\n", controlIn->ALU.op);
	printf("  ALU.bNegate=%d\n", controlIn->ALU.bNegate);
}


int execute_singleCycleCPU(CPUMemory *state, int debug)
{
	int i;

	/* these are several variables which are used in the actual logic of
	 * the code below.
	 */
	WORD       inst;
	CPUControl control;
	WORD       aluInput1, aluInput2;
	ALUResult  aluResult;
	MemResult  memResult;
	WORD       rtVal;
	  memset(&control,   0, sizeof(control));
	  memset(&aluResult, 0, sizeof(aluResult));
	  memset(&memResult, 0, sizeof(memResult));

	/* set this to nonzero to indicate that the program should end */
	int fail = 0;


	/* we make duplicates all 4 of the structs (the parameter, plus the
	 * three result structs) so that we can later compare them.  The
	 * result structs should be *ENTIRELY* unmodified, since they are set
	 * up once, and then never changed.  The 'state' variable should
	 * change, but only in a few places.
	 */
	CPUMemory      state_save;
	CPUControl   control_save;
	ALUResult  aluResult_save;
	MemResult  memResult_save;

	memcpy(&state_save, state, sizeof(*state));


	// STEP 1: read the instruction from memory
	inst = getInstruction(state);

	// is this a system call?  For those, we simply skip over the student
	// implementation.
	if (inst == SYSCALL())
	{
		if (debug) printf("[systemCall]");

		state->pc += 4;
		return execSyscall(state);
	}


	// STEP 2: decode the instruction
	execute_CPUControl(inst,          &control);
	memcpy            (&control_save, &control, sizeof(control));

	if (debug)
	{
		printf("Opcode: 0x%02x   at 0x%04x_%04x\n",
		        control.opcode,
		       (state->pc >> 16) & 0xffff, state->pc & 0xffff);

		if (control.opcode == 0)
			printf("  funct: 0x%02x\n", control.funct);
	}

	if (control.err)
	{
		printf("execute_CPU() set err=1\n");
		return 1;
	}

	if (debug)
		dumpControl(&control);


	// STEP 3: If this isn't a syscall, then do our normal calculations.
	// What do we drive into the ALU?
	aluInput1 = getALUinput1(&control, state->regs);
	aluInput2 = getALUinput2(&control, state->regs);

	execute_ALU( aluInput1, aluInput2,
	             control.ALU.op, control.ALU.bNegate,
	            &aluResult);
	memcpy(&aluResult_save, &aluResult, sizeof(aluResult));

	if (debug)
	{
		printf("  --\n");
		printf("  ALU.result=0x%04x_%04x\n",
		       (aluResult.result >> 16) & 0xffff,
		        aluResult.result        & 0xffff);
		printf("  ALU.zero  =%d\n", aluResult.zero);
	}



	// STEP 4: handle the memory operations (if any)
	rtVal = state->regs[control.rt];

	execute_MEM(&control, &aluResult, rtVal, state->dataMemory,
	            &memResult);
	memcpy(&memResult_save, &memResult, sizeof(memResult));

	if (debug)
	{
		printf("  --\n");
		printf("  memResult.readVal=0x%04x_%04x\n",
		       (memResult.readVal >> 16) & 0xffff,
		        memResult.readVal        & 0xffff);
		printf("  --\n");
	}


	// STEP 5: update the PC
	state->pc = getNewPC(&control, aluResult.zero, state->pc);
	if (state->pc == state_save.pc)
	{
		printf("ERROR: The PC did not change!\n");
		fail = 1;
	}

	if ((state->pc & 0x3) != 0)
	{
		printf("ERROR: The new Program Counter 0x%04x_%04x is not a multiple of 4!\n",
		       (state->pc >> 16) & 0xffff, state->pc & 0xffff);
		return 1;
	}


	// STEP 6: update registers
	execute_updateRegs(&control, &aluResult, &memResult, state->regs);


	// AFTER THE INSTRUCTION: COMPARE THE VARIOUS STRUCTS

	/* control should not have changed - except that we won't compare
	 * the 'extra' fields
	 */
	if (memcmp(&control_save, &control, sizeof(control)-3*sizeof(WORD)) != 0)
	{
		printf("ERROR: The Control struct changed somewhere in the testcase, after the original call to execute_Control().\n");
	}

	if (memcmp(&aluResult_save, &aluResult, sizeof(aluResult) != 0))
	{
		printf("ERROR: The ALUResult struct changed somewhere in the testcase, after the original call to execute_ALU().\n");
	}

	if (memcmp(&memResult_save, &memResult, sizeof(memResult) != 0))
	{
		printf("ERROR: The MemResult struct changed somewhere in the testcase, after the original call to execute_MEM().\n");
	}


	/* changs to the CPUMemory struct are not errors.  At least, not
	 * necessarily
	 */
	if (debug)
	printf("  PC was: 0x%04x_%04x is: 0x%04x_%04x\n",
	       (state_save.pc >> 16) & 0xffff, state_save.pc & 0xffff,
	       (state    ->pc >> 16) & 0xffff, state    ->pc & 0xffff);

	for (i=0; i<32; i++)
	if (state_save.regs[i] != state->regs[i])
	{
		if (debug)
		printf("  reg[%2d] was: 0x%04x_%04x is 0x%04x_%04x\n",
		       i,
		       state_save.regs[i] >> 16, state_save.regs[i] & 0xffff,
		       state    ->regs[i] >> 16, state    ->regs[i] & 0xffff);
	}

	for (i=0; i<sizeof(state->dataMemory)/sizeof(state->dataMemory[0]); i++)
	if (state_save.dataMemory[i] != state->dataMemory[i])
	{
		if (debug)
		printf("  mem[%2d] was: 0x%04x_%04x is 0x%04x_%04x\n",
		       i,
		       state_save.dataMemory[i] >> 16, state_save.dataMemory[i] & 0xffff,
		       state    ->dataMemory[i] >> 16, state    ->dataMemory[i] & 0xffff);
	}

	if (debug)
		printf("\n");

	return fail;
}



int execSyscall(CPUMemory *state)
{
	WORD v0 = state->regs[2];
	WORD a0 = state->regs[4];

	// syscall 10: exit
	if (v0 == 10)
	{
		printf("--- syscall 10 executed: Normal termination of the assembly language program.\n");
		return 1;
	}


	// syscall 1: print_int
	if (v0 == 1)
		printf("%d", a0);

	// syscall 11: print_char
	else if (v0 == 11)
		printf("%c", a0);


	// syscall 4: print_str
	else if (v0 == 4)
		printf("%s", ((char*)state->dataMemory)+a0);


	// unrecognized syscall
	else
		printf("--- ERROR: Unrecognized syscall $v0=%d\n", v0);

	return 0;
}


