#include <stdio.h>
#include "my_malloc_free.h"

typedef struct {
    char* name;
    int passed;
} TestResult;

// Test function prototypes
TestResult test_single_integer_allocation();
TestResult test_array_of_integers_allocation();
TestResult test_zero_allocation();
TestResult test_free_null_pointer();
TestResult test_coalesce_free_blocks();
TestResult test_allocate_entire_heap();
TestResult test_allocate_out_of_memory();
TestResult test_multiple_small_allocations();

int main() {
    initialize_memory_system();

    TestResult results[10]; // Adjust the size based on the number of tests
    int total_tests = 0;
    int tests_passed = 0;

    // Test 1: Allocate memory for a single integer
    results[total_tests++] = test_single_integer_allocation();

    // Test 2: Allocate memory for an array of 10 integers
    results[total_tests++] = test_array_of_integers_allocation();

    // Test 3: Allocate memory for zero bytes
    results[total_tests++] = test_zero_allocation();

    // Test 4: Free a NULL pointer
    results[total_tests++] = test_free_null_pointer();

    // Test 5: Coalesce free blocks
    results[total_tests++] = test_coalesce_free_blocks();

    // Test 6: Allocate memory for the entire heap
    results[total_tests++] = test_allocate_entire_heap();

    // Test 7: Allocate memory beyond the heap size
    results[total_tests++] = test_allocate_out_of_memory();

    // Test 8: Allocate multiple small blocks
    results[total_tests++] = test_multiple_small_allocations();

    // Report individual test results and summary statistics
    for (int i = 0; i < total_tests; i++) {
        printf("Test '%s': %s\n", results[i].name, results[i].passed ? "PASS" : "FAIL");
        if (results[i].passed) {
            tests_passed++;
        }
    }

    printf("Summary: %d/%d tests passed.\n", tests_passed, total_tests);

    return 0;
}

TestResult test_single_integer_allocation() {
    int *num = (int *)malloc(sizeof(int));
    if (!num) {
        return (TestResult){"Single Integer Allocation", 0}; // Test failed
    }
    *num = 0x0000002A;
    free(num);
    return (TestResult){"Single Integer Allocation", 1}; // Test passed
}

TestResult test_array_of_integers_allocation() {
    int *arr = (int *)malloc(10 * sizeof(int));
    if (!arr) {
        return (TestResult){"Array of Integers Allocation", 0}; // Test failed
    }
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }
    free(arr);
    return (TestResult){"Array of Integers Allocation", 1}; // Test passed
}

TestResult test_zero_allocation() {
    int *num = (int *)malloc(0);
    if (num) {
        free(num);
        return (TestResult){"Zero Allocation", 0}; // Test failed
    }
    return (TestResult){"Zero Allocation", 1}; // Test passed
}

TestResult test_free_null_pointer() {
    free(NULL);
    return (TestResult){"Free NULL Pointer", 1}; // Test passed
}

TestResult test_coalesce_free_blocks() {
    // Step 1: Allocate two small blocks
    int *num1 = (int *)malloc(sizeof(int));
    int *num2 = (int *)malloc(sizeof(int));

    // Ensure allocations were successful
    if (!num1 || !num2) {
        if (num1) free(num1);
        if (num2) free(num2);
        return (TestResult){"Coalesce Free Blocks", 0}; // Allocation failed, test cannot proceed
    }

    // Step 2: Free both blocks to allow for potential coalescing
    free(num1);
    free(num2);

    // Step 3: Attempt to allocate a larger block that requires the space of both A and B
    int *largeBlock = (int *)malloc(2 * sizeof(int));

    // Step 4: Check if the allocation succeeded
    if (largeBlock) {
        free(largeBlock); // Clean up
        return (TestResult){"Coalesce Free Blocks", 1}; // Test passed, coalescing might have worked
    } else {
        return (TestResult){"Coalesce Free Blocks", 0}; // Test failed, coalescing did not work as expected
    }
}

TestResult test_allocate_entire_heap() {
    // Allocate memory for the entire heap
    int *entireHeap = (int *)malloc(HEAP_SIZE - BLOCK_SIZE);

    // Check if the allocation succeeded
    if (entireHeap) {
        free(entireHeap); // Clean up
        return (TestResult){"Allocate Entire Heap", 1}; // Test passed
    } else {
        return (TestResult){"Allocate Entire Heap", 0}; // Test failed
    }
}

TestResult test_allocate_out_of_memory() {
    // Allocate memory beyond the heap size
    int *outOfMemory = (int *)malloc(HEAP_SIZE + 1);

    // Check if the allocation succeeded
    if (outOfMemory) {
        free(outOfMemory); // Clean up
        return (TestResult){"Allocate Out of Memory", 0}; // Test failed
    } else {
        return (TestResult){"Allocate Out of Memory", 1}; // Test passed
    }
}

TestResult test_multiple_small_allocations() {
    const int num_allocations = 100;
    char *ptrs[num_allocations];
    int i;

    for (i = 0; i < num_allocations; i++) {
        ptrs[i] = (char *)malloc(i);
        if (!ptrs[i]) {
            break; // Allocation failed
        }
    }

    // Check if all allocations were successful
    if (i == num_allocations) {
        for (i = 0; i < num_allocations; i++) {
            free(ptrs[i]);
        }
        return (TestResult){"Multiple Small Allocations", 1}; // Test passed
    } else {
        for (i = 0; i < num_allocations; i++) {
            if (ptrs[i]) free(ptrs[i]);
        }
        return (TestResult){"Multiple Small Allocations", 0}; // Test failed
    }
}