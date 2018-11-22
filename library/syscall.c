

#define SYSTEM_CALL

#include "../kernel/include/i386/interrupt.h"
#include "../kernel/include/i386/memory.h"
#include "../kernel/include/kernel.h"
#include "../kernel/include/syscall.h"
#include "../include/io.h"


void *do_print(const char c){
	do_sys_call(1);
}

void *do_exit(void){
	
}