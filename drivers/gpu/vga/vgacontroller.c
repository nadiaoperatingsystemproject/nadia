#ifndef NOS_VGA
#define NOS_VGA
#include "../../../include/global.h"
#include "../../../include/io.h"
#include "../../../kernel/include/kprint.h"

#define IN_STATUS0					0x3C2
#define MIS_PORT					0x3C2
#define SEQUENCER_INDEX_PORT		0x3C4
#define SEQUENCER_DATA_PORT			0x3C5
#define GRAPHICC_INDEX_PORT			0x3CE
#define GRAPHICC_DATA_PORT			0x3CF
#define ATTRIBUTEC_INDEX_PORT		0x3C0
#define ATTRIBUTEC_READ_PORT		0x3C1
#define ATTRIBUTEC_WRITE_PORT		0x3C0
#define ATTRIBUTEC_RESET_PORT		0x3DA

unsigned char inputstatus0(void);

unsigned char inputstatus1(void);

void misc_reg_out(unsigned char data){
	outb(MIS_PORT, data);
}

void sendcommandregister(unsigned short port, unsigned char reg);

void init_vga_controller(int mode){
	kprint("\n set mode Emulation %i", mode);
	if(mode!=0 && mode!=1)
		return;
	if(mode){
		#define MODE_VGA 1
	}
	else{
		#define MODE_VGA 0
	}

	#ifdef MODE_VGA
	kprint("\n CGA Emulation mode");
	#define IN_STATUS1					0x3DA
	#define CRTC_INDEX_PORT				0x3D4
	#define CRTC_DATA_PORT				0x3D5
	#else
	kprint("\n MDA Emulation mode");
	#define IN_STATUS1					0x3BA
	#define CRTC_INDEX_PORT				0x3B4
	#define CRTC_DATA_PORT				0x3B5
	#endif

	// VGA Miscellaneous Output Register
	/*
		bit 0 : I/O address select bit [0:0x3Bx (MDA Emulation mode) | 1:0x3Dx (CGA Emulation mode)]
		bit 1 : RAM enable / disable [0:VRAM disable | 1:VRAM enable] 
		bit 2-3 : clock select bits
			[
				00: 25.175 MHz clock on VGA | 14 MHz clock on EGA
				01: 28.322 MHz clock on VGA | 16 MHz clock on EGA
				10: external clock selected
				11: Reserved
			]
		bit 4 : 0
		bit 5 : page bit for odd/even mode [0: low | 1: high (diagnostic use)]
		bit 6 : horizontal sync polarity
		bit 7 : vertical sync polarity


	*/

	misc_reg_out(0x62|mode);
	kprint("\n VGA Miscellaneous Output Register defined ");
	unsigned char i0, i1;
	i0 = inputstatus0();
	kprint("\n input status register 0 : %b", i0);
	i1 = inputstatus1();
	kprint("\n input status register 1 : %b", i1);

	// VGA CRT Controller Register
	// x = D (for CGA) | B (for MDA)
	/*
		port 	 offset 			description

		0x 3x4 					address register
		0x 3x5 		0
					1
					2
					3
					4
					5
					6
					7
					8*
					9
					10*
					11*
					12*
					13*
					14*
					15*
					16
					17
					18
					19
					20
					21
					22
					23
					24
	*/

	// VGA Sequencer Registers
	/*
		port 	 offset 			description

		0x 3C4 				address register
		0x 3C5 		0
					1
					2*
					3*
					4*
	*/			
}

void sendcommandregister(unsigned short port, unsigned char reg){

}

unsigned char inputstatus0(void){
	unsigned char b;
	b = inb(IN_STATUS0);
	return b;
}


unsigned char inputstatus1(void){
	unsigned char b;
	b = inb(IN_STATUS1);
	return b;
}
















unsigned char vga_config_res[] = {
	/* MISC */
		0x63,
	/* SEQ */
		0x03, 0x01, 0x0F, 0x00, 0x06,
	/* CRTC */
		0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
		0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x9C, 0x0E, 0x8F, 0x28, 0x00, 0x96, 0xB9, 0xE3,
		0xFF,
	/* GC */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
		0xFF,
	/* AC */
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x41, 0x00, 0x0F, 0x00, 0x00

};

unsigned int supportmode(unsigned int, unsigned int, unsigned int);
unsigned int setmode(unsigned int, unsigned int, unsigned int);
void putpixel(unsigned int, unsigned int, unsigned char, unsigned char, unsigned char);
unsigned char getcolor(unsigned char, unsigned char, unsigned char);
void setpixel(unsigned int, unsigned int, unsigned char);
void writeregs(unsigned char*);
unsigned char* getframebuffersegment(void);

#endif


// void drawobject(struct graph* gr, int width, int heigth, int x, int y, const char* color){

// }



unsigned int supportmode(unsigned int width, unsigned int heigth, unsigned int colordeph){
	switch(width){
		case 320:
		switch(heigth){
			case 200:
			switch(colordeph){
				case 8:
				return (unsigned int) &vga_config_res;
				break;
				default:
				return 0;
				break;
			}
			break;
			default:
			return 0;
			break;
		}
		break;
		case 640:
		break;
		default:
		return 0;
		break;
	}
}

unsigned int setmode(unsigned int width, unsigned int heigth, unsigned int color){
	unsigned char* resol = NULL;
	if(!(resol = (unsigned char*) supportmode(width, heigth, color)))
		return 0;
	writeregs(resol);
	return 1;

}

void writeregs(unsigned char* reg){

	/* MISC */
	outb(MIS_PORT,*(reg++));

	/* SEQUENCER */
	for (unsigned char i = 0; i < 5; ++i)
	{
		/* code */
		outb(SEQUENCER_INDEX_PORT, i);
		outb(SEQUENCER_DATA_PORT, *(reg++));
	}

	/* CRT CONTROLLER */
	outb(CRTC_INDEX_PORT, 0x03);
	outb(CRTC_DATA_PORT, inb(CRTC_DATA_PORT) | 0x80);
	outb(CRTC_INDEX_PORT, 0x11);
	outb(CRTC_DATA_PORT, inb(CRTC_DATA_PORT) & ~0x80);

	reg[0x03] = reg[0x03] | 0x80;
	reg[0x11] = reg[0x11] & ~0x80;
	for (unsigned char i = 0; i < 25; ++i)
	{
		/* code */
		outb(CRTC_INDEX_PORT, i);
		outb(CRTC_DATA_PORT, *(reg++));
	}
	/* SEQUENCER */
	for (unsigned char i = 0; i < 9; ++i)
	{
		/* code */
		outb(GRAPHICC_INDEX_PORT, i);
		outb(GRAPHICC_DATA_PORT, *(reg++));
	}
	/* SEQUENCER */
	for (unsigned char i = 0; i < 21; ++i)
	{
		/* code */
		inb(ATTRIBUTEC_RESET_PORT);
		outb(ATTRIBUTEC_INDEX_PORT, i);
		outb(ATTRIBUTEC_WRITE_PORT, *(reg++));
	}

	inb(ATTRIBUTEC_RESET_PORT);
	outb(ATTRIBUTEC_INDEX_PORT, 0x20);
}

unsigned char* getframebuffersegment(void){
	outb(GRAPHICC_INDEX_PORT,0x06);
	unsigned char segment = ((inb(GRAPHICC_DATA_PORT)>>2)&0x03);
	switch(segment){
		default:
		case 0: return (unsigned char*) 0x00000;
		case 1: return (unsigned char*) 0xA0000;
		case 2: return (unsigned char*) 0xB0000;
		case 3: return (unsigned char*) 0xB8000;
	}
}

unsigned char getcolor(unsigned char r, unsigned char g, unsigned char b){
	if(r==0x00 && g==0x00 && b==0x00) return 0x00;
	if(r==0xab && g==0x00 && b==0x00) return 0x04;
	if(r==0x00 && g==0x00 && b==0xab) return 0x01;
	if(r==0x00 && g==0xab && b==0x00) return 0x02;
	if(r==0xFF && g==0xFF && b==0xFF) return 0x3F;
	return 0;
}

void setpixel(unsigned int x, unsigned int y, unsigned char colorindex){
	unsigned char* pixcelptr = getframebuffersegment() + 320 *y +x;
	*pixcelptr = colorindex;
}

void putpixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b){
	setpixel(x, y , getcolor(r,g,b));
}

void vga_init(void){
	if(!setmode(320, 200,8))
		return;
	for (int y = 0; y < 200; ++y)
		for (int x = 0; x < 320; ++x)
			putpixel(x, y, 0x0, 0x0, 0xab);
	
}