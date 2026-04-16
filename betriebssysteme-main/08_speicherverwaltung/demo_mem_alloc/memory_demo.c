/**
 * Linux Memory Allocation Demo
 * 
 * This program demonstrates different types of memory allocation in Linux:
 * 1. Stack allocation (automatic memory)
 * 2. Heap allocation (dynamic memory)
 * 3. Memory mapping (mmap)
 * 4. Copy-on-Write behavior
 * 5. Memory pressure testing
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <sys/mman.h>
 #include <sys/types.h>
 #include <sys/wait.h>
 
 // Constants for memory sizes
 #define MB (1024 * 1024)                    // 1 Megabyte in bytes
 #define ARRAY_SIZE (100 * MB)               // 100MB array size
 #define MAX_MEMORY_USAGE_PERCENT 80         // Stop when we reach 80% of physical memory
 
 /**
  * Helper function to print memory information and wait for user input
  * This allows us to observe memory changes at each step
  */
 void print_memory_info(const char* message) {
     printf("\n%s\n", message);
     printf("Press Enter to continue...");
     getchar();
 }
 
 int main() {
     printf("Memory Allocation Demo Program\n");
     printf("PID: %d\n", getpid());
     print_memory_info("Initial state");
 
     // 1. Stack Allocation
     // - Memory is automatically allocated on the stack
     // - Size is fixed at compile time
     // - Memory is automatically freed when the function returns
     // - Limited by stack size (typically 8MB on Linux)
     char stack_array[MB];  // Allocate 1MB on stack
     memset(stack_array, 'A', MB);  // Fill with 'A' to ensure memory is actually allocated
     print_memory_info("After stack allocation");
 
     // 2. Heap Allocation
     // - Memory is dynamically allocated using malloc
     // - Size can be determined at runtime
     // - Must be manually freed using free()
     // - Limited by available physical memory and swap
     char* heap_array = (char*)malloc(ARRAY_SIZE);
     if (heap_array == NULL) {
         perror("malloc failed");
         return 1;
     }
     memset(heap_array, 'B', ARRAY_SIZE);  // Fill with 'B' to ensure memory is actually allocated
     print_memory_info("After heap allocation");
 
     // 3. Memory Mapping (mmap)
     // - Creates a new mapping in the virtual address space
     // - Can be used for large allocations
     // - More flexible than malloc for certain use cases
     // - Can be shared between processes
     char* mmap_array = (char*)mmap(NULL, ARRAY_SIZE, 
                                   PROT_READ | PROT_WRITE,  // Memory protection: read and write
                                   MAP_PRIVATE | MAP_ANONYMOUS,  // Private, not file-backed
                                   -1, 0);
     if (mmap_array == MAP_FAILED) {
         perror("mmap failed");
         return 1;
     }
     memset(mmap_array, 'C', ARRAY_SIZE);  // Fill with 'C' to ensure memory is actually allocated
     print_memory_info("After mmap allocation");
 
     // 4. Fork and Copy-on-Write Demonstration
     // - Creates a child process that shares memory with parent
     // - Demonstrates Linux's copy-on-write optimization
     // - Memory is only copied when modified by either process
     pid_t pid = fork();
     if (pid < 0) {
         perror("fork failed");
         return 1;
     } else if (pid == 0) {
         // Child process
         printf("\nChild process (PID: %d)\n", getpid());
         // Modify some memory in child to trigger copy-on-write
         memset(heap_array, 'D', MB);
         print_memory_info("Child process after modifying memory");
         exit(0);
     } else {
         // Parent process
         wait(NULL);  // Wait for child to finish
         print_memory_info("Parent process after child exit");
     }
 
     // 5. Memory Pressure Test
     // - Gradually allocates memory until reaching target
     // - Demonstrates system behavior under memory pressure
     // - Shows how memory allocation fails when system is under pressure
     printf("\nStarting memory pressure test...\n");
     char* pressure_array = NULL;
     size_t total_allocated = 0;
     
     // Calculate maximum allocation based on physical memory
     long total_physical_memory = sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE);
     size_t max_allocation = (total_physical_memory * MAX_MEMORY_USAGE_PERCENT) / 100;
     
     printf("Total physical memory: %ld MB\n", total_physical_memory / MB);
     printf("Maximum allocation target: %zu MB\n", max_allocation / MB);
     
     // Allocate memory in 1MB chunks until reaching target
     while (total_allocated < max_allocation) {
         char* new_array = (char*)malloc(MB);
         if (new_array == NULL) {
             printf("Failed to allocate more memory after %zu MB\n", total_allocated);
             break;
         }
         memset(new_array, 'E', MB);  // Fill with 'E' to ensure memory is actually allocated
         pressure_array = new_array;  // Keep reference to prevent optimization
         total_allocated += MB;
         
         // Print progress every 100MB
         if (total_allocated % (100 * MB) == 0) {
             printf("Allocated %zu MB (%.1f%% of target)\n", 
                    total_allocated, 
                    (float)total_allocated * 100 / max_allocation);
             print_memory_info("After memory pressure allocation");
         }
     }
 
     printf("\nMemory pressure test completed.\n");
     printf("Total memory allocated: %zu MB\n", total_allocated);
     printf("Target memory usage: %zu MB\n", max_allocation / MB);
 
     // Cleanup: Free all allocated memory
     free(heap_array);
     munmap(mmap_array, ARRAY_SIZE);
     print_memory_info("After cleanup");
 
     return 0;
 } 