
#include "../include/stdio.h"
#include "../include/assert.h"
#include "../include/string.h"
#include "../library/math.h"
#include "../kernel/include/kprint.h"
#include "../version.h"
#include "../logo.h"

extern void clear(void);

#define N_CHR	1024
#define MAX_CMD	1024
#define MAX_CHR	128

extern unsigned char getposX(void);
extern unsigned char getposY(void);
extern unsigned char gotoXY(unsigned int x, unsigned int y);
extern void cursor_enable(unsigned char s, unsigned char e);
extern void cursor_disable(void);
extern int login_usr(void*, void*);

extern const char* user;
extern const char* password;

unsigned char cmd[N_CHR] = {0,};
unsigned char copy[MAX_CHR] = "\n CopyRight(c) 2017-2018\n";
unsigned char log_in[] = "\n Login : ";
unsigned char passwrd[] = "\n Password : ";
unsigned char prompt[] = "\n root@prompt:[Root]# ";
unsigned char usr[MAX_CHR] = "";
unsigned char pwrd[MAX_CHR] = "";

void setlogin(unsigned char*, unsigned char*);
void shell(unsigned char* cmd);
void write_console(unsigned const char c);
void init_prompt(void){
	unsigned char c = 0;
	unsigned int i = 0;
	unsigned char x = 0, y = 0, z = 0, bs=0;
	cursor_enable(1,0xe);
	clear();
	kprint(" ========= [ NADIA OPERATING SYSTEM ] ========================================\n");
	kprint(version);
	kprint(copy);
	kprint(logo);
	kprint("\n Connect you as login : %s | password : %s", user, password);
	
	kprint("\n");
	// login
	login:
	kprint(log_in);
	empty_buf(usr);
	x=getposX();
	i=0;
	do{
		c = getchar();
		if(c==8){
			
			bs = 1;
			if(x < strlen(log_in)){
				x = strlen(log_in)-1;
				bs = 2;
			}
			if(i>0){
				x--;
				usr[--i] = 0;
			}
		}
		if(c != 10){
			if(bs!=2 && i<MAX_CHR){
				if(bs!=1){
					usr[i++] = c;
					x++;
				}
				kprint("%c", c);
			}
			bs = 0;
		}
	}while(c != 10);
	
	kprint(passwrd);
	empty_buf(pwrd);
	x=getposX();
	i=0;
	do{
		c = getchar();
		if(c==8){
			bs = 1;
			if(x< strlen(passwrd)){
				x = strlen(passwrd)-1;
				bs = 2;
			}
			if(i>0){
				--x;
				pwrd[--i] = 0;
			}
		}
		if(c != 10){
			if(bs!=2 && i<MAX_CHR){
				if(bs!=1){
					pwrd[i++] = c;
					x++;
				}
				kprint("%c", c!=0x8?'*':c);
			}
			bs = 0;
		}
	}while(c != 10);
	if(!login_usr(usr, pwrd))
		goto login;
	kprint("\n\n Welcome to NADIA 18.10 " \
			"\n New release xx.xx LTS" \
			"\n Type HELP command to show all commands system " \
			"\n NADIA COME WIHT ABSOLUTE NO WARRANTY!\n");
	command:
	i=0;
	kprint(prompt);
	empty_buf(cmd);
	x=getposX();
	do{
		c = getchar();
		if(c==8){
			bs = 1;
			if(x< strlen(prompt)){
				x = strlen(prompt)-1;
				bs = 2;
			}
			if(i>0){
				--x;
				cmd[--i] = 0;
			}
		}
		if(c != 10){
			if(bs!=2 && i<MAX_CHR){
				if(bs!=1){
					cmd[i++] = c;
						x++;
				}
				kprint("%c", c);
			}
			bs = 0;
		}
	}while(c != 10);
	shell(cmd);
	goto command;
}


void setlogin(unsigned char* u, unsigned char* p){

}

void shell(unsigned char* cmd){
	unsigned int n=0;
	unsigned char *command[MAX_CMD] ={"help","echo", "history", "date", "ls","pwd", "exit", "lsdisk", 0,};
	unsigned char *description[MAX_CMD] ={"List command system","Print string on screen","List command used",
	 "Show current time at YYYY-MM-DD format","List files or directories on current directory","Show path of current directory",
	  "Log out on system", "list all disk present", 0,};

	do{
		if(strcmp(cmd,command[n])){
			break;
		}
	}while(n++!=MAX_CMD);

	switch(n){
		case 0:
		kprint("\n");
		kprint("\n ================ ");
		kprint("\n | HELP command |");
		kprint("\n ================ ");
		kprint("\n");
		unsigned int i=0;
		while(command[i]){
			kprint("\n %s 		%s", command[i], description[i]);
			i++;
		}
		break;
		case 1:
		kprint("\n Print string ");
		break;
		case 2:
		kprint("\n File system is not implemented");
		break;
		case 3:
		kprint("\n File system is not implemented");
		break;
		case 4:
		kprint("\n Log out system");
		break;
		default:
		kprint("\n [ Bad command ] %s is unknow command", cmd);
		break;
	}
}



