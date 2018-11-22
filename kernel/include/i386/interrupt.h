
#ifndef NOS_INTERRUPT_H
#define NOS_INTERRUPT_H

#ifdef I8259A
#define	I8259A_PORTA0	0x20
#define	I8259A_PORTB0	0x21
#define	I8259A_PORTA1	0xA0
#define	I8259A_PORTB1	0xA1
#endif

typedef struct registers
{
	unsigned int ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int num_int, err_code;
	unsigned int eip, cs, eflags, usr_esp, ss;
} registers_t;

typedef void (*isr_t)(registers_t);

struct int_vect_table
{
	int id;
	int flags;
	isr_t handler;
	int level;
	int maskable;
};

void register_int_handler(unsigned int, isr_t );

#ifdef ISR_INT

#define ISR0 	0
#define ISR1 	1
#define ISR2 	2
#define ISR3 	3
#define ISR4 	4
#define ISR5 	5
#define ISR6 	6
#define ISR7 	7
#define ISR8 	8
#define ISR9 	9
#define ISR10 	10
#define ISR11 	11
#define ISR12 	12
#define ISR13 	13
#define ISR14 	14
#define ISR15 	15
#define ISR16 	16
#define ISR17 	17
#define ISR18 	18
#define ISR19 	19
#define ISR20 	20

void* divise_by_zero(void);			/*	int 0 */
void* debug(void);
void* NMI(void);
void* INT3(void);
void* overflow_mm(void);
void* bounds(void);
void* invalid_op(void);
void* device_not_available(void);
void* double_fault(void);
void* coproc_seg_overrun(void);
void* invalid_tss(void);
void* seg_not_present(void);
void* stack_segment(void);
void* general_protection(void);
void* page_fault(void);
void* coprocessor_error(void);
void* alignment_check(void);
void* machine_check(void);
void* SIMD_floating_point_exception(void);
void* virtualization_exception(void);
void* reserved(void);

#endif

#ifdef IRQ_INT

#define IRQ0 	32
#define IRQ1 	33
#define IRQ2 	34
#define IRQ3 	35
#define IRQ4 	36
#define IRQ5 	37
#define IRQ6 	38
#define IRQ7 	39
#define IRQ8 	40
#define IRQ9 	41
#define IRQ10 	42
#define IRQ11 	43
#define IRQ12 	44
#define IRQ13 	45
#define IRQ14 	46
#define IRQ15 	47

#endif

#ifdef NOS_CLOCK
int CPL(registers_t reg);
#endif

void map_i386_irq(void);
void isr_init(void);

#endif