/**
* Nadia OS descriptor file .c
*
* This file describe 
*
* @author : kabong freddy
*/

/**
*														========= IDT REGISTER =========
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

#ifndef NOS_INTERRUPT_DESCRIPTOR_TABLE
#define NOS_INTERRUPT_DESCRIPTOR_TABLE
#include "../include/types.h"
#include "include/i386/memory.h"
#include "../include/io.h"
#include "../include/string.h"
#endif

idt_entry_t idt_entry[MAX_IDT];
idt_ptr_t idt_ptr;

void init_idt(void){
	idt_ptr.limit = MAX_IDT*8-1;
	idt_ptr.base = (unsigned int) &idt_entry;

	memset((unsigned char*) &idt_entry,0,(256*8));

	fn_desc_idt(0,(unsigned int) asm_isr_0,0x08, INTGATE);
	fn_desc_idt(1,(unsigned int) asm_isr_1,0x08, INTGATE);
	fn_desc_idt(2,(unsigned int) asm_isr_2,0x08, INTGATE);
	fn_desc_idt(3,(unsigned int) asm_isr_3,0x08, INTGATE);
	fn_desc_idt(4,(unsigned int) asm_isr_4,0x08, INTGATE);
	fn_desc_idt(5,(unsigned int) asm_isr_5,0x08, INTGATE);
	fn_desc_idt(6,(unsigned int) asm_isr_5,0x08, INTGATE);
	fn_desc_idt(7,(unsigned int) asm_isr_7,0x08, INTGATE);
	fn_desc_idt(8,(unsigned int) asm_isr_8,0x08, INTGATE);
	fn_desc_idt(9,(unsigned int) asm_isr_9,0x08, INTGATE);
	fn_desc_idt(10,(unsigned int) asm_isr_10,0x08, INTGATE);
	fn_desc_idt(11,(unsigned int) asm_isr_11,0x08, INTGATE);
	fn_desc_idt(12,(unsigned int) asm_isr_12,0x08, INTGATE);
	fn_desc_idt(13,(unsigned int) asm_isr_13,0x08, INTGATE);
	fn_desc_idt(14,(unsigned int) asm_isr_14,0x08, INTGATE);
	fn_desc_idt(15,(unsigned int) asm_isr_15,0x08, INTGATE);
	fn_desc_idt(16,(unsigned int) asm_isr_16,0x08, INTGATE);
	fn_desc_idt(17,(unsigned int) asm_isr_17,0x08, INTGATE);
	fn_desc_idt(18,(unsigned int) asm_isr_18,0x08, INTGATE);
	fn_desc_idt(19,(unsigned int) asm_isr_19,0x08, INTGATE);
	fn_desc_idt(20,(unsigned int) asm_isr_20,0x08, INTGATE);
	fn_desc_idt(21,(unsigned int) asm_isr_21,0x08, INTGATE);
	fn_desc_idt(22,(unsigned int) asm_isr_22,0x08, INTGATE);
	fn_desc_idt(23,(unsigned int) asm_isr_23,0x08, INTGATE);
	fn_desc_idt(24,(unsigned int) asm_isr_24,0x08, INTGATE);
	fn_desc_idt(25,(unsigned int) asm_isr_25,0x08, INTGATE);
	fn_desc_idt(26,(unsigned int) asm_isr_26,0x08, INTGATE);
	fn_desc_idt(27,(unsigned int) asm_isr_27,0x08, INTGATE);
	fn_desc_idt(28,(unsigned int) asm_isr_28,0x08, INTGATE);
	fn_desc_idt(29,(unsigned int) asm_isr_29,0x08, INTGATE);
	fn_desc_idt(30,(unsigned int) asm_isr_30,0x08, INTGATE);
	fn_desc_idt(31,(unsigned int) asm_isr_31,0x08, INTGATE);

	fn_desc_idt(32,(unsigned int) asm_irq_0,0x08, INTGATE);
	fn_desc_idt(33,(unsigned int) asm_irq_1,0x08, INTGATE);
	fn_desc_idt(34,(unsigned int) asm_irq_2,0x08, INTGATE);
	fn_desc_idt(35,(unsigned int) asm_irq_3,0x08, INTGATE);
	fn_desc_idt(36,(unsigned int) asm_irq_4,0x08, INTGATE);
	fn_desc_idt(37,(unsigned int) asm_irq_5,0x08, INTGATE);
	fn_desc_idt(38,(unsigned int) asm_irq_6,0x08, INTGATE);
	fn_desc_idt(39,(unsigned int) asm_irq_7,0x08, INTGATE);
	fn_desc_idt(40,(unsigned int) asm_irq_8,0x08, INTGATE);
	fn_desc_idt(41,(unsigned int) asm_irq_9,0x08, INTGATE);
	fn_desc_idt(42,(unsigned int) asm_irq_10,0x08, INTGATE);
	fn_desc_idt(43,(unsigned int) asm_irq_11,0x08, INTGATE);
	fn_desc_idt(44,(unsigned int) asm_irq_12,0x08, INTGATE);
	fn_desc_idt(45,(unsigned int) asm_irq_13,0x08, INTGATE);
	fn_desc_idt(46,(unsigned int) asm_irq_14,0x08, INTGATE);
	fn_desc_idt(47,(unsigned int) asm_irq_15,0x08, INTGATE);
	fn_desc_idt(96,(unsigned int) asm_irq_16,0x08, INTGATE);


	idt_up((unsigned int) &idt_ptr);
}

void activate_All_int(){
	sti;
}

static void fn_desc_idt(int num, unsigned int base, unsigned short select, unsigned char flags){
	
	idt_entry[num].base_low = base & 0xFFFF;
    idt_entry[num].base_high = (base >> 16) & 0xFFFF;

    idt_entry[num].select     = select;
    idt_entry[num].type = 0;
    idt_entry[num].flags   = flags;

}
