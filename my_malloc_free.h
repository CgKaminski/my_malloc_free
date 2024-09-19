#ifndef MY_MALLOC_FREE_H
#define MY_MALLOC_FREE_H

#include <stddef.h>

#define HEAP_START 0x80010000
#define HEAP_END 0x80020000
#define HEAP_SIZE (HEAP_END - HEAP_START)
#define BLOCK_SIZE sizeof(block_t)

typedef struct block {
  size_t size;
  int free;
  struct block *next;
} block_t;

void initialize_memory_system();
void split_block(block_t *fitting_slot, size_t size);
void *malloc(size_t size);
void free(void *ptr);

#endif // MY_MALLOC_FREE_H