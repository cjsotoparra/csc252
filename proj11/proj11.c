/*File:  proj11.c
  Author:  Christian Soto
  Purpose:  The purpose of this file is to implement a full
            pipelined cpu.
*/


#include <string.h>
#include <stdio.h>
#include "proj11.h"


// R type func (opcode = 0)
#define JR   8
#define ADD  32
#define ADDU 33
#define SUB  34
#define SUBU 35
#define AND  36
#define OR   37
#define SLT  42
#define SLTU 43

// I type opcode
#define BEQ   4
#define BNE   5
#define ADDI  8
#define ADDIU 9
#define SLTI  10
#define SLTIU 11
#define ANDI  12
#define ORI   13
#define LW    35
#define SW    43

// J type opcode
#define J   2
#define JAL 3

// ALU control
#define ALU_AND 0
#define ALU_OR  1
#define ALU_ADD 2
#define ALU_SLT 3
#define ALU_NOP 4

typedef union {
	unsigned int word;
	struct {
		unsigned int func:6;
		unsigned int shamt:5;
		unsigned int rd:5;
		unsigned int rt:5;
		unsigned int rs:5;
		unsigned int opcode:6;
	} r;
	struct {
		unsigned int imm:16;
		unsigned int rt:5;
		unsigned int rs:5;
		unsigned int opcode:6;
	} i;
	struct {
		unsigned int addr:26;
		unsigned int opcode:6;
	} j;
} inst_t;


#define ID_EX_NOP() memset(new_idex, 0, sizeof(ID_EX))

int execute_ID(IF_ID *in, WORD *regs, ID_EX *old_idex, ID_branchControl *branchControl_out, ID_EX *new_idex)
{
	memset(branchControl_out, 0, sizeof(ID_branchControl));
	ID_EX_NOP();

	inst_t inst;
	// copy the values
	inst.word = in->instruction;
	new_idex->rs = inst.r.rs;
	new_idex->rt = inst.r.rt;
	new_idex->rd = inst.r.rd;
	new_idex->shamt = inst.r.shamt;
	new_idex->imm16 = inst.i.imm;
	new_idex->imm32 = signExtend16to32(inst.i.imm);
	// r0 is always 0
	new_idex->rsVal = inst.r.rs > 0 ? regs[inst.r.rs] : 0;
	new_idex->rtVal = inst.r.rt > 0 ? regs[inst.r.rt] : 0;
	// set the appropriate control lines for each instruction
	if (inst.word == 0) { // nop
		new_idex->ALU.op = ALU_NOP;
		new_idex->regDst = 1;
		new_idex->regWrite = 1;
	} else if (inst.r.opcode == 0) { // R type
		new_idex->regDst = 1;
		new_idex->regWrite = 1;
		switch (inst.r.func) {
			case JR:
				branchControl_out->branch = 1;
				branchControl_out->branchDest = new_idex->rsVal;
				ID_EX_NOP();
				break;
			case ADD:
			case ADDU:
				new_idex->ALU.op = ALU_ADD;
				break;
			case SUB:
			case SUBU:
				new_idex->ALU.op = ALU_ADD;
				new_idex->ALU.bNegate = 1;
				break;
			case AND:
				new_idex->ALU.op = ALU_AND;
				break;
			case OR:
				new_idex->ALU.op = ALU_OR;
				break;
			case SLT:
				new_idex->ALU.op = ALU_SLT;
				new_idex->ALU.bNegate = 1;
				break;
			case SLTU:
				new_idex->ALU.op = ALU_SLT;
				new_idex->ALU.bNegate = 1;
				// use extra1 to indicate unsigned comparison
				new_idex->extra1 = 1;
				break;
			default:
				// unsupported
				return -1;
		}
	}
	else if (inst.i.opcode >= 4) { // I type
		switch (inst.i.opcode) {
			case ANDI:
				new_idex->ALU.op = ALU_AND;
				new_idex->ALUsrc = 2;
				new_idex->regWrite = 1;
				break;
			case ORI:
				new_idex->ALU.op = ALU_OR;
				new_idex->ALUsrc = 2;
				new_idex->regWrite = 1;
				break;
			case BEQ:
				if (new_idex->rsVal == new_idex->rtVal) {
					branchControl_out->branch = 1;
					branchControl_out->branchDest = in->pc + 4 + (new_idex->imm32 << 2);
				}
				ID_EX_NOP();
				break;
			case BNE:
				if (new_idex->rsVal != new_idex->rtVal) {
					branchControl_out->branch = 1;
					branchControl_out->branchDest = in->pc + 4 + (new_idex->imm32 << 2);
				}
				ID_EX_NOP();
				break;
			case ADDI:
			case ADDIU:
				new_idex->ALUsrc = 1;
				new_idex->ALU.op = ALU_ADD;
				new_idex->regWrite = 1;
				break;
			case SLTI:
				new_idex->ALUsrc = 1;
				new_idex->ALU.op = ALU_SLT;
				new_idex->ALU.bNegate = 1;
				new_idex->regWrite = 1;
				break;
			case SLTIU:
				new_idex->ALUsrc = 1;
				new_idex->ALU.op = ALU_SLT;
				new_idex->ALU.bNegate = 1;
				new_idex->regWrite = 1;
				// use extra1 to indicate unsigned comparison
				new_idex->extra1 = 1;
				break;
			case LW:
				new_idex->ALUsrc = 1;
				new_idex->ALU.op = ALU_ADD;
				new_idex->memRead = 1;
				new_idex->regWrite = 1;
				new_idex->memToReg = 1;
				break;
			case SW:
				new_idex->ALUsrc = 1;
				new_idex->ALU.op = ALU_ADD;
				new_idex->memWrite = 1;
				break;
			default:
				// unsupported
				return -1;
		}
	} else if (inst.j.opcode == J || inst.j.opcode == JAL) { // J type
		branchControl_out->branch = 1;
		branchControl_out->branchDest = ((in->pc + 4) & 0xf0000000) | (inst.j.addr << 2);
		ID_EX_NOP();
		if (inst.j.opcode == JAL) {
			// save return address
			new_idex->rt = 31;
			new_idex->imm32 = in->pc + 4;
			new_idex->ALUsrc = 1;
			new_idex->ALU.op = ALU_ADD;
			new_idex->regWrite = 1;
		}
	} else {
		return -1;
	}
	// LW stall
	if (!old_idex->regDst && old_idex->memRead && old_idex->regWrite &&
		(old_idex->rt == new_idex->rs || old_idex->rt == new_idex->rt)) {
		branchControl_out->stallIF = 1;
		ID_EX_NOP();
	}
	return 0;
}

void execute_EX(ID_EX *in, EX_MEM *old_exMem, MEM_WB *old_memWb, EX_MEM *new_exMem)
{
	memset(new_exMem, 0, sizeof(EX_MEM));
	
	// copy values
	new_exMem->rtVal = in->rtVal;
	new_exMem->memRead = in->memRead;
	new_exMem->memWrite = in->memWrite;
	new_exMem->memToReg = in->memToReg;
	new_exMem->destReg = in->regDst ? in->rd : in->rt;
	new_exMem->regWrite = in->regWrite;
	
	int rsVal = in->rsVal;
	int rtVal = in->rtVal;
	// forward from MEM/WB
	//if (old_memWb->regWrite && old_memWb->destReg != 0) {
	if (old_memWb->regWrite) {
		if (old_memWb->destReg == in->rs) {
			rsVal = old_memWb->aluResult;
		}
		if (old_memWb->destReg == in->rt) {
			rtVal = old_memWb->aluResult;
		}
	}
	// forward from EX/MEM
	//if (old_exMem->regWrite && old_exMem->destReg != 0) {
	if (old_exMem->regWrite) {
		if (old_exMem->destReg == in->rs) {
			rsVal = old_exMem->aluResult;
		}
		if (old_exMem->destReg == in->rt) {
			rtVal = old_exMem->aluResult;
		}
	}
	// use extra2 for possibly forwarded rtVal for SW
	new_exMem->extra2 = rtVal;
	
	// get the second ALU source
	unsigned int src2 = 0;
	switch (in->ALUsrc) {
		case 0:
			src2 = rtVal;
			break;
		case 1:
			src2 = in->imm32;
			break;
		case 2:
			src2 = in->imm16;
			break;
	}
	// perform ALU operation
	if (in->ALU.bNegate) {
		src2 = -src2;
	}
	switch (in->ALU.op) {
		case ALU_AND:
			new_exMem->aluResult = rsVal & src2;
			break;
		case ALU_OR:
			new_exMem->aluResult = rsVal | src2;
			break;
		case ALU_ADD:
			new_exMem->aluResult = rsVal + src2;
			break;
		case ALU_SLT:
			if (in->extra1) {
				new_exMem->aluResult = (unsigned int)rsVal < (unsigned int)-src2;
			} else {
				new_exMem->aluResult = (int)rsVal < (int)-src2;
			}
			break;
	}
}

void execute_MEM(EX_MEM *in, WORD *mem, MEM_WB *out)
{
	memset(out, 0, sizeof(MEM_WB));
	// copy values
	out->memToReg = in->memToReg;
	out->aluResult = in->aluResult;
	out->destReg = in->destReg;
	out->regWrite = in->regWrite;
	
	if (in->memRead) {  // LW
		out->memResult = mem[in->aluResult >> 2];
	} else if (in->memWrite) {  // SW
		mem[in->aluResult >> 2] = in->extra2;
	}
}

void execute_WB(MEM_WB *in, WORD *regs)
{
	if (in->regWrite && in->destReg > 0) {
		regs[in->destReg] = in->memToReg ? in->memResult : in->aluResult;
	}
}
