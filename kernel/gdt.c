
/**
* Nadia OS descriptor file .c
*
* This file describe 
*
* @author : kabong freddy
*/

/**
*														========= GDT REGISTER =========
*
*
*		63				59				55				51				47				43				39				35			   32
*		+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+
*		|            base 31:24         | g | d |   |   |  limit 19:16  |   |   |   |   |     type      |           base 23:16          |
*		+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+
*		|                           base 15:0                           |                           limit 15:0                          |
*		+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+
*		31				27				23				19				15				11				7				3				0
*															
*/

#ifndef NOS_GLOBAL_DESCRIPTOR_TABLE
#define NOS_GLOBAL_DESCRIPTOR_TABLE
#include "include/i386/memory.h"
#endif


gdt_desc_t gdt_entry[MAX_GDT];
gdt_reg_t gdt_ptr;

void init_gdt_sys(void){
	gdt_ptr.limit = 8*MAX_GDT-1;
	gdt_ptr.base = (unsigned int) &gdt_entry;

	fn_gdt_desc(0,0x0,0x0,0x0,0x0);
	fn_gdt_desc(1,0,0xFFFFFFFF, 0x9A, 0xCF);
	fn_gdt_desc(2,0,0xFFFFFFFF, 0x92, 0xCF);
	fn_gdt_desc(3,0,0xFFFFFFFF,0xFA, 0xCF);
	fn_gdt_desc(4,0,0xFFFFFFFF, 0xF2, 0xCF);

	gdt_up((unsigned int) &gdt_ptr);
}

void fn_gdt_desc(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char granularity){
	gdt_entry[num].base_low = (base & 0xFFFF);
	gdt_entry[num].base_middle = (base >> 16) & 0xFF;
	gdt_entry[num].base_high = (base >> 24) & 0xFF;
	gdt_entry[num].limit_low = (limit & 0xFFFF);
	gdt_entry[num].granularity = (limit >> 16) & 0x0F;
	gdt_entry[num].granularity |= granularity & 0xF0;
	gdt_entry[num].access = access;

}