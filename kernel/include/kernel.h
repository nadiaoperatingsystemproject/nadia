#ifndef NOS_KERNEL_H
#define NOS_KERNEL_H
#include "../../include/types.h"
#define ltr(a)	asm volatile("ltr %%ax"::"a"(a));
#define isdigit(n) (n<'9' && n>'0')
#define isupper(n) (n<'A' && n>'Z')
#define islower(n) (n<'a' && n>'z')
#define isalpha(n) (isdigit(n)|islower(n)|isupper(n))
#define bcd_to_bin(val) ((val)=((val)&15) + ((val)>>4)*10)
#define getflags()	({		\
						unsigned int flags;	\
						asm volatile("	\n 	\
							cli	\n 	\
							pushfl	\n 	\
							popl %%eax	\n 	\
							mov %%eax, %0	\n 	\
							sti":"=m"(flags):);	\
						flags;	\
					})

#define setflags(n)	({		\
						asm volatile("	\n 	\
							cli	\n 	\
							pushl %%eax	\n 	\
							popfl	\n 	\
							sti"::"a"(n));	\
					})

struct page_s
{
	unsigned int present	:1;
	unsigned int writable	:1;
	unsigned int user		:1;
	unsigned int pwt		:1;
	unsigned int pcd 		:1;
	unsigned int accessed 	:1;
	unsigned int dirty 		:1;
	unsigned int pat_ps		:1;
	unsigned int global 	:1;
	unsigned int flags	 	:3;
	unsigned int address 	:20;
} __attribute__ ((packed));

struct page_fault
{
	unsigned int present	:1;
	unsigned int writable	:1;
	unsigned int user		:1;
	unsigned int rsvd 		:1;
	unsigned int id 		:1;
	unsigned int reserved 	:27;
} __attribute__ ((packed));

typedef struct page_s page_s_t;


struct heap_s_list
{
	struct heap_s *next;
	struct heap_s *prev;
};

struct heap_s
{
	unsigned int start_addr;
	unsigned int size;
	unsigned int proc;
	struct heap_s *next;
	struct heap_s *prev;
};

struct area_s_list
{
	struct area_s *next;
	struct area_s *prev;
	unsigned int count;
};


struct area_s
{
	//virtual area
	unsigned int start_addr;
	unsigned int npages;
	unsigned int attribute;
	unsigned int flags;
	unsigned int count;
	unsigned int size;
	unsigned int remain_size;
	struct area_s *next;
	struct area_s *prev;
};

struct as_map
{
	unsigned int start;
	unsigned int end;
	unsigned int limit;
	unsigned int size;
	struct area_s_list* list_f;
	struct area_s_list* list_u;
	struct heap_s_list* heap_f;
	struct heap_s_list* heap_u;
};

typedef struct as_map as_map_t;
typedef struct area_s area_s_t;
typedef struct area_s_list area_list_t;
typedef struct heap_s heap_s_t;
typedef struct heap_s_list heap_list_t;
#ifdef PROCESS

struct tss_registers
{
	unsigned short prev_task, prev_task_u;
    unsigned int esp0;
    unsigned short ss0, ss0_u;
    unsigned int esp1;
    unsigned short ss1, ss1_u;
    unsigned int esp2;
    unsigned short ss2, ss2_u;
    unsigned int cr3;
    unsigned int eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
    unsigned short es, es_u;
    unsigned short cs, cs_u;
    unsigned short ss, ss_u;
    unsigned short ds, ds_u;
    unsigned short fs, fs_u;
    unsigned short gs, gs_u;
    unsigned short ldt, ldt_u;
    unsigned short dbg_flag, io;
}__attribute__ ((packed));

struct process_struct
{
	pid_t pid;
	pid_t ppid;
	unsigned int top;
	unsigned int state;
	unsigned int utime;
	unsigned int ktime;
	unsigned int *code,*data,*stack;
	struct tss_registers tss;
	page_s_t* dir;
	struct process_struct* parent;
	struct process_struct* chidrens;
	as_map_t* heap;
};

typedef struct process_struct task_t;
unsigned int nb_task = 0;

static task_t *task;
static task_t * queue;
static task_t * current_task;
#endif
#endif