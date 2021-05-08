#include "satv_emu.h"
#include<stdio.h>
#define ram(__ct,__loc) ((uint16_t*)((__ct)->ram+((__loc)|(__ct)->bank)))[0]
#define ram8(__ct,__loc) (__ct)->ram[(__loc)|(__ct)->bank]

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

void static satve_movi(struct satve_context *ct,uint16_t data) {
	printf("# got movi instruction.\n");
	uint16_t dst,val;
	dst = (data>>4)&0xf;
	val = data>>8;

	ram8(ct,dst) = val;
}


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

void static satve_bank(struct satve_context *ct,uint16_t data) {
	printf("# got bank instruction.\n");
	uint16_t bank;
	bank = data>>4;
	ct->bank = bank<<4;
}

void(*optab[])(struct satve_context*,uint16_t) = {
	satve_add,
	satve_movi,
	satve_out,
	satve_bank
};

void satve_exec(struct satve_context *ct, struct satve_pgm *pgm){
	uint16_t opc;
	
	ct->ip = 0;
	uint16_t in;
	while(1){
		/*
			the instruction
			we cast to 16-bit as thats how bit the instructions are
		*/
		in = ((uint16_t*)(ct->ram+pgm->data+ct->ip))[0];
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

