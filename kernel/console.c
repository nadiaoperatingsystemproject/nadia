/**
* Nadia OS descriptor file .c
*
* This file describe 
*
* @author : kabong freddy
*/

#ifndef NOS_VIDEO
#define NOS_VIDEO
#endif
#include "../include/global.h"
#include "../include/io.h"
#define VIDEO_TEXT_MODE		0x0
#define VIDEO_GRAPHIC_MODE	0x1
#define MAX_ADD_V			0xFA0
#define ADD_V				0xb8000
#define LINE				80
#define COL					25
#define COLOR_DEFAULT		0x07

static char cx = 0, cy = 0;
char color = COLOR_DEFAULT;
unsigned char* video;


char set_color(char clr){
	return color = (color&0xf0)|(clr&0x0f);
}

char set_bgcolor(char bg){
	return color = (color&0x0f)|(bg&0xf0);
}


void cursor_enable(unsigned char s, unsigned char e){

	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | s);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3E0) & 0xE0) | e);
}

void cursor_disable(void){
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void set_cursor(unsigned int x, unsigned int y){
	unsigned short pos_cur;
	pos_cur = y * 80 + x;
	cli;
	outb(0x3d4, 0x0f);
	outb(0x3d5, (unsigned char) pos_cur);
	outb(0x3d4, 0x0e);
	outb(0x3d5, (unsigned char) (pos_cur >> 8));
	sti;
}

unsigned char getposX(void){
	return cx;
}

unsigned char getposY(void){
	return cy;
}

unsigned char gotoXY(unsigned char x, unsigned int y){
	set_cursor(x, y);
}

void __n_putchr(unsigned const char c){
	unsigned char* v;
	v = (unsigned char*)((cy*LINE+cx)*2+ADD_V);
	*v = c;
	*(v+1) = color;
}

void scroll(void){ 
	unsigned char i = 0, j=0;
	if (cy>24)
	{
		/* do scroll up */
		for ( i = 0; i < COL; i++)
		{
			/* code */
			unsigned char* tmp = (unsigned char*) (LINE*(i+1)*2 + ADD_V);
			video = (unsigned char*) (LINE*i*2 + ADD_V);
			for (j = 0; j < LINE*2; j+=2)
			{
				/* code */
				*(video+j) = *(tmp+j);
			}
		}
		--cy;
		for (int i = 0; i < LINE*2; i+=2)
		{
			/* code */
			video = (unsigned char*) (cy*LINE*2 + i + ADD_V);
			*video = 0x20;
		}
		cx=0;
	}
}


void write_console(unsigned const char c){
	
	if (c==0xa || cx==80)
	{
		/* do next line */
		++cy;
		cx = 0;
		set_cursor(cx, cy);
		if(c!=0xa){
			__n_putchr(c);
			++cx;
		}
		scroll();
		return;
	}
	switch(c){
		case 0x8:
		if(!(cx!=0)){
			--cy;
			cx = 80;
		}
		--cx;
		__n_putchr(0);
		break;
		case 0x9:
		cx = cx + 8 - (cx % 8);
		break;
		default:
		__n_putchr(c);
		++cx;
		break;
	}
	set_cursor(cx, cy);
}

void * __n_string(const char* s){
	while(*s){
		write_console(*s++);
	}
	return (void*) 0;
}

void clear(void){
	for (int i = 0; i < (int) MAX_ADD_V/2; ++i)
	{
		/* code */
		write_console(0x20);
	}
	cx=0;
	cy=0;
}
