#include <stdio.h>
#include <memory.h>
#include <malloc.h>

#include "proj11.h"
#include "proj11_test_commonCode.h"



int Test_ID(IF_ID *in, WORD *regs,
            ID_EX *out, ID_branchControl *bcOut,
            ID_EX *old_idex)
{
	IF_ID in_save;
	WORD  regs_save[32];
	  memcpy(&  in_save, in,   sizeof(  in_save));
	  memcpy( regs_save, regs, sizeof(regs_save));

	// if the caller didn't provide a BC to fill in, we'll provide one.
	ID_branchControl bc_mine;
	if (bcOut == NULL)
		bcOut = &bc_mine;

	memset(bcOut, -1, sizeof(*bcOut));
	memset(  out, -1, sizeof(*  out));

	// if the caller didn't provide an old ID/EX version, then we'll
	// provide a NOP.
	ID_EX nop;
	  memset(&nop, 0, sizeof(nop));
	if (old_idex == NULL)
		old_idex = &nop;

	ID_EX old_idex_save;
	  memcpy(&old_idex_save, old_idex, sizeof(old_idex_save));


	printf("Before execute_ID(): pc=0x%04x_%04x instruction=0x%04x_%04x\n",
	       (in->pc          >> 16) & 0xffff,
	       (in->pc               ) & 0xffff,
	       (in->instruction >> 16) & 0xffff,
	       (in->instruction      ) & 0xffff);

	int rc = execute_ID(in, regs, old_idex, bcOut, out);

	if (memcmp(in, &in_save, sizeof(in_save)) != 0)
		printf("ERROR: execute_ID() modified the (old) IF_ID struct.\n");
	if (memcmp(old_idex, &old_idex_save, sizeof(old_idex_save)) != 0)
		printf("ERROR: execute_ID() modified the (old) ID_EX struct.\n");

	if (memcmp(regs, &regs_save, sizeof(regs_save)) != 0)
		printf("ERROR: execute_ID() modified the registers.\n");

	if (rc != 0)
	{
		// this is not always an error.  Maybe the instruction was
		// actually invalid?  So we'll just print out a message.
		printf("  execute_ID() returned %d\n", rc);
		return rc;
	}

	if (bcOut->stallIF != 0 || bcOut->branch != 0 || bcOut->branchDest != 0)
	{
		printf("  ID_branchControl.stallIF    = %d\n", bcOut->stallIF);
		printf("  ID_branchControl.branch     = %d\n", bcOut->branch);
		printf("  ID_branchControl.branchDest = 0x%04x_%04x\n",
		       (bcOut->branchDest >> 16) & 0xffff,
		       (bcOut->branchDest      ) & 0xffff);
		printf("  ---\n");
	}

	printf("  ID_EX.rs    = %d\n", out->rs);
	printf("  ID_EX.rt    = %d\n", out->rt);
	printf("  ID_EX.rd    = %d\n", out->rd);
	printf("  ID_EX.shamt = %d\n", out->shamt);
	printf("  ID_EX.imm16 = 0x%04x_%04x\n",
	       (out->imm16 >> 16) & 0xffff,
	       (out->imm16      ) & 0xffff);
	printf("  ID_EX.imm32 = 0x%04x_%04x\n",
	       (out->imm32 >> 16) & 0xffff,
	       (out->imm32      ) & 0xffff);
	printf("  ---\n");
	printf("  ID_EX.rsVal = 0x%04x_%04x\n",
	       (out->rsVal >> 16) & 0xffff,
	       (out->rsVal      ) & 0xffff);
	printf("  ID_EX.rtVal = 0x%04x_%04x\n",
	       (out->rtVal >> 16) & 0xffff,
	       (out->rtVal      ) & 0xffff);
	printf("  ---\n");
	printf("  ID_EX.ALUsrc      = %d\n", out->ALUsrc);
	printf("  ID_EX.ALU.bNegate = %d\n", out->ALU.bNegate);
	printf("  ID_EX.ALU.op      = %d\n", out->ALU.op);
	printf("  ---\n");
	printf("  ID_EX.memRead  = %d\n", out->memRead);
	printf("  ID_EX.memWrite = %d\n", out->memWrite);
	printf("  ID_EX.memToReg = %d\n", out->memToReg);
	printf("  ---\n");
	printf("  ID_EX.regDst   = %d\n", out->regDst);
	printf("  ID_EX.regWrite = %d\n", out->regWrite);

	printf("\n");

	return 0;
}


void Test_EX(ID_EX *in, EX_MEM *out, EX_MEM *old_exMem, MEM_WB *old_memWb)
{
	ID_EX in_save;
	  memcpy(&in_save, in, sizeof(in_save));

	memset(out, -1, sizeof(*out));

	// if the caller didn't provide an old EX/MEM or MEM/WBi, then we'll
	// provide a NOP.
	EX_MEM nop_exMem;
	MEM_WB nop_memWb;
	  memset(&nop_exMem, 0, sizeof(nop_exMem));
	  memset(&nop_memWb, 0, sizeof(nop_memWb));

	if (old_exMem == NULL)
		old_exMem = &nop_exMem;
	if (old_memWb == NULL)
		old_memWb = &nop_memWb;

	EX_MEM old_exMem_save;
	MEM_WB old_memWb_save;
	  memcpy(&old_exMem_save, old_exMem, sizeof(old_exMem_save));
	  memcpy(&old_memWb_save, old_memWb, sizeof(old_memWb_save));


	// there's no need for a preliminary printf(), because we probably
	// just finished Test_ID().


	execute_EX(in, old_exMem, old_memWb, out);


	if (memcmp(&in_save, in, sizeof(*in)) != 0)
		printf("ERROR: execute_EX() modified the (old) ID_EX struct.\n");
	if (memcmp(&old_exMem_save, old_exMem, sizeof(*old_exMem)) != 0)
		printf("ERROR: execute_EX() modified the (old) EX_MEM struct.\n");
	if (memcmp(&old_memWb_save, old_memWb, sizeof(*old_memWb)) != 0)
		printf("ERROR: execute_EX() modified the (old) MEM_WB struct.\n");


	printf("  EX_MEM.rtVal = 0x%04x_%04x\n",
	       (out->rtVal >> 16) & 0xffff,
	       (out->rtVal      ) & 0xffff);
	printf("  ---\n");
	printf("  EX_MEM.memRead  = %d\n", out->memRead);
	printf("  EX_MEM.memWrite = %d\n", out->memWrite);
	printf("  EX_MEM.memToReg = %d\n", out->memToReg);
	printf("  ---\n");
	printf("  EX_MEM.destReg  = %d\n", out->destReg);
	printf("  EX_MEM.regWrite = %d\n", out->regWrite);
	printf("  ---\n");
	printf("  EX_MEM.aluResult = 0x%04x_%04x\n",
	       (out->aluResult >> 16) & 0xffff,
	       (out->aluResult      ) & 0xffff);
	printf("\n");

	return;
}


void Test_MEM(EX_MEM *in, WORD *mem, int memSizeWords, MEM_WB *out)
{
	EX_MEM in_save;
	  memcpy(&in_save, in, sizeof(in_save));

	WORD *mem_save = malloc(sizeof(WORD)*memSizeWords);
	  memcpy(mem_save, mem, sizeof(WORD)*memSizeWords);

	memset(out, -1, sizeof(*out));


	execute_MEM(in, mem, out);


	if (memcmp(&in_save, in, sizeof(in_save)) != 0)
		printf("ERROR: execute_MEM() modified the (old) EX_MEM struct.\n");


	// memory modifications are normal - at least, for SW instructions
	int i;
	for (i=0; i<memSizeWords; i++)
	if (mem[i] != mem_save[i])
	{
		int addr = i*4;

		printf("  MEM CHANGED: Address=0x%04x_%04x   Was: 0x%04x_%04x Now: 0x%04x_%04x\n",
		       (addr        >> 16) & 0xffff,
		       (addr             ) & 0xffff,
		       (mem_save[i] >> 16) & 0xffff,
		       (mem_save[i]      ) & 0xffff,
		       (mem     [i] >> 16) & 0xffff,
		       (mem     [i]      ) & 0xffff);
	}


	printf("  MEM_WB.memToReg  = %d\n", out->memToReg);
	printf("  MEM_WB.aluResult = 0x%04x_%04x\n",
	       (out->aluResult >> 16) & 0xffff,
	       (out->aluResult      ) & 0xffff);
	printf("  MEM_WB.memResult = 0x%04x_%04x\n",
	       (out->memResult >> 16) & 0xffff,
	       (out->memResult      ) & 0xffff);
	printf("  ---\n");
	printf("  MEM_WB.destReg  = %d\n", out->destReg);
	printf("  MEM_WB.regWrite = %d\n", out->regWrite);
	printf("\n");

	free(mem_save);
	return;
}


void Test_WB(MEM_WB *in, WORD *regs)
{
	MEM_WB in_save;
	  memcpy(&in_save, in, sizeof(in_save));

	WORD regs_save[34];
	  memcpy(regs_save, regs, sizeof(regs_save));


	execute_WB(in, regs);


	if (memcmp(&in_save, in, sizeof(in_save)) != 0)
		printf("ERROR: execute_WB() modified the (old) MEM_WB struct.\n");


	// reigster modifications are normal, for many instructions
	int count = 0;
	int i;
	for (i=0; i<34; i++)
	if (regs[i] != regs_save[i])
	{
		count++;

		printf("  REGISTER %d CHANGED.  Was: 0x%04x_%04x Now: 0x%04x_%04x\n",
		       i,
		       (regs_save[i] >> 16) & 0xffff,
		       (regs_save[i]      ) & 0xffff,
		       (regs     [i] >> 16) & 0xffff,
		       (regs     [i]      ) & 0xffff);
	}

	printf("  A total of %d registers were changed.\n", count);
	printf("\n");

	return;
}


void Test_Pipelined_FixedSequence(IF_ID *ifid, int instCount,
                                  WORD  *regs,
                                  WORD  *dataMemory, int dataMemorySizeWords)
{
	ID_EX  idex [2];
	EX_MEM exmem[2];
	MEM_WB memwb[2];

	/* initialize all of the pipeline registers (except for ID/EX) to
	 * zero (NOP)
	 */
	memset(idex , 0, sizeof(idex));
	memset(exmem, 0, sizeof(exmem));
	memset(memwb, 0, sizeof(memwb));

	int i;
	for (i=0; i<instCount; i++)
	{
		// for every iteration of the pipeline, we run the WB phase
		// *FIRST* (to update registers).
		//
		// For the rest, the order is kind of arbitrary, since we
		// always read from [0] and write to [1].  However, we'll
		// choose to do the conventional ID, EX, MEM, just because it
		// looks nice.

		printf("-------------- Clock %d ---------------\n", i);
		printf("WB phase:\n");
		Test_WB(&memwb[0], regs);

		printf("ID phase:\n");
		Test_ID(&ifid[i], regs, &idex[1], NULL, &idex[0]);

		printf("EX phase:\n");
		Test_EX (&idex[0], &exmem[1], &exmem[0], &memwb[0]);

		printf("MEM phase:\n");
		Test_MEM(&exmem[0], dataMemory, dataMemorySizeWords, &memwb[1]);

		// copy each [1] back into [0] to be the input for the next
		// clock cycle.
		memcpy(&idex [0], &idex [1], sizeof(idex [0]));
		memcpy(&exmem[0], &exmem[1], sizeof(exmem[0]));
		memcpy(&memwb[0], &memwb[1], sizeof(memwb[0]));
	}

	return;
}


void Test_FullProcessor(WORD *instMemory, int instMemSizeWords,
                        WORD *regs,
                        WORD *dataMemory, int dataMemSizeWords,
                        WORD  codeOffset)
{
	/* this is largely similar to Test_PIpelined_FixedSequence(), except
	 * that instead of having an array of IF/ID registers already filled
	 * in, we dynamically fill one, basd on the current PC.
	 *
	 * Also, this supports syscalls.
	 */

	IF_ID  ifid [2];
	ID_EX  idex [2];
	EX_MEM exmem[2];
	MEM_WB memwb[2];

	/* initialize all of the pipeline registers (except for ID/EX) to
	 * zero (NOP)
	 */
	memset(ifid , 0, sizeof(ifid));
	memset(idex , 0, sizeof(idex));
	memset(exmem, 0, sizeof(exmem));
	memset(memwb, 0, sizeof(memwb));

	/* except, that the first IF/ID must be initialized with the 
	 * starting PC.
	 */
	ifid[0].pc          = codeOffset;
	ifid[0].instruction = instMemory[0];

	int clock = 0;
	while (1)
	{
		// for every iteration of the pipeline, we run the WB phase
		// *FIRST* (to update registers).
		//
		// For the rest, the order is kind of arbitrary, since we
		// always read from [0] and write to [1].  However, we'll
		// choose to do the conventional ID, EX, MEM, just because it
		// looks nice.

		ID_branchControl bc;
		  memset(&bc, -1, sizeof(bc));

		printf("-------------- Clock %d ---------------\n", clock);
		printf("WB phase:\n");
		Test_WB(&memwb[0], regs);

		printf("ID phase:\n");

		if (ifid[0].instruction == SYSCALL())
		{
			// handle syscalls locally
			if (execSyscall(regs, dataMemory) != 0)
				return;

			// turn it into a NOP
			memset(&bc     , 0, sizeof(bc));
			memset(&idex[1], 0, sizeof(idex[1]));
		}
		else
		{
			// orinary instructions
			int rc = Test_ID(&ifid[0], regs,
			                 &idex[1], &bc,
			                 &idex[0]);
			if (rc != 0)
			{
				printf("Test_FullProcessor(): Ending program because execute_ID() returned %d\n", rc);
				return;
			}
		}

		// figure out the proper PC for the new IF/ID; also, fill in
		// the proper instruction.
		if (bc.stallIF)
			memcpy(&ifid[1], &ifid[0], sizeof(ifid[1]));
		else
		{
			if (bc.branch)
				ifid[1].pc = bc.branchDest;
			else
				ifid[1].pc = ifid[0].pc+4;

			int instIndx = (ifid[1].pc - codeOffset)/4;

			if (instIndx <  0                ||
			    instIndx >= instMemSizeWords ||
			    ifid[1].pc % 4 != 0)
			{
				printf("ERROR: Invalid Program Counter 0x%08x\n", ifid[0].pc);
				return;
			}

			ifid[1].instruction = instMemory[instIndx];
		}


		printf("EX phase:\n");
		Test_EX (&idex[0], &exmem[1], &exmem[0], &memwb[0]);

		printf("MEM phase:\n");
		Test_MEM(&exmem[0], dataMemory, dataMemSizeWords, &memwb[1]);


		// copy each [1] back into [0] to be the input for the next
		// clock cycle.
		memcpy(&ifid [0], &ifid [1], sizeof(ifid [0]));
		memcpy(&idex [0], &idex [1], sizeof(idex [0]));
		memcpy(&exmem[0], &exmem[1], sizeof(exmem[0]));
		memcpy(&memwb[0], &memwb[1], sizeof(memwb[0]));

		clock++;
	}
}


void ExecProcessor(WORD *instMemory, int instMemSizeWords,
                   WORD *regs,
                   WORD *dataMemory, int dataMemSizeWords,
                   WORD  codeOffset)
{
	/* this is basically the same function as Test_FullProcessor(),
	 * except that it calls the user functions directly, instead of
	 * using the Test*() functions (which do too much printing).
	 */

	IF_ID  ifid [2];
	ID_EX  idex [2];
	EX_MEM exmem[2];
	MEM_WB memwb[2];

	memset(ifid , 0, sizeof(ifid));
	memset(idex , 0, sizeof(idex));
	memset(exmem, 0, sizeof(exmem));
	memset(memwb, 0, sizeof(memwb));

	ifid[0].pc          = codeOffset;
	ifid[0].instruction = instMemory[0];

	while (1)
	{
		ID_branchControl bc;
		  memset(&bc, -1, sizeof(bc));

		execute_WB(&memwb[0], regs);

		if (ifid[0].instruction == SYSCALL())
		{
			if (execSyscall(regs, dataMemory) != 0)
				return;

			memset(&bc     , 0, sizeof(bc));
			memset(&idex[1], 0, sizeof(idex[1]));
		}
		else
		{
			int rc = execute_ID(&ifid[0], regs, &idex[0],
			           &bc, &idex[1]);
			if (rc != 0)
			{
				printf("ExecProcessor(): Ending program because execute_ID() returned %d\n", rc);
				return;
			}
		}

		if (bc.stallIF)
			memcpy(&ifid[1], &ifid[0], sizeof(ifid[1]));
		else
		{
			if (bc.branch)
				ifid[1].pc = bc.branchDest;
			else
				ifid[1].pc = ifid[0].pc+4;

			int instIndx = (ifid[1].pc - codeOffset)/4;

			if (instIndx <  0                ||
			    instIndx >= instMemSizeWords ||
			    ifid[1].pc % 4 != 0)
			{
				printf("ERROR: Invalid Program Counter 0x%08x\n", ifid[0].pc);
				return;
			}

			ifid[1].instruction = instMemory[instIndx];
		}


		execute_EX (&idex [0], &exmem[0], &memwb[0], &exmem[1]);
		execute_MEM(&exmem[0], dataMemory, &memwb[1]);


		// copy each [1] back into [0] to be the input for the next
		// clock cycle.
		memcpy(&ifid [0], &ifid [1], sizeof(ifid [0]));
		memcpy(&idex [0], &idex [1], sizeof(idex [0]));
		memcpy(&exmem[0], &exmem[1], sizeof(exmem[0]));
		memcpy(&memwb[0], &memwb[1], sizeof(memwb[0]));
	}
}


int execSyscall(WORD *regs, WORD *dataMemory)
{
	WORD v0 = regs[2];
	WORD a0 = regs[4];

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
		printf("%s", ((char*)dataMemory)+a0);


	// unrecognized syscall
	else
		printf("--- ERROR: Unrecognized syscall $v0=%d\n", v0);

	return 0;
}


