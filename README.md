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

*Describe the high-level design of the solution*

---

## Function Descriptions

### `void *malloc(size_t bytes);`

*Provide details about how function is implemented, how memory is allocated, and how splitting of blocks is handled.*

---

### `void free(void *ptr);`

*Explain how `free()` works, how blocks are returned to the heap, and how block coalescing (if any) is managed.*

---

## Memory Management

*Explain how memory is tracked, how block metadata is handled, and what data structures are used (e.g., free list, linked list of blocks).*

---

## Limitations and Assumptions

*Describe any assumptions made (e.g., no external libraries are used) and any limitations of the current implementation.*

---

## Testing

*Provide instructions or descriptions of how to test the `malloc` and `free` functions to ensure they work correctly.*

---

## Future Improvements

*List potential areas for improvement, optimizations, or enhancements to the current implementation.*

---
