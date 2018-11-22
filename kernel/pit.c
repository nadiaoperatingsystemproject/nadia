/**
* Nadia OS descriptor file .c
*
* This file describe 
*
* @author : kabong freddy
*/

/**
*			PIT 8254
*			=========
*/
#ifndef NOS_CLOCK
/**
* Nadia OS descriptor file .c
*
* This file describe 
*
* @author : kabong freddy
*/

#define NOS_CLOCK
#define IRQ_INT
#endif
#include "include/i386/interrupt.h"
#include "include/i386/clock.h"
#include "include/kprint.h"
#include "../include/string.h"
#include "../include/io.h"
#define PIT_FREQ 			100
#define PIT_COUNTER_0_PORT 	0x40
#define PIT_COUNTER_1_PORT 	0x41
#define PIT_COUNTER_2_PORT 	0x42
#define PIT_CTRL_REG_PORT 	0x43



static void timer_callback(registers_t reg){
	static unsigned int tic = 0;
	unsigned char* str;
	if(tic%100 == 0){
		
	}
	++tic;
}

static void pit_config(unsigned int freq){
	unsigned int divid = 1193180/freq;

	outb(PIT_CTRL_REG_PORT, 0x36);/* channel 0 -> 00 11 x11 0*/
	outb(PIT_CTRL_REG_PORT, 0x54);/* channel 1 -> 01 01 x10 0*/
	outb(PIT_CTRL_REG_PORT, 0xB6);/* channel 2 -> 10 11 x11 0*/

	outb(PIT_COUNTER_0_PORT, 0x00);
	outb(PIT_COUNTER_0_PORT, 0x00);

	outb(PIT_COUNTER_1_PORT, 0x12);

	outb(PIT_COUNTER_0_PORT, 0xd1);
	outb(PIT_COUNTER_0_PORT, 0x11);

	unsigned char l = (unsigned char)(divid & 0xFF);
	unsigned char h = (unsigned char)((divid>>8) & 0xFF); 

	outbp(PIT_CTRL_REG_PORT, 0x36);/* channel 0 -> 00 11 x11 0*/
	outbp(PIT_COUNTER_0_PORT, l);
	outb(PIT_COUNTER_0_PORT, h);
	kprint("\nTimer is initialized --- [ ok ] \n");
}

void init_timer(void){
	register_int_handler(IRQ0,&timer_callback);
	pit_config(PIT_FREQ);
	kprint("\nTimer is initialized --- [ ok ] \n");
}