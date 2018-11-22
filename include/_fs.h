#ifndef NOS_FILE_SYSTEM_H
#define NOS_FILE_SYSTEM_H
#include "hd.h"
struct BPB_s
{
	unsigned char jump[3];
	unsigned char solfname[8];
	unsigned short bytesPerSector;
	unsigned char sectorsPerCluster;
	unsigned short reservedSectors;		// contain number sectors reserved
	unsigned char fatCopies;
	unsigned short rootDirEntries;
	unsigned short totalSectors;
	unsigned char mediaType;
	unsigned short fatSectorCount;
	unsigned short sectorPerTrack;
	unsigned short headCount;
	unsigned int hiddenSectors;
	unsigned int totalSectorCount;

	unsigned int tableSize;				// fat size
	unsigned short extFlags;
	unsigned short fatVersion;
	unsigned int rootCluster;
	unsigned short fatInfo;
	unsigned short backupSector;
	unsigned char reserved0[12];
	unsigned char driveNumber;
	unsigned char reserved;
	unsigned char bootSignature;
	unsigned int volumeId;
	unsigned char volumeLabel[11];
	unsigned char fatTypeLabel[8];
}__attribute__((packed));

struct dirent
{
	unsigned char name[8];
	unsigned char ext[3];
	unsigned char attributes;
	unsigned char reserved;
	unsigned char cTimeTenth;
	unsigned short cTime;
	unsigned short cDate;
	unsigned short aTime;

	unsigned short firstClusterHi;

	unsigned short wTime;
	unsigned short wDate;
	unsigned short firstClusterLow;
	unsigned int size;
}__attribute__((packed));


struct dev_s
{
	struct mbr bootsect;
	unsigned int device;
	unsigned int id;
	unsigned char name[1024];
	struct dirent* data;
};

typedef struct dev_s dev_t;
void init_fs(dev_t*);
#endif