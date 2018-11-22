#ifndef NOS_SYS_CALL_H
#define NOS_SYS_CALL_H

#define IRQ_SYS 	96
#ifdef SYSTEM_CALL
void do_timer(int );
void do_exit(void );
void write(void );
#endif
void do_sys_call(unsigned int, unsigned int);
void *sys_call_irq(void);
#endif