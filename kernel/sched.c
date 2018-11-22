/**
* Nadia OS descriptor file .c
*
* This file describe 
*
* @author : kabong freddy
*/

#define	PROCESS
#define NOS_PAGING
#define NOS_GLOBAL_DESCRIPTOR_TABLE
#include "include/i386/interrupt.h"
#include "include/i386/memory.h"
#include "include/sched.h"
#include "../include/io.h"
#include "../include/string.h"
#include "include/kprint.h"

#define T_READY		1
#define T_RUNNING	2
#define T_WAIT		0
#define T_LOCK		3
#define T_END		4

struct tss_registers tss = {0,};
extern struct mem_struct mem;
extern page_s_t* page_dir;
extern as_map_t* user_as;
void do_witch_to(unsigned int t){
	unsigned int eflags = (getflags()|0x200)&0xFFFFBFFF;
	/*asm volatile("\
				  push ss \n \
				  push esp \n \
				  push eflags \n \
				  push cs \n \
				  push eip \n \
				  iret"::"m"(eflags));*/
}

static page_s_t* init_task(task_t* t){
	t->pid = nb_task++;
	t->ppid = 0;
	t->top = 10;
	t->state = T_WAIT;
	t->utime = 0;
	t->ktime = 0;
}


static void load_task(task_t* t){

}

void do_nothing(void){
	while(1);
}

void init_sheduler(void){

	/* Init TSS by default this TSS register is used to save context of a task */

	unsigned int base = (unsigned int) &tss;
	unsigned int limit = sizeof(struct tss_registers);
	cli;
	fn_gdt_desc(5,base,limit, 0xE9, 0x00);
	sti;
	ltr(0x28);
	tss.ss0 = 0x10;
	tss.esp0 = 0x00;
	tss.cs = 0x0b;
	tss.ss = tss.ds = tss.ds = tss.es = tss.fs = tss.gs = 0x13;
	
	task = (task_t*) k_malloc(user_as, sizeof(int)*32);
	/* initializing first task init*/
	task_t init;
	init_task(&init);

}

void shedule(void){
	if(nb_task == 0)
		return;
		
}



