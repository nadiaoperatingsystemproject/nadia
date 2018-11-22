#ifndef NOS_ASSERET_H
#define NOS_ASSERET_H
#include "../kernel/include/kernel.h"
extern int _assert(unsigned int);
extern void _wassert(const char*, const char*, const char*);
#ifdef NO_DEBUG
#define assert(c) (_assert(c))
#else
#define assert(c) (void)(c || (_wassert(#c, __FILE__, __LINE__),0))
#endif
#define abort()	asm volatile("cli;hlt"::)
#endif