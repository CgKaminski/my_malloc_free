#include <stdio.h>
#include "my_malloc_free.h"

int main() {

  // Initialize the memory system
  initialize_memory_system();

  // Test 1: Allocate memory for a single interger
  int *num = (int *)malloc(sizeof(int));
  if (!num) {
    printf("Failed to allocate memory for num\n");
    return 1;
  }
  *num = 0x0000002A;
  printf("num = %d\n", *num);
  free(num);

  // Test 2: Allocate memory for an array of 10 integers
  int *arr = (int *)malloc(10 * sizeof(int));
  if (!arr) {
    printf("Failed to allocate memory for arr\n");
    return 1;
  }
  for (int i = 0; i < 10; i++) {
    arr[i] = i;
  }
  for (int i = 0; i < 10; i++) {
    printf("arr[%d] = %d\n", i, arr[i]);
  }
  free(arr);


  printf("Memory allocation free and tests complete.");
  return 0;
}