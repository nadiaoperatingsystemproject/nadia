#ifndef NOS_FILE_SYSTEM_H
#define NOS_FILE_SYSTEM_H
#include "sblock.h"
#include "inode.h"
// set block size of disk
#define	BLOCKSIZE	0x1000
// define type of file
#define FS_REGULARY		0x1
#define FS_DIRECTORY	0x2
#define FS_CHARDEVICE	0x3
#define FS_BLOCKDEVICE	0x4
#define FS_PIPE			0x5
#define FS_SYMBOLELINK	0x6
#define FS_MOUNTPOINT	0x8
typedef struct m_file m_file;
typedef struct s_inode s_inode;
struct s_grp
{
	unsigned int *i_map;
	unsigned int *d_map;
	m_file* i_table;
};

struct s_fs
{
	struct mbr* bootsect;
	struct fs_block* fs_sb;
	struct s_grp* grp;
};

struct file
{
	unsigned char name[30];
	unsigned int perm;
	unsigned int i_node;
};


struct dev_s
{
	unsigned int device;
	unsigned int id;
	unsigned char name[1024];
	struct s_fs* fs;
};

typedef struct file file;
typedef struct dev_s dev_t;
void init_fs(void);
void* read_super_block(dev_t* dev);
int read(dev_t* dev, file *f, char* b);
int write(dev_t* dev, file *f, char* b);
char* read_node(dev_t *dev, unsigned int i_num);
char* write_node(dev_t *dev, unsigned int i_num, const char* b);
#endif