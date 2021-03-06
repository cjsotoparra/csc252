#ifndef TEST_COMMONCODE_H
#define TEST_COMMONCODE_H



/* these functions test the various stages of the processor. */

int  Test_ID (IF_ID *in, WORD *regs,
              ID_EX *out, ID_branchControl *bcOut,
              ID_EX *old_idex);
void Test_EX (ID_EX *in, EX_MEM *out, EX_MEM *old_exMem, MEM_WB *old_memWb);
void Test_MEM(EX_MEM *in, WORD *mem, int memSizeWords, MEM_WB *out);
void Test_WB (MEM_WB *in, WORD *regs);

/* this function tests the full processor in pipelined mode, but it uses a
 * hard-coded sequence of instructions (it ignores branching).  The caller
 * provides pre-filled IF/ID registers (including PC values).
 */
void Test_Pipelined_FixedSequence(IF_ID *ifid, int instCount,
                                  WORD *regs,
                                  WORD *dataMemory, int dataMemSizeWords);

/* this function tests a realistic processor: the caller gives a series of
 * INSTRUCTIONS (in memory), and branches are honored.
 *
 * This terminates on an 'error' (from execute_ID()) or on syscall 10.
 *
 * NOTE: It includes a 'codeOffset' field; this is the effective address of
 * the instruction at element [0].
 */
void Test_FullProcessor(WORD *instMemory, int instMemSizeWords,
                        WORD *regs,
                        WORD *dataMemory, int dataMemSizeWords,
                        WORD  codeOffset);


/* this version simply executes the instructions, in a pipelined fashion,
 * without any debugging printfs.  It's a stripped-down version of
 * Test_FullProcessor()
 */
void ExecProcessor(WORD *instMemory, int instMemSizeWords,
                   WORD *regs,
                   WORD *dataMemory, int dataMemSizeWords,
                   WORD  codeOffset);


/* a helper function, used by some of the simulator functions above. */
int execSyscall(WORD *regs, WORD *dataMemory);


/* these macros are useful for encoding instructions.
 *
 * The first few are macros that allow us to generate some register
 * numbers.
 */
#define S_REG(X) ((X)+16)
#define T_REG(X) ((X) < 8 ? (X)+8 : (X)+24)
#define A_REG(X) ((X)+4)
#define V_REG(X) ((X)+2)
#define RA_REG    31
#define SP_REG    29
#define FP_REG    30
#define REG_ZERO   0


/* The next three are macros that represent the three instruction formats */
#define R_FORMAT(funct, rs,rt,rd, shamt) (( 0x00                << 26)  |  \
                                          (((rs    ) &    0x1f) << 21)  |  \
                                          (((rt    ) &    0x1f) << 16)  |  \
                                          (((rd    ) &    0x1f) << 11)  |  \
                                          (((shamt ) &    0x1f) <<  6)  |  \
                                          (((funct ) &    0x3f) <<  0))

#define I_FORMAT(opcode, rs,rt, imm16)   ((((opcode) &    0x3f) << 26)  |  \
                                          (((rs    ) &    0x1f) << 21)  |  \
                                          (((rt    ) &    0x1f) << 16)  |  \
                                          (((imm16 ) & 0x0ffff) <<  0))

#define J_FORMAT(opcode, addr26)         ((((opcode) &      0x3f) << 26)  |    \
                                          (((addr26) & 0x3ffffff) <<  0))



/* these macros encode various instructions.  Each uses the format macros
 * above to actually do the encoding.
 */
#define  ADD(rd, rs,rt)      R_FORMAT(32, rs,rt,rd, 0)
#define  ADDU(rd, rs,rt)     R_FORMAT(33, rs,rt,rd, 0)
#define  SUB(rd, rs,rt)      R_FORMAT(34, rs,rt,rd, 0)
#define  SUBU(rd, rs,rt)     R_FORMAT(35, rs,rt,rd, 0)
#define ADDI(rt, rs,imm16)   I_FORMAT( 8, rs,rt,imm16)
#define ADDIU(rt, rs,imm16)  I_FORMAT( 9, rs,rt,imm16)

#define LUI(rt, imm16)       I_FORMAT(15,  0,rt,imm16)

#define  AND(rd, rs,rt)      R_FORMAT(36, rs,rt,rd, 0)
#define   OR(rd, rs,rt)      R_FORMAT(37, rs,rt,rd, 0)
#define ANDI(rt, rs,imm16)   I_FORMAT(12, rs,rt,imm16)
#define  ORI(rt, rs,imm16)   I_FORMAT(13, rs,rt,imm16)
#define  NOR(rd, rs,rt)      R_FORMAT(39, rs,rt,rd, 0)

#define  SLT(rd, rs,rt)      R_FORMAT(42, rs,rt,rd, 0)
#define SLTU(rd, rs,rt)      R_FORMAT(43, rs,rt,rd, 0)
#define SLTI(rt, rs,imm16)   I_FORMAT(10, rs,rt,imm16)

#define  SLL(rd, rt,shamt)   R_FORMAT(0,  0, rt,rd, shamt)
#define SLLV(rd, rt,rs)      R_FORMAT(4,  rs,rt,rd, 0)
#define  SRL(rd, rt,shamt)   R_FORMAT(2,  0, rt,rd, shamt)
#define SRLV(rd, rt,rs)      R_FORMAT(6,  rs,rt,rd, 0)
#define  SRA(rd, rt,shamt)   R_FORMAT(3,  0, rt,rd, shamt)
#define SRAV(rd, rt,rs)      R_FORMAT(7,  rs,rt,rd, 0)

#define LW(rt, rs,imm16)     I_FORMAT(35, rs,rt,imm16)
#define SW(rt, rs,imm16)     I_FORMAT(43, rs,rt,imm16)

#define BEQ(rs,rt, imm16)    I_FORMAT(4,  rs,rt,imm16)
#define BNE(rs,rt, imm16)    I_FORMAT(5,  rs,rt,imm16)
#define   J(address)         J_FORMAT(2,  address)
#define JAL(address)         J_FORMAT(3,  address)
#define  JR(rs)              R_FORMAT(8, rs, 0,0,0)

#define SYSCALL()            R_FORMAT(12, 0,0,0, 0)

#define NOP()                0x00000000


#endif

