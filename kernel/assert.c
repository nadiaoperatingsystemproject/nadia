#ifndef ASSERT
#define ASSERT
#include "../include/assert.h"
#include "include/kprint.h"
#endif

int _assert(unsigned int c){

}

void _wassert(const char* msg, const char* file, const char* line){
	kprint("\n Assertion: %s , in file %s at line %i", msg, file, line);
	abort();
}