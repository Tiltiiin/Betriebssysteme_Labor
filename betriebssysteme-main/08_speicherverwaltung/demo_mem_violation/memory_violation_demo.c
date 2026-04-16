/**
 * Memory Safety Violation Demo
 * 
 * This program demonstrates various ways a process can crash by violating memory safety rules.
 * WARNING: This program is intentionally designed to crash in different ways.
 * It's for educational purposes only to understand why memory safety is important.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 
 // Function to demonstrate accessing memory beyond array bounds
 void demonstrate_buffer_overflow() {
     printf("\n=== Buffer Overflow Demonstration ===\n");
     printf("Attempting to write beyond array bounds...\n");
     
     char small_array[5] = "Hello";
     printf("Original array: %s\n", small_array);
     
     // Deliberately write beyond array bounds
     strcpy(small_array, "This string is way too long for our small array!");
     printf("If you see this, the program didn't crash (unlikely)\n");
 }
 
 // Function to demonstrate use-after-free
 void demonstrate_use_after_free() {
     printf("\n=== Use After Free Demonstration ===\n");
     
     // Allocate memory
     char* ptr = (char*)malloc(10);
     if (ptr == NULL) {
         perror("malloc failed");
         return;
     }
     
     // Initialize memory
     strcpy(ptr, "Hello");
     printf("Before free: %s\n", ptr);
     
     // Free the memory
     free(ptr);
     printf("Memory freed\n");
     
     // Try to use the memory after it's been freed
     printf("Attempting to use freed memory...\n");
     strcpy(ptr, "This will crash!");
     printf("If you see this, the program didn't crash (unlikely)\n");
 }
 
 // Function to demonstrate null pointer dereference
 void demonstrate_null_pointer() {
     printf("\n=== Null Pointer Dereference Demonstration ===\n");
     
     // Create a null pointer
     char* ptr = NULL;
     printf("Created null pointer\n");
     
     // Try to dereference it
     printf("Attempting to dereference null pointer...\n");
     *ptr = 'X';
     printf("If you see this, the program didn't crash (unlikely)\n");
 }
 
 // Function to demonstrate stack corruption
 void demonstrate_stack_corruption() {
     printf("\n=== Stack Corruption Demonstration ===\n");
     
     // Create a buffer on the stack
     char buffer[10];
     
     // Get a pointer to a local variable
     int local_var = 42;
     printf("Local variable value: %d\n", local_var);
     
     // Deliberately corrupt the stack by writing beyond buffer
     printf("Attempting to corrupt stack...\n");
     memset(buffer, 'X', 100);  // Write way beyond buffer bounds
     
     printf("Local variable value after corruption: %d\n", local_var);
     printf("If you see this, the program didn't crash (unlikely)\n");
 }
 
 // Function to demonstrate double free
 void demonstrate_double_free() {
     printf("\n=== Double Free Demonstration ===\n");
     
     // Allocate memory
     char* ptr = (char*)malloc(10);
     if (ptr == NULL) {
         perror("malloc failed");
         return;
     }
     
     printf("Memory allocated\n");
     
     // Free the memory
     free(ptr);
     printf("First free completed\n");
     
     // Try to free it again
     printf("Attempting to free memory again...\n");
     free(ptr);
     printf("If you see this, the program didn't crash (unlikely)\n");
 }
 
 // Function to demonstrate accessing invalid memory
 void demonstrate_invalid_memory_access() {
     printf("\n=== Invalid Memory Access Demonstration ===\n");
     
     // Create a pointer to an invalid memory location
     char* ptr = (char*)0x12345678;
     printf("Created pointer to invalid memory location\n");
     
     // Try to access it
     printf("Attempting to access invalid memory...\n");
     *ptr = 'X';
     printf("If you see this, the program didn't crash (unlikely)\n");
 }
 
 int main() {
     printf("Memory Safety Violation Demo\n");
     printf("WARNING: This program is designed to crash in different ways!\n");
     printf("It demonstrates why memory safety is important.\n\n");
     
     int choice;
     while (1) {
         printf("\nChoose a demonstration:\n");
         printf("1. Buffer Overflow\n");
         printf("2. Use After Free\n");
         printf("3. Null Pointer Dereference\n");
         printf("4. Stack Corruption\n");
         printf("5. Double Free\n");
         printf("6. Invalid Memory Access\n");
         printf("7. Exit\n");
         printf("Enter your choice (1-7): ");
         scanf("%d", &choice);
         getchar(); // Consume newline
         
         switch (choice) {
             case 1:
                 demonstrate_buffer_overflow();
                 break;
             case 2:
                 demonstrate_use_after_free();
                 break;
             case 3:
                 demonstrate_null_pointer();
                 break;
             case 4:
                 demonstrate_stack_corruption();
                 break;
             case 5:
                 demonstrate_double_free();
                 break;
             case 6:
                 demonstrate_invalid_memory_access();
                 break;
             case 7:
                 printf("\nExiting program safely...\n");
                 return 0;
             default:
                 printf("Invalid choice. Please try again.\n");
         }
     }
     
     return 0;
 } 