#include "main.h"

fat32_boot_t boot[4];
u8int partid;

void fat32_init(u8int id)
{
	vga_puts("[INFO] [INIT] [FS] [PART");
	pisz_u8int(id+1);
	vga_puts("] [FAT32] Wczytywanie bootsectora...\n");
	disc_read(0, partition[id].start_H, partition[id].start_C, partition[id].start_S, 1, (u8int*)&boot[id]);

	partid = id;
	
	vga_puts("[INFO] [INIT] [FS] [PART");
	pisz_u8int(id+1);
	vga_puts("] [FAT32] Sterownik uruchomiony!\n");
}

void fat32_readfile(u32int start_cluster, u8int* buffer)
{
	u32int active_cluster = start_cluster;
	u8int* __buffer = buffer;
	for(;;) {
		u8int FAT_table[boot[partid].bytes_per_S * boot[partid].S_per_cluster];
		u32int fat_offset = active_cluster * 4;
		u32int fat_sector = boot[partid].reserved_sectors + (fat_offset / (boot[partid].bytes_per_S * boot[partid].S_per_cluster));
		u32int ent_offset = fat_offset % (boot[partid].bytes_per_S * boot[partid].S_per_cluster);
		 
		disc_read(0, partition[partid].start_H, partition[partid].start_C, fat_sector, 1, (u8int*)&FAT_table[0]);
		
		u32int table_value = *(u32int*)&FAT_table[ent_offset] & 0x0FFFFFFF;
		
		vga_puts("[INFO] [FS] [PART");
		pisz_u8int(partid+1);
		vga_puts("] [FAT32] table_value = ");
		pisz_u32int(table_value);
		vga_putch('\n');
		
		if(table_value >= 0x0FFFFFF8) break;
		if(table_value == 0x0FFFFFF7) break; //Stop reading file on bad sector - in future I'll change this
		
		//disc_read(0, cluster_to_H(table_value), cluster_to_C(table_value), cluster_to_S(table_value), boot[partid].S_per_cluster, (u8int*)__buffer);
		//__buffer += boot[partid].bytes_per_S * boot[partid].S_per_cluster;		
		active_cluster = table_value;
		
		/* If "table_value" is greater than or equal to (>=) 0x0FFFFFF8 then there are no more clusters in the chain. This means that the whole file has been read. If "table_value" equals (==) 0x0FFFFFF7 then this cluster has been marked as "bad". "Bad" clusters are prone to errors and should be avoided. If "table_value" is not one of the above cases then it is the cluster number of the next cluster in the file. */
	}
}