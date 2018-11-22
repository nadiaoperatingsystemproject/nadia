#include "../include/string.h"
#include "include/input.h"
#include "include/v_print.h"

int v_print(const char* s,list_arg arg, char* buf){

	char* str, *tmp;
	void* ptr;
	char c;
	int count = 0, i,b;
	goto make;
	do_conv_dec:
		tmp = itoa(get_arg(arg, int));
		goto do_next;
	do_conv_x:
		tmp = itoax((unsigned int) get_arg(arg, int), b);
		goto do_next;
	do_conv_hex:
		tmp = itoaHex((unsigned int) get_arg(arg, int));
		goto do_next;
	do_conv_ptr:
		ptr = get_arg(arg, void*);
		tmp = itoaHex((unsigned int) ptr);
		goto do_next;
	do_conv_str:
		tmp = get_arg(arg, char*);
	do_next:
		i = strcopy(buf, tmp);
		buf+=i;
		s++;
	make:
	if(*s){
		switch(*s){
			case '%':
				switch(*++s){
					case 'i':
						goto do_conv_dec;
						break;
					case 'd':
						goto do_conv_dec;
						break;
					case 'u':
						b = 10;
						goto do_conv_x;
						break;
					case 'o':
						b = 8;
						goto do_conv_x;
						break;
					case 'x':
						b = 16;
						goto do_conv_x;
						break;
					case 'X':
						goto do_conv_hex;
						break;
					case 'b':
						b=2;
						goto do_conv_x;
						break;
					case 'p':
						goto do_conv_ptr;
						break;
					case 'n':
						break;
					case 'c':
						c = (unsigned char) get_arg(arg, int);
						*buf++=c;
						s++;
						goto make;
						break;
					case 's':
						goto do_conv_str;
						break;
					case '%':
						*buf++='%';
						s++;
						goto make;
						break;
					default:
						__n_string("\nError syntaxe : Argument expected after % symbole\n");
						return 0;
						break;
				}
				break;
			default:
				*buf++ = *s++;
				++count;
				goto make;
				break;
		}
	}

	
	return count;
}