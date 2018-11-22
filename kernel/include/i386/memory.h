#ifndef NOS_MEMORY_H
#define NOS_MEMORY_H
#include "../../../include/global.h"
#include "../../../include/types.h"
#include "../kernel.h"
#define MAX_GDT		7
	
#define SYSTEMGATE	 	0xEF
#define MAX_IDT	 		0xFF
#define PAGE_SIZE	 	0x1000

#define VM_START	 	0x00400000

#define S_KERNEL_OFFSET		0x00400000
#define END_KERNEL_OFFSET	0x40000000
#define S_BUFFER			0x40000000
#define END_BUFFER			0x80000000
#define S_U_OFFSET			0x80000000
#define END_U_OFFSET		0xC0000000
#define S_U_STACK	 		0xBFFFFFFF
#define S_ADDR_HEAP	 		END_U_OFFSET
#define END_HEAP		 	0xFFFFF000

#define MEM_ATTR_NO	 		0x0
#define MEM_ATTR_RESIDENT	0x1
#define MEM_ATTR_SHARED	 	0x2

#define X_ONLY	 	0x1
#define W_ONLY		0x2
#define R_ONLY	 	0x4

#ifdef NOS_BITMAP

#define BIT_SIZE	 	0x20

void setbit(unsigned int*,unsigned int);
unsigned int testbit(unsigned int*,unsigned int);
void clearbit(unsigned int*,unsigned int);

#endif

#ifdef NOS_PAGING
#define PAGING_ON() asm("push %eax; mov %cr0, %eax; orl $0x80000000,%eax ; mov %eax, %cr0 ; pop %eax");
#define PAGING_OFF() asm("push %eax; mov %cr0, %eax; andl $0x7FFFFFFF,%eax ; mov %eax, %cr0 ; pop %eax");

int real_alloc_ap(size_t, unsigned int);
int *alloc(size_t);
int *alloc_a(size_t);
int *alloc_p(size_t, void*);
int *alloc_ap(size_t, void*);

area_s_t* get_free_area(as_map_t*, unsigned int);
void fragment_area(as_map_t*, area_s_t*, unsigned int);

int m_malloc_real(as_map_t*, page_s_t*, int, unsigned int);
int kfree_real(page_s_t*, unsigned int, area_s_t*);
int krealloc_real(page_s_t*, area_s_t*, unsigned int, int, unsigned int);
int put_area(area_s_t*, unsigned int);
unsigned int get_free_frame(void);
unsigned int get_free_vm_frame(void);
int free_page(unsigned int);
static void do_idty_page(page_s_t *);
void switch_pd(page_s_t* pd);
void copytablepage(page_s_t* to, const page_s_t* from);
int do_no_page(unsigned int address);
void put_page(page_s_t*, unsigned int, unsigned int, unsigned int);
void do_wr_page(unsigned int address);
void do_usr_page(unsigned int address);
void do_rsvd_page(unsigned int address);
void do_intr_fetch(unsigned int address);
page_s_t* get_page_table(page_s_t*, unsigned int address);
page_s_t* put_page_table(page_s_t*, unsigned int address);
#endif

#ifdef NOS_GLOBAL_DESCRIPTOR_TABLE

struct gdt_desc{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__ ((packed));

struct gdt_reg{
	unsigned short limit;
	unsigned int base;
} __attribute__ ((packed));


typedef struct gdt_desc gdt_desc_t;
typedef struct gdt_reg gdt_reg_t;

void fn_gdt_desc(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char granularity);
extern void gdt_up(unsigned int);

#endif

#ifdef NOS_INTERRUPT_DESCRIPTOR_TABLE
#define INTGATE	  		0x8E		
#define TRAPGATE 		0x8F
#define SYSGATE 		0xEF
struct idt_desc
{
	unsigned short base_low;
	unsigned short select;
	unsigned char type;
	unsigned char flags;
	unsigned short base_high;
} __attribute__ ((packed));

struct idt_reg
{
	unsigned short limit;
	unsigned int base;
} __attribute__ ((packed));

typedef struct idt_desc idt_entry_t;
typedef struct idt_reg idt_ptr_t;

static void fn_desc_idt(int, unsigned int, unsigned short, unsigned char);
static void activate_int(int);
static void deactivate_int(int);
static void reset_int(int);
extern void idt_up(unsigned int);

extern void asm_int_ign(void);
extern void asm_isr_def(void);

extern void asm_isr_0(void);
extern void asm_isr_1(void);
extern void asm_isr_2(void);
extern void asm_isr_3(void);
extern void asm_isr_4(void);
extern void asm_isr_5(void);
extern void asm_isr_6(void);
extern void asm_isr_7(void);
extern void asm_isr_8(void);
extern void asm_isr_9(void);
extern void asm_isr_10(void);
extern void asm_isr_11(void);
extern void asm_isr_12(void);
extern void asm_isr_13(void);
extern void asm_isr_14(void);
extern void asm_isr_15(void);
extern void asm_isr_16(void);
extern void asm_isr_17(void);
extern void asm_isr_18(void);
extern void asm_isr_19(void);
extern void asm_isr_20(void);
extern void asm_isr_21(void);
extern void asm_isr_22(void);
extern void asm_isr_23(void);
extern void asm_isr_24(void);
extern void asm_isr_25(void);
extern void asm_isr_26(void);
extern void asm_isr_27(void);
extern void asm_isr_28(void);
extern void asm_isr_29(void);
extern void asm_isr_30(void);
extern void asm_isr_31(void);

extern void asm_irq_0(void);
extern void asm_irq_1(void);
extern void asm_irq_2(void);
extern void asm_irq_3(void);
extern void asm_irq_4(void);
extern void asm_irq_5(void);
extern void asm_irq_6(void);
extern void asm_irq_7(void);
extern void asm_irq_8(void);
extern void asm_irq_9(void);
extern void asm_irq_10(void);
extern void asm_irq_11(void);
extern void asm_irq_12(void);
extern void asm_irq_13(void);
extern void asm_irq_14(void);
extern void asm_irq_15(void);
extern void asm_irq_16(void);

static void fn_desc_idt(int num, unsigned int base, unsigned short select, unsigned char flags);

#endif

#ifdef NOS_HEAP
heap_s_t* get_free_heap(as_map_t*, unsigned int, unsigned int);
heap_s_t* kmalloc_heap(as_map_t*, unsigned int, unsigned int);
void fragment_heap(as_map_t*, heap_s_t*, unsigned int);
#endif

void activate_All_int();
void init_gdt_sys(void);
void INIT_PIC(void);
void init_idt(void);
void init_paging(void);
void init_mm_map(void);
unsigned int get_remain_size_memory(void);
int malloc(unsigned int);
int free(void*);
void align(void);
int smalloc(as_map_t*, int, int, unsigned int, unsigned int);
int m_malloc_a(as_map_t*, int, unsigned int);
int k_malloc(as_map_t*, int);
int k_malloc_sh(as_map_t* as, int size);
int k_malloc_res(as_map_t* as, int size);
int m_malloc(as_map_t*, int, unsigned int);
int m_malloc_shared(as_map_t*, int, unsigned int);
int m_malloc_res(as_map_t*, int, unsigned int);
int vm_malloc(as_map_t*, unsigned int size,unsigned int);
int sfree(void*, unsigned int);
int kfree(void*);
int kfree_shared(void*);
int kfree_res(void*);
unsigned int krealloc(area_s_t*, int);
void switch_as(as_map_t*);
void init_area(page_s_t*,as_map_t*);
#endif
