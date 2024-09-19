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



void *malloc(size_t size) {
  if (!size) return NULL;

  block_t *current = free_list;
  while (current) {
    // Check if block is free and has enough space
    if (current->free && current->size >= size) {
      if (current->size > size + BLOCK_SIZE) {
        // TODO split block
      }
      current->free = 0;
      return (void *)(++current);
    }
    current = current->next;
  }
  return NULL; // No free block found with enough space
}


void free(void *ptr) {
  return NULL;
}