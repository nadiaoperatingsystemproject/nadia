#ifndef NOS_INTR
#define NOS_INTR 
#define ISR_INT
#define NOS_PAGING
#endif
#include "include/i386/interrupt.h"
#include "include/i386/memory.h"
#include "../include/io.h"
#include "include/kprint.h"
#include "include/syscall.h"
#include "include/sched.h"
#include "include/panic.h"
#include "../include/string.h"

struct int_vect_table interrupt_table[0xFF] = {{0,},};
extern page_s_t* currentdir;
extern as_map_t* current_as;

void register_int_handler(unsigned int n, isr_t handler){
	interrupt_table[n].id = n;
	interrupt_table[n].handler = handler;
}

extern void isr_handler(registers_t reg){
	if (interrupt_table[reg.num_int].handler != 0)
    {
        isr_t handler = interrupt_table[reg.num_int].handler;
        handler(reg);
    }
}

extern void irq_handler(registers_t reg){
	if (reg.num_int >= 40)
	{
		/* code */
		outb(0xA0, 0x20);
	}
	outb(0x20, 0x20)
	if (interrupt_table[reg.num_int].handler != 0)
	{
		/* code */
		isr_t handler = interrupt_table[reg.num_int].handler;
		handler(reg);
	}
}

/*	ROUTINE DIVIDE BY ZERO 	*/
static void isr_divide_by_zero(registers_t reg){
	kprint("\n ============ [  DIVIDE ERROR (#DE)  ] =========\n");
	asm volatile ("hlt"::);
}			/*	int 0 */
static void isr_debug(registers_t reg){
	kprint("\n ============ [  DEBUG (#DB)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_NMI(registers_t reg){
	kprint("\n ============ [  NMI INTERRUPT  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_INT3(registers_t reg){
	kprint("\n ============ [  BREAKPOINT (#BP)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_overflow_mm(registers_t reg){
	kprint("\n ============ [  OVERFLOW (#OF)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_bounds(registers_t reg){
	kprint("\n ============ [  BOUND RANGE EXCEEDED (#BR)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_invalid_op(registers_t reg){
	kprint("\n ============ [  INVALID OPCODE (#UD)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_device_not_available(registers_t reg){
	kprint("\n ============ [  DEVICE NOT AVAILABLE (#NM)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_double_fault(registers_t reg){
	kprint("\n ============ [  DOUBLE FAULT (#DF)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_coproc_seg_overrun(registers_t reg){
	kprint("\n ============ [  COPROCESSOR SEGMENNT OVERRUN (#MF)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_invalid_tss(registers_t reg){
	kprint("\n ============ [  INVALID TSS (#TS)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_seg_not_present(registers_t reg){
	kprint("\n ============ [  SEGMENT NOT PRESENT (NP)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_stack_segment(registers_t reg){
	kprint("\n ============ [  STACK SEGMENT FAULT (#SS)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_general_protection(registers_t reg){
	kprint("\n ============ [  GENERAL PROTECTION (#GP)  ] =========\n");
	
	asm volatile ("hlt"::);
}
static void isr_page_fault(registers_t reg){
	unsigned int address;
	unsigned int _p = 0;
	page_s_t* page;
	asm volatile("mov %%cr2, %0" : "=r" (address));
	struct page_fault* err_code = (struct page_fault*) &reg.err_code;
	PAGING_OFF();
	if (!(err_code->present & 0x1)){
		//we test validity address

		if(!do_no_page(address)){
			if(!(page = get_page_table(currentdir,address))){
				page = put_page_table(currentdir, address);
			}
			_p = page->address<<12;
			if(current_as && (address>=(unsigned int) current_as->start && address<current_as->end)){
				put_page(currentdir,address,get_free_frame(),0x7);
			}
			else{
				kprint("\n Segmentation fault!");
				panic("\n [ PANIC ] System are crashed!");
			}
		}
		else{
			kprint("\n Page %x not valid process will go stop!", address);
			// invalid address kill process
			panic("\n [ PANIC ] System are crashed!");
		}
	}
	if (err_code->writable & 0x2)
		do_wr_page(address);
	if (err_code->user & 0x4)
		do_usr_page(address);
	if (err_code->reserved & 0x8)
		do_rsvd_page(address);
	if (err_code->id & 0x10)
		do_intr_fetch(address);
	PAGING_ON();
}
static void isr_coprocessor_error(registers_t reg){
	kprint("\n ============ [  FLOATING POINT ERROR (#MF)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_alignment_check(registers_t reg){
	kprint("\n ============ [  ALIGNMENT CHECK (#AC)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_machine_check(registers_t reg){
	kprint("\n ============ [  MACHINE CHECK (#MC)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_SIMD_floating_point_exception(registers_t reg){
	kprint("\n ============ [  SIMD FLOATING POINT EXCEPTION (#XM)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_virtualization_exception(registers_t reg){
	kprint("\n ============ [  VIRTUALIZATION EXCEPTION (#VE)  ] =========\n");
	asm volatile ("hlt"::);
}
static void isr_reserved(registers_t reg){
	kprint("\n ============ [  RESERVED  ] =========\n");
	asm volatile ("hlt"::);
}


void* divise_by_zero(void){
	register_int_handler(ISR0, &isr_divide_by_zero);
}			/*	int 0 */
void* debug(void){
	register_int_handler(ISR1, &isr_debug);
}
void* NMI(void){
	register_int_handler(ISR2, &isr_NMI);
}
void* INT3(void){
	register_int_handler(ISR3, &isr_INT3);
}
void* overflow_mm(void){
	register_int_handler(ISR4, &isr_overflow_mm);
}
void* bounds(void){
	register_int_handler(ISR5, &isr_bounds);
}
void* invalid_op(void){
	register_int_handler(ISR6, &isr_invalid_op);
}
void* device_not_available(void){
	register_int_handler(ISR7, &isr_device_not_available);
}
void* double_fault(void){
	register_int_handler(ISR8, &isr_double_fault);
}
void* coproc_seg_overrun(void){
	register_int_handler(ISR9, &isr_coproc_seg_overrun);
}
void* invalid_tss(void){
	register_int_handler(ISR10, &isr_invalid_tss);
}
void* seg_not_present(void){
	register_int_handler(ISR11, &isr_seg_not_present);
}
void* stack_segment(void){
	register_int_handler(ISR12, &isr_stack_segment);
}
void* general_protection(void){
	register_int_handler(ISR13, &isr_general_protection);
}
void* page_fault(void){
	register_int_handler(ISR14, &isr_page_fault);
}
void* coprocessor_error(void){
	register_int_handler(ISR16, &isr_coprocessor_error);
}
void* alignment_check(void){
	register_int_handler(ISR17, &isr_alignment_check);
}
void* machine_check(void){
	register_int_handler(ISR18, &isr_machine_check);
}
void* SIMD_floating_point_exception(void){
	register_int_handler(ISR19, &isr_SIMD_floating_point_exception);
}
void* virtualization_exception(void){
	register_int_handler(ISR20, &isr_virtualization_exception);
}
void* reserved(void){
	register_int_handler(ISR15, &isr_reserved);
	for (int i = 17; i < 32; ++i)
	{
		/* code */
		register_int_handler(i, &isr_reserved);
	}
}


void isr_init(void){
	divise_by_zero();			/*	int 0 */
	debug();
	NMI();
	INT3();
	overflow_mm();
	bounds();
	invalid_op();
	device_not_available();
	double_fault();
	coproc_seg_overrun();
	invalid_tss();
	seg_not_present();
	stack_segment();
	general_protection();
	page_fault();
	coprocessor_error();
	alignment_check();
	machine_check();
	SIMD_floating_point_exception();
	virtualization_exception();
	reserved();
	sys_call_irq();
}