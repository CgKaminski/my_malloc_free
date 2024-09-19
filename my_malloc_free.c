// my *malloc() and free() implementation

#define HEAP_START 0x80010000
#define HEAP_END 0x80020000
#define HEAP_SIZE (HEAP_END - HEAP_START)


void *malloc(size_t size) {
  return NULL;
}

void free(void *ptr) {
  return NULL;
}