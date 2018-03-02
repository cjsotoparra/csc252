#ifndef __PROJ09_H__INCLUDED__
#define __PROJ09_H__INCLUDED__


typedef int WORD;


typedef struct CPUMemory
{
	// INSTRUCTION & DATA MEMORY
	//
	// It is *NOT* realistic to have the instruction memory and the data
	// memory be two sepearte memories.  See "von Neumann architecture" on
	// Wikipedia to see how real computers work.  But, it simplifies the
	// code for our little toy processor to pretend that they are
	// separate.
	//
	// The instruction memory is READ ONLY.
	//
	// The data memory is read/write.

	WORD instMemory[   1024];
	WORD dataMemory[16*1024];

	// REGISTERS
	WORD pc;
	WORD regs[32];
} CPUMemory;



typedef struct CPUControl
{
	// THESE ARE NOT ACTUALLY CONTROL BITS
	//
	// However, you have to fill them out.  Fill out *all* of these fields
	// for *all* instructions, even if it doesn't use that particular
	// field.  For instance, opcode 0 means that it is an R format
	// instruction - but you *still* must set the proper values for imm16,
	// imm32, and address.
	//
	// NOTE: imm16 is the field from the instruction,  imm32 is the
	//       sign-extended version.
	int opcode;
	int rs;
	int rt;
	int rd;
	int shamt;
	int funct;
	int imm16, imm32;
	int address;		// this is the 26 bit field from the J format


	// THIS IS A SPECIAL CONTROL BIT, JUST FOR THIS PROJECT
	//
	// You must *ALWAYS* fill in all of the fields above.  But then,
	// *AFTER* you have done that, check the opcode and funct fields.  if
	// they are not something that you recognize, then set this bit to 1,
	// and change *NOTHING* below.  But if it is an opcode/funct that you
	// recognize, then set this field to zero, and then also set all of
	// the other fields below as well.
	//
	// In real hardware, this sort of situation triggers an exception -
	// which probably means that the OS will kill your program.
	int err;


	// THESE ARE THE REAL CONTROL BITS
	//
	// For the ALU control bits, we will ignore the fact that the "main"
	// control produces a 2-bit value, which is combined with the funct
	// field to produce a 3-bit control (bNegate+ALUop).  We'll ignore the
	// 2-bit from the main control; we will *only* report the 3-bit
	// control that comes out of the ALU Control field.
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

	int branch;
	int jump;


	// EXTRA WORDS
	//
	// You are not required to use these fields.  But if you want to
	// supoprt other instructiosn, some additional control bits might be
	// necessary.  You may use these fields for anything you want; the
	// testcases will ignore them.
	WORD extra1, extra2, extra3;
} CPUControl;



typedef struct ALUResult
{
	int result;
	int zero;
} ALUResult;

typedef struct MemResult
{
	int readVal;
} MemResult;



WORD getInstruction(CPUMemory *state);

void execute_CPUControl(WORD instruction, CPUControl *controlOut);

WORD getALUinput1(CPUControl *controlIn, WORD *regs);
WORD getALUinput2(CPUControl *controlIn, WORD *regs);

void execute_ALU(WORD input1, WORD input2,
                 int  aluOp,  int  bNegate,
                 ALUResult *aluResultOut);

void execute_MEM(CPUControl *controlIn,
                 ALUResult  *aluResultIn,
                 WORD        rtVal,
                 WORD       *memory,
                 MemResult  *resultOut);

WORD getNewPC(CPUControl *control, int aluZero, WORD oldPC);

void execute_updateRegs(CPUControl *controlIn,
                        ALUResult  *aluResultIn, MemResult *memResultIn,
                        WORD       *regs);



/* HELPER FUNCTIONS THAT YOU CAN CALL */

static inline WORD signExtend16to32(int val16)
{
	if (val16 & 0x8000)
		return val16 | 0xffff0000;
	else
		return val16;
}


#endif

