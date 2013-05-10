#ifndef __PARTTABLE_H_
#define __PARTTABLE_H_

#define FS_NONE 0x00
#define FS_FAT12 0x01
#define FS_FAT16A 0x04
#define FS_FAT16B 0x06
#define FS_FAT32 0x0B
#define FS_LINUX 0x83

typedef struct MBR_partiton {
	u8int bootable; // Boot indicator bit flag: 0 = no, 0x80 = bootable (or "active")
	u8int start_H; // Starting head
	u8int start_S; // Starting sector (Bits 6-7 are the upper two bits for the Starting Cylinder field.)
	u8int start_C; // Starting Cylinder
	u8int systemID; // System ID (FS type)
	u8int end_H; // Ending Head
	u8int end_S; // Ending Sector (Bits 6-7 are the upper two bits for the ending cylinder field)
	u8int end_C; // Ending Cylinder
	u16int relative_start; // Relative Sector (to start of partition -- also equals the partition's starting LBA value)
	u16int total_sectors; // Total Sectors in partition
} __attribute__((packed)) MBR_partition_t;

typedef struct MBR {
	u8int code[446];
	MBR_partition_t part[4];
	u16int boot_magic; // 0xAA55
} __attribute__((packed)) MBR_t;

typedef struct partiton {
	u8int bootable; // Boot indicator bit flag: 0 = no, 1 = bootable (or "active")
	u8int start_H; // Starting head
	u8int start_S; // Starting sector (6 bits)
	u16int start_C; // Starting Cylinder (10 bits)
	u8int filesystem; // System ID (FS type)
	u8int used; // 1 = used, 0 = unused
	u8int end_H; // Ending Head
	u8int end_S; // Ending Sector (6 bits)
	u16int end_C; // Ending Cylinder (10 bits)
	u16int relative_start; // Relative Sector (to start of partition -- also equals the partition's starting LBA value)
	u16int total_sectors; // Total Sectors in partition
} __attribute__((packed)) partition_t;

extern MBR_t mbr;
extern partition_t partition[4];
extern u8int partition_bootable;

void parttable_load();
partition_t parttable_process(MBR_partition_t part);
partition_t parttable_get(u8int id);
partition_t parttable_getbootable();
void parttable_initfs(u8int id);

#endif
