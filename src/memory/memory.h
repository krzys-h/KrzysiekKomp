#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/types.h"

#define MEMORY_HEADER_MAGIC 0xABCD1234
typedef struct t_memory_header t_memory_header;
struct t_memory_header {
	u32int magic;
	u8int used;
	u32int size;
	t_memory_header* next;
} __attribute__((packed));

#define NULL 0x00000000
extern u8int* memory;

void* malloc(unsigned int size);
void free(void* addr);

#ifdef __cplusplus
}
#endif
