#include "main.h"

ext2_superblock_t superblock[4];
ext2_block_group_desc_table_t block_group_desc_table[4];

void ext2_init(u8int id)
{
	vga_puts("[INFO] [INIT] [FS] [PART");
	pisz_u8int(id+1);
	vga_puts("] [EXT2] Uruchamianie sterownika...\n");

	vga_puts("[INFO] [INIT] [FS] [PART");
	pisz_u8int(id+1);
	vga_puts("] [EXT2] Ladowanie superbloku...\n");
	disc_read(0, partition[id].start_H, partition[id].start_C, partition[id].start_S+2, 2, (u8int*)&superblock[id]);

	vga_puts("[INFO] [INIT] [FS] [PART");
	pisz_u8int(id+1);
	vga_puts("] [EXT2] Ladowanie tablicy deskyptorow grup blokow...\n");
	disc_read(0, partition[id].start_H, partition[id].start_C, partition[id].start_S+2+((superblock[id].block_size << 10)/512), ((superblock[id].block_size << 10)/512), (u8int*)&block_group_desc_table[id]);

	vga_puts("[INFO] [INIT] [FS] [PART");
	pisz_u8int(id+1);
	vga_puts("] [EXT2] Sterownik uruchomiony!\n");
}
