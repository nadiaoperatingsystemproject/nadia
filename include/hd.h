#ifndef NOS_HDD_H
#define NOS_HDD_H

struct partition
{
	unsigned char bootable;

	unsigned char f_head;
	unsigned char f_sect;
	unsigned char f_cyl;

	unsigned char part_id;	// type fs

	unsigned char e_head;
	unsigned char e_sect;
	unsigned char e_cyl;

	unsigned char lba;		//start lba
	unsigned char length;
}__attribute__ ((packed));

struct mbr
{
	unsigned char code[440];
	unsigned int signature;
	unsigned short unused;

	struct partition pr_part[4];
	unsigned short magic;
}__attribute__ ((packed));

void *read_disk(void);
void write_disk(void);
void *read_b(void);
void write_b(void);
#endif