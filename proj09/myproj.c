#include <stdio.h>

int main(){

	int x = 2350514280;

	int opcode = (x & 0xFC000000) >> 26;
	int rs = (x & 0x03E00000) >> 21;
	int rt = (x & 0x001F0000) >> 16;
	int rd = (x & 0x0000F800) >> 11;
	int shamt = (x & 0x000007C0) >> 6;
	int funct = (x & 0x0000003F);
	int imm16 = x & 0x0000FFFF;

	printf("x= %d\n", x);
	printf("opcode= %d\n", opcode);
	printf("x= %d\n", x);
	printf("rs= %d\n", rs);
	printf("rt= %d\n", rt);
	printf("rd= %d\n", rd);
	 printf("shamt= %d\n", shamt);
        printf("funct= %d\n", funct);
	printf("imm16= %d\n", imm16);

 	return 0;
}
