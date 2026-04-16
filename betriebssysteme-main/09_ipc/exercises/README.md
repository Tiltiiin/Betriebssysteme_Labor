# Chapter 9: Inter-Process Communication (IPC) Exercises

This document provides an overview of three IPC demonstration programs: `mmap_anon.c`, `pipe.c`, and `process_vm_readv.c`. Each program illustrates different methods of inter-process communication in C, and the following exercise tasks are designed to help you investigate, extend, and measure the performance of these implementations.

## 1. mmap_anon.c

### Overview
The `mmap_anon.c` program demonstrates the use of anonymous memory mapping with `mmap`, allowing both the parent and child processes to share the same memory space. The parent process writes a string to the mapped memory, and the child process reads from it, showcasing inter-process communication through shared memory.

### Exercise Tasks
#### (i) Investigate the file, compile, and run it
- **Compile**: Use the following command to compile the program:
  ```bash
  gcc -o mmap_anon mmap_anon.c
  # or using the Makefile
  make mmap_anon
  ```
- **Run**: Execute the compiled program:
  ```bash
  ./mmap_anon
  ```

#### (ii) Extend the size of data shared across the threads
- Modify the `mmap` call to increase the size of the shared memory. For example, change `4096` to `8192` or more, depending on your requirements:
  ```c
  anon = mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
  ```

#### (iii) Measure the time and bandwidth of the data shared
- Implement timing measurements using the CPU's time-stamp counter (similar to the other programs) to measure the time taken for writing and reading operations. You can use the `getrdtsc` function to capture the start and stop times around the `strcpy` operations. Check this repository's chapter **04 System Interrupts** and the `syscall_benchmark.c` program for inspiration on how to do this.

## 2. pipe.c

### Overview
The `pipe.c` program demonstrates a simple inter-process communication (IPC) between a parent and child process using pipes. The program also measures the time taken to write to the pipe using the CPU's time-stamp counter (TSC).

### Exercise Tasks
#### (i) Investigate the file, compile, and run it
- **Compile**: Use the following command to compile the program:
  ```bash
  gcc -o pipe pipe.c
  # or using the Makefile
  make pipe
  ```
- **Run**: Execute the compiled program:
  ```bash
  ./pipe
  ```

#### (ii) Extend the size of data shared across the threads
- Modify the `SIZE` definition to increase the buffer size for reading and writing. For example, change `#define SIZE 4096` to `#define SIZE 8192`.

#### (iii) Measure the time and bandwidth of the data shared
- Use the existing timing mechanism in the program to measure the time taken for writing to the pipe. To calculate bandwidth, you can use the formula:
  ```plaintext
  Bandwidth = (Number of Bytes Written) / (Time Taken in Seconds)
  ```

## 3. process_vm_readv.c

### Overview
The `process_vm_readv.c` program demonstrates the use of `process_vm_readv` and `process_vm_writev` to read and write to another process's memory. This program only works on Linux and allows direct memory access between processes. Use the BSLab server to run this program (attention: you need to be logged in to HSE VPN to have access to the BSLab server).

### Exercise Tasks
#### (i) Investigate the file, compile, and run it
- **Compile**: Use the following command to compile the program:
  ```bash
  gcc -o process_vm_readv process_vm_readv.c
  # or using the Makefile
  make process_vm_readv
  ```
- **Run**: Execute the compiled program:
  ```bash
  ./process_vm_readv
  ```

#### (ii) Extend the size of data shared across the threads
- Increase the size of the shared buffer by modifying the `SIZE` definition. For example, change `#define SIZE 4096` to `#define SIZE 8192`.

#### (iii) Measure the time and bandwidth of the data shared
- Similar to the previous programs, use the `getrdtsc` function to measure the time taken for the `process_vm_writev` operation. Calculate the bandwidth using the formula mentioned above.

## Conclusion
These exercises will help you understand the different IPC mechanisms in C, how to extend their capabilities, and how to measure their performance. Make sure to document your findings and any challenges you encounter during the exercises.
