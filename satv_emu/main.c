#include "satv_emu.h"
#include<stdio.h>
#include<string.h>
#define loh(__x) (__x<<4)
#define roh(__x) (__x<<8)

uint16_t program_code[] = {
	/* set to bank(0) */
	_satve_bank|loh(0),
	/* move the value 0x41 into address(0) */
	_satve_movi|loh(0)|roh(0x41),
	/* move the value 0x41 into address(1) */
	_satve_movi|loh(1)|roh(0x41),
	/* show the value at this location */
	_satve_out|loh(0),
	_satve_exit	
};

struct satve_pgm are_program = {
	.data = 128,
	.len = sizeof(program_code)
};
/*
	the context
*/
struct satve_context ctx;
int main(){
	/*
		clear the memory 
	*/
	memset(ctx.ram,0xff,256);
	ctx.ip = 0;
	ctx.bank = 0;

	memcpy(ctx.ram+are_program.data,program_code,are_program.len);
	printf("running program.\n");
	satve_exec(&ctx,&are_program);
}
