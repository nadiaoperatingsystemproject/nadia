#ifndef NOS_STRING_H
#define NOS_STRING_H 
#include "global.h"
#include "types.h"

void memset(unsigned char* p,int value,size_t size);

void *memmove(void *d, const void *s, size_t size);

unsigned int memcmp(const void *d, const void *s, size_t size);

void *memcpy(void *d, const void *s, size_t size);

unsigned int strlen(const char* );

unsigned int strcmp(const char* , const char* );

unsigned int strcopy(char* , const char* );

char* itoa(int );

char* itoax(unsigned int ,unsigned int);

char* itoaHex(unsigned int);

int atoi(const char* );

int atoix(const char* , int );

#endif
