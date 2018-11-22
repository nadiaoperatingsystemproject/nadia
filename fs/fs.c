#ifndef NOS_FILE_SYSTEM
#define NOS_FILE_SYSTEM
#include "../include/fs/fs.h"
#include "../kernel/include/i386/memory.h"
#include "../kernel/include/kprint.h"
#include "../include/assert.h"
#include "../include/string.h"
#endif
dev_t* current_dev_disk;
void init_fs(void){
	//check device
	
	// mount device

	// init fs structure
	current_dev_disk->fs = (struct s_fs*) malloc(sizeof(struct s_fs));
	current_dev_disk->fs->fs_sb = (struct fs_block*) malloc(sizeof(struct fs_block));
	current_dev_disk->fs->grp = (struct s_grp*) malloc(sizeof(struct s_grp));
	
	current_dev_disk->fs->grp->i_map = (unsigned int*) malloc(sizeof(unsigned int)*1024);
	memset((unsigned char*) current_dev_disk->fs->grp->i_map,0,sizeof(unsigned int)*1024);
	current_dev_disk->fs->grp->d_map = (unsigned int*) malloc(sizeof(unsigned int)*1024);
	memset((unsigned char*) current_dev_disk->fs->grp->d_map,0,sizeof(unsigned int)*1024);
	current_dev_disk->fs->grp->i_table = (m_file*) malloc(sizeof(m_file)*8*1024);
	memset((unsigned char*) current_dev_disk->fs->grp->i_table,0,sizeof(unsigned int)*8*1024);

	current_dev_disk->device = 0;
	//init root directory
}

void* read_super_block(dev_t* dev){

}

void* write_super_block(dev_t* dev){

}

int read(dev_t* dev, file *f, char* b){

}

int readchunk(dev_t* dev, file *f, char* b, unsigned int size){

}

int write(dev_t* dev, file *f, char* b){

}

int writechunk(dev_t* dev, file *f, char* b, unsigned int size){

}

char* read_node(dev_t *dev, unsigned int i_num){

}

char* write_node(dev_t *dev, unsigned int i_num, const char* b){

}

//16150095649