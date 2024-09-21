#include "my_malloc_free.h"

static char heap[HEAP_SIZE];
static block_t *free_list = (block_t *)heap;

/*
 * Initialize the memory system by setting the free_list to the start of the 
 * heap.
 * 
 * Parameters   : None
 * Returns Type : void
 */
void initialize_memory_system() {
	// Set the free_list to the start of the heap
	free_list = (block_t *)heap;
	free_list->size = HEAP_SIZE - BLOCK_SIZE;
	free_list->free = 1;
	free_list->next = NULL;
}

/*
 * Split the block into two blocks. The first block will be allocated and the
 * second block will be free. 
 *
 * Parameters   : block_t *fitting_slot, size_t size
 * Returns Type : void
 */
void split_block(block_t *fitting_slot, size_t size) {
	block_t *new = (void *)((char *)fitting_slot + size + BLOCK_SIZE);
	new->size = (fitting_slot->size) - size - BLOCK_SIZE;
	new->free = 1;
	new->next = fitting_slot->next;
	fitting_slot->size = size;
	fitting_slot->free = 0;
	fitting_slot->next = new;
}

/*
 * Allocate memory of the specified size. If a free block is found with enough
 * space, it is allocated and returned. If no free block is found, NULL is
 * returned.
 * 
 * Parameters   : size_t size
 * Returns Type : void *
*/
void *malloc(size_t size) {
	if (!size) return NULL;

	block_t *current = free_list;
	while (current) {
		// Check if block is free and has enough space
		if (current->free && current->size >= size) {
			if (current->size > size + BLOCK_SIZE) {
				split_block(current, size);
			}
			current->free = 0;
			return (void *)(++current);
		}
		current = current->next;
	}
	return NULL; // No free block found with enough space
}

/*
 * Coalesce free blocks in the free list. If two adjacent blocks are free, they
 * are combined into a single block.
 * 
 * Parameters   : None
 * Returns Type : void
 */
void coalesce_free_blocks() {
	block_t *current = free_list;
	while (current) {
		if (current->free && current->next && current->next->free) {
			current->size += BLOCK_SIZE + current->next->size;
			current->next = current->next->next;
		} else {
			current = current->next;
		}
	}
}

/* 
 * Free the memory block pointed to by ptr. The block is marked as free and
 * coalescing is performed to combine adjacent free blocks.
 * 
 * Parameters   : void *ptr
 * Returns Type : void
 */
void free(void *ptr) {
	if (!ptr) return; // Safety check

	// Move back to the block header
	block_t *block = (block_t *)ptr -1;
	block->free = 1;

	// Coalesce free blocks
	coalesce_free_blocks();
	return;
}
