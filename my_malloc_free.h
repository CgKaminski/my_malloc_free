#ifndef MY_MALLOC_FREE_H
#define MY_MALLOC_FREE_H

#include <stddef.h>

// Define the heap size and block size
#define HEAP_START 0x80010000
#define HEAP_END 0x80020000
#define HEAP_SIZE (HEAP_END - HEAP_START)
#define WORD_SIZE 4 

#define BLOCK_SIZE sizeof(block_t)
#define ALIGN(size) (((size) + (WORD_SIZE - 1)) & ~(WORD_SIZE - 1))

/*
 * Define the block structure. Each block contains a size field to store the
 * size of the block, a free field to indicate if the block is free, and a next
 * field to point to the next block in the free list.
 */
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