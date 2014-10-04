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
inline void *operator new(size_t size)
{
    return malloc(size);
}
 
inline void *operator new[](size_t size)
{
    return malloc(size);
}
 
inline void operator delete(void *p)
{
    free(p);
}
 
inline void operator delete[](void *p)
{
    free(p);
}

inline void *operator new(size_t, void *p)     throw() { return p; }
inline void *operator new[](size_t, void *p)   throw() { return p; }
inline void  operator delete  (void *, void *) throw() { };
inline void  operator delete[](void *, void *) throw() { };
#endif

#ifdef __cplusplus
}
#endif
