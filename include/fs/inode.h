#ifndef NOS_FILE_H
#define NOS_FILE_H

struct file
{
	unsigned short mode;
	unsigned int uid;
	unsigned int size;
	unsigned int atime;
	unsigned int ctime;
	unsigned int mtime;
	unsigned int dtime;
	unsigned short gid;
	unsigned int links_count;
	unsigned int block[15];
};

struct m_file
{
	unsigned short mode;
	unsigned int uid;
	unsigned int size;
	unsigned int atime;
	unsigned int ctime;
	unsigned int mtime;
	unsigned int dtime;
	unsigned short gid;
	unsigned int links_count;
	unsigned int blocks;
	unsigned int flags;
	unsigned int block[15];
	unsigned int i_mount;
	unsigned int i_num;
	unsigned int dev;
};

#endif