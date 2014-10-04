#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/types.h"

void hdd_read(u32int lba, u8int sector_count, u8int* buffer);

#ifdef __cplusplus
}
#endif
