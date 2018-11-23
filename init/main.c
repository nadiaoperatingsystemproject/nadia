/**
* Nadia OS descriptor file .c
*
* This file describe 
*
* @author : kabong freddy
*/

#ifndef NOS_MAIN_H
#define NOS_MAIN_H
#define NOS_PAGING

#include "../include/global.h"
#include "../include/assert.h"
#include "../include/fs/fs.h"
#include "../kernel/include/keyboard.h"
#include "../kernel/include/i386/memory.h"
#include "../kernel/include/i386/interrupt.h"
#include "../kernel/include/sched.h"
#include "../kernel/include/kprint.h"
#include "../kernel/include/syscall.h"
#include "../library/list.h"
#endif

extern void clear(void);
extern void init_vga_controller(int);
extern void init_prompt(void);
extern void init_timer(void);
extern void initrdisk(void);

extern area_list_t* free_area;
extern area_list_t* area_used;
extern dev_t* current_dev_disk;

struct mem_struct mem = {0,};
//extern dev_t* initrdisk(void);

// int print(const char* str, ...){
	
// }

int kmain(struct multiboot* _m){
	mem.higher = _m->high_mem << 10; // obtain memory size in byte
	clear();
	kprint("\n == [ NADIA OPERATING SYSTEM ] ===========================================\n\n");
	isr_init();
	init_timer();
	kprint("\n [+] INTERRUPT INITIALIZED AND LOADED ----------------------[ok]");
	init_gdt_sys();
	kprint("\n [+] GDT REGISTER INITIALIZED AND LOADED ----------------------[ok]");
	map_i386_irq();
	kprint("\n [+] PIC INITIALIZED AND LOADED ----------------------[ok]");
	init_idt();
	sti;
	kprint("\n [+] IDT REGISTER INITIALIZED AND LOADED ----------------------[ok]");
	init_keyboard_driver();
	init_mm_map();//paging enable
	//init ramdisk
	kprint("\n total size %i", mem.higher>>20);
	//current_dev_disk = initrdisk();
	abort();
	//install fs
	
	// mount fs
	init_sheduler();
	init_vga_controller(1);
	init_fs();
	init_prompt();
	while(1);
	return 0;
}