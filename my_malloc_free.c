// my *malloc() and free() implementation

#define HEAP_START 0x80010000
#define HEAP_END 0x80020000
#define HEAP_SIZE (HEAP_END - HEAP_START)

typedef struct block {
  size_t size;
  int free;
  struct block *next;
} block_t;

#define BLOCK_SIZE sizeof(block_t)

static char heap[HEAP_SIZE];
static block_t *free_list = (block_t *)heap;

void split_block(block_t *fitting_slot, size_t size) {
  block_t *new = (void *)((char *)fitting_slot + size + BLOCK_SIZE);
  new->size = (fitting_slot->size) - size - BLOCK_SIZE;
  new->free = 1;
  new->next = fitting_slot->next;
  fitting_slot->size = size;
  fitting_slot->free = 0;
  fitting_slot->next = new;
}

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


void free(void *ptr) {
  if (!ptr) return; // Safety check

  // Move back to the block header
  block_t *block = (block_t *)ptr -1;
  block->free = 1;
  return;
}