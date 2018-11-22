
#include "include/kprint.h"
#include "../include/io.h"

void panic(const unsigned char* str){
    kprint(str);
    cli;
	asm volatile ("hlt"::);
}