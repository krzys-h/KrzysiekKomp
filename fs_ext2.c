#include "main.h"

ext2_superblock_t superblock[4];
ext2_block_group_desc_t block_group_desc[4][BLOCK_SIZE/32];

#define blksize() (1024 << superblock[id].block_size)

#define DEBUG(what) 	pisz_u32int(what); \
	vga_putch('\n');

void ext2_init(u8int id)
{
	vga_puts("[INFO] [INIT] [FS] [PART");
	pisz_u8int(id+1);
	vga_puts("] [EXT2] Uruchamianie sterownika...\n");

	vga_puts("[INFO] [INIT] [FS] [PART");
	pisz_u8int(id+1);
	vga_puts("] [EXT2] Ladowanie superbloku...\n");
	disc_read(0, partition[id].relative_start+2, 2, &superblock[id]);
	if(superblock[id].signature != EXT2_SIGNATURE) {
		vga_puts("[ERROR] [INIT] [FS] [PART");
		pisz_u8int(id+1);
		vga_puts("] [EXT2] Bledna sygnatura!\n");
	}
	
	DEBUG(blksize());

	vga_puts("[INFO] [INIT] [FS] [PART");
	pisz_u8int(id+1);
	vga_puts("] [EXT2] Ladowanie tablicy deskyptorow grup blokow...\n");
	disc_read(0, partition[id].relative_start+((BLOCK_SIZE*2)/512), BLOCK_SIZE/512, &block_group_desc[id]); // ((superblock[id].block_size << 10)/512

/*int i=0;
char buf[BLOCK_SIZE];
disc_read(0, partition[id].relative_start+((BLOCK_SIZE*2)/512), BLOCK_SIZE/512, &buf);
for(; i<BLOCK_SIZE; i++) { pisz_u32int(i); vga_putch(':'); pisz_u8int(buf[i]); vga_putch('\n'); delay(10);}*/

	vga_puts("[INFO] [INIT] [FS] [PART");
	pisz_u8int(id+1);
	vga_puts("] [EXT2] Sterownik uruchomiony!\n");

	ext2_get_inode(id, 2); // 2 = /
}

void ext2_get_inode(u8int id, u32int inode)
{
	char buf[BLOCK_SIZE];

	u32int inode_blockgroup = (inode - 1) / superblock[id].inodes_in_group;
	DEBUG(block_group_desc[id][0].unallocated_blocks);
	disc_read(0, partition[id].relative_start+(((block_group_desc[id][inode_blockgroup].inode_table-1)*BLOCK_SIZE)/512), BLOCK_SIZE/512, (u8int*)&buf);
	u32int* inodes = (u32int*)&buf;
	//u32int inode_idx = inode_ptrs[(inode - 1) % superblock[id].inodes_in_group];
	//u32int inode_block = (inode_idx * (superblock[id].version_major >= 1 ? superblock[id].size_of_inode : 128)) / BLOCK_SIZE;
	//DEBUG(inode_block);
	//vga_putch(':'); vga_putch('\n');
	//DEBUG(inode_idx);
	
	/*ext2_dir_inode_entry_t dir;
	char buf[BLOCK_SIZE];
	disc_read(0, partition[id].relative_start+2+((inode_block*BLOCK_SIZE)/512), BLOCK_SIZE/512, (u8int*)&buf);*/

	ext2_inode_t *inode_data = &(inodes[inode-1]);

	DEBUG(inode_data->type_permissions);

	/*u32int i = 0;
	for(; i<BLOCK_SIZE; i++) { pisz_u32int(i); vga_putch(':'); pisz_u8int(((ext2_inode_t*)((&buf+i)))->type_permissions); vga_putch('\n'); delay(50); }*/

	/*int i=0;
	for(; i<sizeof(ext2_dir_inode_entry_t); i++) *((char*)(&dir)+i) = buf[i];
	DEBUG(dir.inode);
	DEBUG(dir.size);
	DEBUG(dir.name[0]);
	vga_puts(dir.name);*/
	
	return;
}
