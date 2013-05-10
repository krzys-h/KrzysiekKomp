#ifndef __FS_EXT2_H_
#define __FS_EXT2_H_

typedef struct ext2_superblock {
	u32int total_inodes;
	u32int total_blocks;
	u32int reserved_superuser;
	u32int unallocated_blocks;
	u32int unallocated_inodes;
	u32int superblock_block;
	u32int block_size;
	u32int fragment_size;
	u32int blocks_in_group;
	u32int fragments_in_group;
	u32int inodes_in_group;
	u32int last_mount;
	u32int last_written;
	u16int mounts_since_fsck;
	u16int fsck_after_mounts;
	u16int signature; //0xef53 = ext2
	u16int filesystem_state; //1 = clean, 2 = errors
	u16int error_action; //1 = ignore, 2 = remount r/o, 3 = panic
	u16int version_minor;
	u32int fsck_time;
	u32int fsck_every_time;
	u32int creator_system_id;
	u32int version_major;
	u16int reservedblocks_user;
	u16int reservedblocks_group;
	// Extended: if(version_major >= 1)
	u32int first_nonreserved_inode; // old: 11
	u16int size_of_inode; //old: 128
	u16int part_of_group; //only if it's a backup copy
	u32int optional_features;
	u32int required_features;
	u32int required_features_for_write;
	char   filesystem_id[16];
	char   volume_name[16];
	char   last_mounted_path[64];
	u32int compression;
	u8int  preallocated_blocks_files;
	u8int  preallocated_blocks_directories;
	u16int unused1;
	char   journal_id[16];
	u32int journal_inode;
	u32int journal_device;
	u32int head_of_orphan_inode_list;
	char   unused2[789];
} __attribute__((packed)) ext2_superblock_t;

typedef struct ext2_block_group_desc {
	u32int block_usage_bitmap;
	u32int inode_usage_bitmap;
	u32int inode_table;
	u16int unallocated_blocks;
	u16int unallocated_inodes;
	u16int directories;
	char   unused[14];
} __attribute__((packed)) ext2_block_group_desc_t;

typedef struct ext2_block_group_desc_table {
	ext2_block_group_desc_t desc[1024/sizeof(ext2_block_group_desc_t)];
} __attribute__((packed)) ext2_block_group_desc_table_t;

void ext2_init(u8int id);

#endif
