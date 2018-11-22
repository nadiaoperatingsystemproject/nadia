/**
*
*			DESCRIPTION OF PORT : 70
*			========================
*
*			+---+---+---+---+---+---+---+---+
*			| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | <-- bit register
*			---------------------------------
*			| I | X |   	 ADDRESS 		|	I = NMI enable(1) / diseable(0) | X for CMOS Extend 
*			+---+---------------------------+
*			
*			ADDRESS			DESCRIPTION OF REGISTER 		COUNTER
*			=======			=======================   		=======
*
*			00h				SECOND							0-59 --> 0-1 MINUTE
*			01h				ALARM'S SECOND					0-59
*			02h				MINUTE							0-59 --> 0-1 HOUR
*			03h				ALARM'S MINUTE					0-59
*			04h				HOUR							0-23 --> 0-1 DAY
*			05h				ALARM'S HOUR					0-23
*			06h				WEEK'S DAY						1-7 (MONDAY - SUNDAY)
*			07h				MONTH'S DAY						1-31
*			08h				MONTH							0-11
*			09h				YEAH
*			0Ah				STATE REGISTER A
*			0Bh				STATE REGISTER B 				MODE HOUR | BIT 7 = 0 (0-12hour) / 1 (13-24hour) | PLAGE HOUR 0-23
*			0Ch				STATE REGISTER C
*			0Dh				STATE REGISTER D
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
/*
*/


#ifndef CMOS_DRIVER_H
#define CMOS_DRIVER_H
#include "../../../include/io.h"

#define RTC_REG_PORT  		0x70
#define RTC_RW_PORT  		0x71

#define CMOS_READ(a)		({		\
								outbp(a|0x80,RTC_REG_PORT);		\
								inbp(RTC_RW_PORT);			\
							})

void CMOS_WRITE(unsigned char addr, unsigned char val){
	outbp(addr,CMOS_REGISTER_PORT);
	outbp(val,CMOS_RW_PORT);
}

void CMOS_END(){
	outbp(0X80,CMOS_REGISTER_PORT);
}

#endif

