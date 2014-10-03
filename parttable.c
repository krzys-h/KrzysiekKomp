#include "main.h"

MBR_t mbr;
partition_t partition[4];
u8int partition_bootable;

void parttable_load()
{
	disc_read_chs(0, 0, 0, 1, 1, (u8int*)&mbr);
	
	partition[0] = parttable_process(mbr.part[0]);
	partition[1] = parttable_process(mbr.part[1]);
	partition[2] = parttable_process(mbr.part[2]);
	partition[3] = parttable_process(mbr.part[3]);
	
	partition_bootable = 0xFF;
	if(partition[0].bootable) partition_bootable = 0;
	if(partition[1].bootable) partition_bootable = 1;
	if(partition[2].bootable) partition_bootable = 2;
	if(partition[3].bootable) partition_bootable = 3;
	
	parttable_initfs(0);
	parttable_initfs(1);
	parttable_initfs(2);
	parttable_initfs(3);
}

partition_t parttable_process(MBR_partition_t part)
{
	partition_t __ret;
	__ret.bootable = (part.bootable != 0);
	__ret.start_H = part.start_H;
	__ret.start_C = part.start_C & 0x3F;
	__ret.start_S = ((part.start_C & 0xC0) << 2) | part.start_S;
	__ret.filesystem = part.systemID;
	__ret.used = (part.systemID != FS_NONE);
	__ret.end_H = part.end_H;
	__ret.end_C = part.end_C & 0x3F;
	__ret.end_S = ((part.end_C & 0xC0) << 2) | part.end_S;
	__ret.relative_start = part.relative_start;
	__ret.total_sectors = part.total_sectors;
	return __ret;
}

partition_t parttable_get(u8int id)
{
	return partition[id];
}

partition_t parttable_getbootable()
{
	return partition[partition_bootable];
}

void parttable_initfs(u8int id)
{
	if(partition[id].used == 1) {
		if(partition[id].filesystem == FS_LINUX) {
			ext2_init(id);
		} else {
			vga_puts("[WARN] [INIT] [FS] [PART");
			pisz_u8int(id);
			vga_puts("] Nieobslugiwany system plikow!\n");
		}
	}
}
