#ifndef __FS_FAT32_H_
#define __FS_FAT32_H_

typedef struct fat32_boot {
	u8int jmp[3];
	//BPB
	u8int OEM[8];
	u16int bytes_per_S;
	u8int S_per_cluster;
	u16int reserved_sectors;
	u8int FATs;
	u16int directory_entries;
	u16int total_sectors;
	u8int MDT; // Media Descriptor Type
	u16int unused; // Number of sectors per FAT. FAT12/FAT16 only.
	u16int S_per_T;
	u16int heads;
	u32int hidden_sectors;
	u32int large_total_sectors;
	//EBPB
	u32int S_per_FAT;
	u16int flags;
	u8int version_minor;
	u8int version_major;
	u32int root_dir_cluster;
	u16int FSInfo_cluster;
	u16int backup_boot_cluster;
	u8int reserved[12];
	u8int drive_nr;
	u8int flags_WinNT;
	u8int signature; // must be 0x28 or 0x29
	u32int VolumeID_serial; // You can ignore this if you want.
	u8int label[11];
	u8int systemID[8];
	//Bootloader
	u8int code[420];
	u16int boot_magic; // 0xAA55
} __attribute__((packed)) fat32_boot_t;

void fat32_init(u8int id);

#endif