#include "satv_emu.h"
#include<stdio.h>
#include<string.h>
/*
	simple macros to bitshift are operands to the right locations
*/
#define loh(__x) (__x<<4)
#define roh(__x) (__x<<8)

/*
	we have instructions that look like
	_satve_{add,movi,out,bank,exit}

	FORMATTING:

_satve_add
	ADDRESS(X)     ADDRESS(Y)        OPCODE
	11-8           7-4               3-0     # bits
	xxxx           xxxx              0000

	# equation (Y = Y+X)

_satve_movi
	VALUE(X)    ADDRESS(Y)  OPCODE
	15-8        7-4         3-0              # bits
	iiiiiiii    xxxx        0001

	i = integer value 0-255

	# equation (Y = X)
	
_satve_out
	ADDRESS     OPCODE
	7-4         3-0
	0000        0010                         # bits

_satve_bank
	BANK(X)          OPCODE
	15-4             3-0
	000000000000     0011                         # bits

	# equation 

	satve_context.bank = X
*/

uint16_t program_code[] = {
	/* set to bank(0) */
	_satve_bank|loh(0),
	/* move the value 0x10 into address(0) */
	_satve_movi|loh(0)|roh(0x10),
	/* move the value 0x10 into address(1) */
	_satve_movi|loh(1)|roh(0x10),
	/* move the value 0x20 into address(2) */
	_satve_movi|loh(2)|roh(0x20),
	/* move the value 0x20 into address(3) */
	_satve_movi|loh(3)|roh(0x20),
	/* show the value at this location */
	_satve_out|loh(0),
	_satve_out|loh(2),
	/*
		0x1010 + 0x2020 = 0x3030 
	*/
	_satve_add|loh(0)|roh(2),
	/* show result from add instruction*/
	_satve_out|loh(0),
	_satve_exit	
};

/*
	the context
*/

#define PROGRAM_ADDRESS 128
struct satve_context ctx;
int main(){
	/*
		clear the memory 
	*/
	memset(ctx.ram,0xff,256);
	/*
		init context
	*/
	ctx.ip = 0;
	ctx.bank = 0;
	/*
		copy data located at program_code into are RAM at
		the location PROGRAM_ADDRESS
	*/
	memcpy(ctx.ram+PROGRAM_ADDRESS,program_code,sizeof(program_code));
	printf("running program.\n");
	/*
		we provide the functions with two arguments,
		the pointer of 'ctx' and the entry point to where the program
		is stored in RAM.
	*/
	satve_exec(&ctx,PROGRAM_ADDRESS);
}
