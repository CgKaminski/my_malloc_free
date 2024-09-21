# Custom Malloc and Free Implementation

## Problem Statement

Implement `malloc` and `free` for a computer with 32-bit addressing. We are provided with a contiguous range of memory from `0x80010000` - `0x8002000` to manage as a heap. 

Must implement the following two functions:

- `void *malloc(size_t bytes);`
- `void free(void *ptr);`

### Requirements:

1. **`malloc()`** should allocate a contiguous block of memory at least the size of `bytes`, and return a pointer to the allocated space.
   - The function should manage the heap memory within the provided range.
   - If there is insufficient memory to satisfy the request, `malloc()` should return `NULL`.
   - Any overhead needed for tracking allocations should be handled transparently to the user.

2. **`free()`** should take a pointer returned by `malloc()` and return the corresponding block of memory back to the heap for reuse.
   - `free()` should not return anything.
   - The function should also be capable of managing fragmentation by merging adjacent free blocks.

---

## Design Approach
The design of the custom `malloc` and `free` functions involves a simple approach that manages contiguous blocks of memory as a heap. The heap is represented as a static array, and memory blocks within the heap are managed using a linked list of the block headers. Each block header contains metadata regarding the block, such as size and whether it is free.

---

## Function Descriptions

### `void *malloc(size_t bytes);`
Allocates a contiguous block of memory of at least the specified size (`bytes`) and returns a pointer to the allocated space. The function manages the heap memory within a predefined range, represented as a static array. The allocation process involves:

1. Checks for allocatable size: If the requested memory allocation is zero, the function returns `NULL`.
2. Block Search: Traverses the free list to find a free block that is at least as large as the allocation request.
3. Block Splitting: If a large enough block is found and it is larger than the request size (plus overhead), the block is split into two separate blocks. The first block is allocated and the second remains free.
4. Allocation: The selected block is marked as allocated, and a pointer to the next block header is returned.
5. Insufficient Memory: If a large enough block is not found, the function returns `NULL`.

---

### `void free(void *ptr);`
Takes a pointer returned by `malloc` and returns the corresponding block of memory back to the heap for reuse. The de-allocation process involves:

1. Safety Check: If the pointer is `NULL` the function returns immediately.
2. Block Header: The function finds the block header by moving the pointer back by the size of the block header.
3. Mark as Free: The block metadata is marked as free.
4. Coalescing Free Blocks: Merges adjacent free blocks into a single larger block reducing fragmentation and making larger contiguous blocks of memory for future allocations.

---

## Limitations and Assumptions

1. `malloc` shall not request more heap space.
2. Single threaded environment.
3. No reallocation.
4. No error handling for corruption, as this would conflict with problem requirements for `free`.

---

## Testing
To ensure functionality I created a small custom test suite for the custom `malloc` and `free` functions.

1. Single Integer Allocation: Tests allocating memory for a single integer and verifies that the allocation is successful.
2. Array of Integers Allocation: Tests allocating memory for an array of 10 integers and verifies that the allocation is successful.
3. Zero Allocation: Tests allocating zero bytes and verifies that the function returns `NULL`.
4. Free NULL Pointer: Tests freeing a `NULL` pointer and verifies that the function handles it gracefully.
5. Coalesce Free Blocks: Tests the coalescing of adjacent free blocks by allocating and freeing two small blocks, then attempting to allocate a larger block that requires the space of both.
6. Allocate Entire Heap: Tests allocating memory for the entire heap and verifies that the allocation is successful.
7. Allocate Out of Memory: Tests allocating memory beyond the heap size and verifies that the function returns `NULL`.
8. Multiple Small Allocations: Tests allocating multiple small blocks and verifies that all allocations are successful.

---