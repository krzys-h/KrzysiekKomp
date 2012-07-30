#ifndef __DISC_H_
#define __DISC_H_

void disc_read(u8int disc, u8int head, u16int cylinder, u8int sector, u8int sector_count, u8int* buffer);

#endif