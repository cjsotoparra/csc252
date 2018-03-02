#ifndef __PROJ09_H__INCLUDED__
#define __PROJ09_H__INCLUDED__



typedef int WORD;



typedef struct IF_ID
{
	// these control bits are set by the IF phase, which is provided by
	// the testcase.  You will read them, but you don't have to set them!
	WORD pc;
	WORD instruction;
} IF_ID;



typedef struct ID_branchControl
{
	// YOU MUST SET THESE FIELDS IN execute_ID()
	//
	// stallIF (1 bit) - if you set this bit, then the IF phase will
	//           *NOT MODIFY* either the program counter, or the IF/ID
	//           pipeline register.  Use this to "freeze" the program for
	//           one cycle, to insert a stall.
	//
	//           Note that you still must set the control bits in the
	//           ID/EX pipeline register, to force a NOP.
	//
	// branch (1 bit) - Use this to implement a branch or jump.  If you
	//           set this, then the IF phase will set PC=branchDest (see
	//           below).  On the next clock cycle, you will see the new
	//           instruction, fetched from the new PC.
	//
	//           Note that this bit is not accurate to the real hardware.
	//           In the real hardware, the Instruction Fetch has already
	//           begun before you could set this, so the next instruction
	//           will be at oldPC+4.  (This is the branch delay slot.)
	//           But we're skipping that in our program.
	//
	// branchDest (32 bits) - If branch=1, then this is the new PC.

	int  stallIF;      // 1 bit

	int  branch;       // 1 bit
	WORD branchDest;   // 32 bits
} ID_branchControl;



typedef struct ID_EX
{
	// these are bits decoded from the instruction.  See Program 9.

	int rs, rt, rd;		// 5 bits each
	int shamt;              // 5 bits

	int imm16, imm32;	// immediate field, plus its sign-extended
	                        // version.  Of course, imm16 is a 32-bit
	                        // variable in C.  So you can *ALSO* use it
	                        // as the "zero extended" immediate field.


	// these are the two registers, which were read from the register
	// file.
	WORD rsVal, rtVal;


	// these are control bits, which were generated based on the
	// opcode/funct.  They are the same as in Program 9 - although
	// the branch/jump fields have been removed.
	//
	// Note that we still have the 3 'extra' fields, for you to use
	// however you wish.

	int ALUsrc;
	struct {
		int bNegate;
		int op;
	} ALU;

	int memRead;
	int memWrite;
	int memToReg;

	int regDst;
	int regWrite;

	WORD extra1, extra2, extra3;
} ID_EX;



typedef struct EX_MEM
{
	// these fields are (roughly) the same ones from the previous phase,
	// minus the ones that we've used, plus the ALU result.  Note that
	// we've used the 'regDst' (1 bit) control to choose the destination
	// register, which is now the (5 bit) 'destReg' field.

	WORD rtVal;      // useful for SW

	int memRead, memWrite, memToReg;      // 1 bit each

	int destReg;    // 5 bits
	int regWrite;   // 1 bit

	WORD aluResult;

	// If you need extra fields, I have them available for you...
	WORD extra1, extra2, extra3;
} EX_MEM;



typedef struct MEM_WB
{
	// in the official MIPS design, we carry the ALUresult and MEMresult
	// into the WB phase - and then we use memToReg in that phase.  Do
	// the same in your code.
	int  memToReg;
	WORD aluResult;
	WORD memResult;

	int destReg;     // 5 bits
	int regWrite;    // 1 bit

	WORD extra1, extra2, extra3;
} MEM_WB;




/* ------------------ EXECUTE METHODS -----------------------
 *
 * Each of these methods takes a pointer to the "input" pipeline register,
 * and also (except for WB) to the "output" pipeline register.  Read
 * values from the input, and set the proper bits in the output.
 *
 * Several of the phases also take pointers to *OTHER* phases.  This allows
 * you to read the current state of other pipeline registers, so that you
 * can do (for instance) data forwarding and LW stalling.
 *
 * A couple of phases (ID, WB) also take a pointer to the array of registers.
 * This is a 34 (not 32!) element array: the last two are 'lo' and 'hi'.  If
 * you choose to implement the 'mult' or 'div' instructions, use these two
 * registers.  Otherwise, they should never change.
 *
 * MEM, of course, gets a pointer to the array of data words.
 *
 * The testcases will implement the IF phase for you.
 */



/* in the ID phase, you have a return value: return 0 to indicate "OK" and
 * 1 to indicate "ERROR".  (This is the equivalent of the 'err' field from
 * Project 9.)
 *
 * The rest of the phases have no ability to report an error; they simply
 * must do their work.
 */

int execute_ID(IF_ID *in, WORD *regs, ID_EX *old_idex,
               ID_branchControl *branchControl_out, ID_EX *new_idex);

void execute_EX(ID_EX *in, EX_MEM *old_exMem, MEM_WB *old_memWb,
                EX_MEM *new_exMem);

void execute_MEM(EX_MEM *in, WORD *mem, MEM_WB *out);

void execute_WB (MEM_WB *in, WORD *regs);



/* HELPER FUNCTIONS THAT YOU CAN CALL */

static inline WORD signExtend16to32(int val16)
{
	if (val16 & 0x8000)
		return val16 | 0xffff0000;
	else
		return val16;
}


#endif

