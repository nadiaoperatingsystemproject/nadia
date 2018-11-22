
#include "include/kprint.h"
#include "include/v_print.h"
#include "include/input.h"

static char buffer[1024] = {0,};
void empty_buf(char *s){
	while(*s)
		*s++ = 0;
}

int kprint(const char* s, ...){
	list_arg arg;
	int i;
	start_arg(arg, s);
	empty_buf(buffer);
	i = v_print(s, arg, buffer);
	end_arg(arg);
	/*Empty buffer*/
	__n_string(buffer);
	return i;
}