#ifndef NOS_LOGIN
#define NOS_LOGIN
#include "../include/string.h"
#include "../kernel/include/kprint.h"
const char* user = "admin";
const char* password = "root";
#endif

int login_usr(void* u, void* p){
	if(strcmp(u, user))
		if (strcmp(p, password))
			return 1;
		else
			kprint("\n Bad login ... login or password is incorrect");
	else
		kprint("\n Bad login ... login or password is incorrect");
	return 0;
}