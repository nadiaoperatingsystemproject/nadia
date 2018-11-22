#ifndef SUPER_BLOCK_H
#define SUPER_BLOCK_H
#include "../hd.h"
struct fs_block {
    unsigned int inodes_count;     /* Total number of inodes */
    unsigned int blocks_count;     /* Total number of blocks */
    unsigned int r_blocks_count;   /* Total number of blocks reserved for the super user */
    unsigned int free_blocks_count;        /* Total number of free blocks */
    unsigned int free_inodes_count;        /* Total number of free inodes */
    unsigned int first_data_block; /* Id of the block containing the superblock structure */
    unsigned int log_block_size;   /* Used to compute block size = 1024 << s_log_block_size */
    unsigned int log_frag_size;    /* Used to compute fragment size */
    unsigned int blocks_per_group; /* Total number of blocks per group */
    unsigned int frags_per_group;  /* Total number of fragments per group */
    unsigned int inodes_per_group; /* Total number of inodes per group */
    unsigned int mtime;            /* Last time the file system was mounted */
    unsigned int wtime;            /* Last write access to the file system */
    unsigned short mnt_count;        /* How many `mount' since the last was full verification */
    unsigned short max_mnt_count;    /* Max count between mount */
    unsigned short magic;            /* = 0xEF53 */
    unsigned short state;            /* File system state */
    unsigned short errors;           /* Behaviour when detecting errors */
    unsigned short minor_rev_level;  /* Minor revision level */
    unsigned int lastcheck;        /* Last check */
    unsigned int checkinterval;    /* Max. time between checks */
    unsigned int creator_os;       /* = 5 */
    unsigned int rev_level;        /* = 1, Revision level */
    unsigned short def_resuid;       /* Default uid for reserved blocks */
    unsigned short def_resgid;       /* Default gid for reserved blocks */
    unsigned int first_ino;        /* First inode useable for standard files */
    unsigned short inode_size;       /* Inode size */
    unsigned short block_group_nr;   /* Block group hosting this superblock structure */
    unsigned int feature_compat;
    unsigned int feature_incompat;
    unsigned int feature_ro_compat;
    unsigned char uuid[16];          /* Volume id */
    char volume_name[16]; /* Volume name */
    char last_mounted[64];        /* Path where the file system was last mounted */
    unsigned int algo_bitmap;      /* For compression */
    unsigned char padding[820];
} __attribute__ ((packed));

#endif