#include "memory/memory.h"

#include "common/asm.h"
#include "screen/text_screen.h"

extern u8int kernel_end;
u8int* memory = &kernel_end;

void* malloc(unsigned int size)
{
	t_memory_header* current = (t_memory_header*)memory;
	while(true) {
		if(current->magic != MEMORY_HEADER_MAGIC) {
			if((u8int*)current == memory) {
				// Initialize first block, taking full memory
				current->magic = MEMORY_HEADER_MAGIC;
				current->used = 0;
				current->size = 0xFFFFFFFF;
				current->next = NULL;
			} else {
				screen_print("malloc(): Bad magic, memoty corruption\n");
				hang();
			}
		}
		
		if(current->used == 0) {
			if(current->size >= size) {
				// let's use this block
				t_memory_header* next_block = current->next;
				if(current->next == NULL || current->size > size+sizeof(t_memory_header)) {
					next_block = (void*)(((u32int)current)+sizeof(t_memory_header)+size);
					next_block->magic = MEMORY_HEADER_MAGIC;
					next_block->used = 0;
					next_block->size = current->size-size-sizeof(t_memory_header);
					next_block->next = current->next;
				}
				current->size = size;
				current->next = next_block;
				current->used = 1;
				return (void*)(((u32int)current)+sizeof(t_memory_header));
			}
		}
		
		current = current->next;
		if(current == NULL)
			break;
	}
	screen_print("Out of memory\n");
	hang();
	return NULL;
}

void free(void* addr)
{
	t_memory_header* this_block = (t_memory_header*)(((u32int)addr)-sizeof(t_memory_header));
	if(this_block->magic != MEMORY_HEADER_MAGIC) {
		screen_print("free(): Bad magic, memoty corruption\n");
		hang();
		return;
	}
	this_block->used = 0;
	
	// Now, let's collapse all free memory blocks
	t_memory_header* current = this_block;
	while(true) {
		if(current->used != 0)
			break;
		
		current = current->next;
		if(current == NULL)
			break;
	}
	
	this_block->size = ((u32int)current)-((u32int)addr);
	this_block->next = current;
}
