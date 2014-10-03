#ifndef __DISC_H_
#define __DISC_H_

void disc_read(u8int disc, u32int lba, u8int sector_count, void* buffer);
void disc_read_chs(u8int disc, u8int head, u16int cylinder, u8int sector, u8int sector_count, void* buffer);

#endif
