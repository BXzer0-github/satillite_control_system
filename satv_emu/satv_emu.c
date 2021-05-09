#include "satv_emu.h"
#include<stdio.h>
/*
	this lets us read and write 16-bit words
*/
#define ram(__ct,__loc) ((uint16_t*)((__ct)->ram+((__loc)|(__ct)->bank)))[0]
/*
	this is for single bytes
*/
#define ram8(__ct,__loc) (__ct)->ram[(__loc)|(__ct)->bank]

/*
	add two 16-bit unsigned int stored at two locations within RAM 
*/
void static satve_add(struct satve_context *ct,uint16_t data) {
	printf("# got add instruction.\n");
	uint16_t loh,roh;
	/*
		the opcode is 4-bits so we shift to the right by 4-bits,
		the addresses are 4-bits so we AND with 0xf or 1111 in binary.
	*/
	loh = (data>>4)&0xf;
	roh = (data>>(4+4))&0xf;

	/*
		we add them together
	*/
	ram(ct,loh) = ram(ct,loh)+ram(ct,roh);
}

/*
	store 8-bit immediate value into location within RAM
*/
void static satve_movi(struct satve_context *ct,uint16_t data) {
	printf("# got movi instruction.\n");
	uint16_t dst,val;
	dst = (data>>4)&0xf;
	val = data>>8;

	ram8(ct,dst) = val;
}

/*
	take the location of RAM specified within instruction and print the data stored at that location in HEX
*/
void static satve_out(struct satve_context *ct,uint16_t data) {
	printf("# got out instruction.\n");
	uint16_t addr;
	/*
		same as for the add routine
	*/
	addr = (data>>4)&0xf;

	uint16_t word;
	word = ram(ct,addr);
	printf("data at %x shows %x(%u).\n",addr,word,word);
}


/*
	as instructions are restricted to being 16-bits, 
	theres a limitation on address size.

	ram addresses are 8-bits

  BANK        ADDRESS from instruction
	0000        0000

	the bank value makes up the higher 4-bits of the address,
	while the other 4-bits comes from are instruction.

*/
void static satve_bank(struct satve_context *ct,uint16_t data) {
	printf("# got bank instruction.\n");
	uint16_t bank;
	bank = data>>4;
	ct->bank = bank<<4;
}

/*
	example
*/
void static satve_template(struct satve_context *ct,uint16_t data){

}

/*
	a list of pointers to the functions for the operations.
*/
void(*optab[])(struct satve_context*,uint16_t) = {
	satve_add,		// index (0)
	satve_movi,		// index (1)
	satve_out,		// index (2)
	satve_bank,		// index (3)
	satve_template
};

/*
	another way to look at it.

	optab[0] = satve_add;
	optab[1] = satve_movi;
	optab[2] = satve_out;
	optab[3] = satve_bank;
*/

void satve_exec(struct satve_context *ct, uint16_t entry){
	uint16_t opc;
	/*
		set the instruction pointer to point to the first instruction in are program
	*/
	ct->ip = entry;
	uint16_t in;
	while(1){
		/*
			the instruction
			we cast to 16-bit as thats how big the instructions are.

			ct->ip = location of instruction word(16-bit) in the RAM.
		*/
		in = ((uint16_t*)(ct->ram+ct->ip))[0];
		printf("# %x.\n",in);
		/*
			first 4-bits are the opcode
		*/
		opc = in&0xf;
		/*
			if we get the exit opcode then break out of loop thus ending program
		*/
		if(opc == _satve_exit){
			printf("# got exit instruction.\n");
			break;
		}
		/*
			if its not an exit opcode then we do this
		*/
		optab[opc](ct,in);
		/*
			we increment by 2, because 16-bit = two bytes
		*/
		ct->ip+=2;
	}
}

