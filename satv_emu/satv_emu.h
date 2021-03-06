#ifndef __satv__emu__h
#define __satv__emu__h
#include<stdint.h>

/*
	the index in the list of functions pointers
*/

/*
	add has index of (0)
*/
#define _satve_add 0
/*
	movi has index of (1)
*/
#define _satve_movi 1
/*
	out has index of (2)
*/
#define _satve_out 2
/*
	bank has index of (3)
*/
#define _satve_bank 3


/*
	has no index
*/
#define _satve_exit 4
struct satve_context{
	/*
		the block of ram we are going on,

		bank(0) = 0
		bank(1) = 16
		bank(2) = 32
	*/
	uint16_t bank;
	/*
		we store are program as well as other stuff here.
	*/
	uint8_t ram[256];
	/*
		the instruction pointer
	*/
	uint16_t ip;
};
void satve_exec(struct satve_context*,uint16_t);
#endif/*__satv__emu__h*/
