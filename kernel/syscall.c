#include "include/i386/interrupt.h"
#include "include/i386/memory.h"
#include "include/kernel.h"
#include "include/syscall.h"
#include "../include/io.h"
#include "include/kprint.h"

static void fn_sys_call(registers_t reg){
	kprint("\n ============ [  SYSTEM CALL  ] =========\n");
	kprint(" This is aystem call number %i and value %i ", reg.eax, reg.ebx);
	switch(reg.eax){
		case 1:

		break;
		case 2://

		break;
	}
}

void do_sys_call(unsigned int num,unsigned int val){
	
	asm volatile ("int $0x60"::"a"(num), "b"(val));
}

void *sys_call_irq(void){
	register_int_handler(IRQ_SYS, &fn_sys_call);
}

