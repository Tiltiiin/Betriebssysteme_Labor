/**
 * Benchmark to measure Linux' methods to do syscall.
 * Measure's getpid() using the CPU's tick instruction (Intel rdtsc / Apple msr),
 * using:
 *    - libc' getpid()
 *    - using syscall instruction
 *    - (on Intel) using the venerable "int 0x80"
 *
 * Copyright 2013-2024, Rainer Keller, HS Esslingen
 * This will seg-fault after(!) printf() with gcc-4.4.7.
 * Compile:
 *      gcc -Wall -o2 -o benchmark syscall_benchmark.c
 */
#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#define NUM_TIMES 10000

#define DEBUG(x)    x

/**
 * Reads the current value of the processor's Time Stamp Counter (TSC)
 * and returns it as a 64-bit unsigned integer.
 */
unsigned long long int getrdtsc (void)
{
    unsigned long long tsc = 0;
#if defined(__x86_64__)
    unsigned int hi, lo;
    // inline assembly statement in C for direct access to hardware registers
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    // merge low-order (lo) and high-order (hi) 32-bit into a 64-bit value
    tsc = ((uint64_t)hi << 32) |  (uint64_t)lo;
#elif defined(__aarch64__)
    // inline assembly statement in C for direct access to hardware registers
    // mrs = move register to system register where CNTVCT_ELO which holds
    // the "current value of the virtual counter" of the ARM Generic Timer system
    // that tracks the number of ticks since some point in time (typically the system boot)
    // the value of the timer is loaded into variable "tsc"
    __asm__ __volatile__("mrs %0, CNTVCT_EL0" : "=r" (tsc));
    // __asm__ __volatile__("mrs %0, PMCCNTR_EL0" : "=r"(tsc));
#endif
    return tsc;
}

/**
 * The function my_getpid() retrieves the process ID (PID) of the current 
 * process using the 32-bit int $0x80 system call mechanism on x86 architectures. 
 * It directly invokes the getpid() system call by placing the corresponding 
 * system call number (0x27) into EAX and triggering the interrupt int $0x80. 
 * The resulting PID is returned from the function.
 */
#if defined(__x86_64__)
long int my_getpid(void)
{
    long int pid;
    __asm__ __volatile__(
        "movl $0x27, %%eax\n\t"
        "int $0x80\n\t"
        : "=a" ((long int)pid) /* output */
        :                      /* input */
        : "memory");           /* clobbers */
    return pid;
}
#endif

int main(int argc, char * argv[]) {
    // Declare variables for process IDs
    // timestamp counters and avg number of cpu cycles
    long int ID1, ID2, ID3;
    unsigned long long int tsc_start, tsc_stop;
    double tsc_syscall = 0.0, tsc_libc = 0.0, tsc_int80 = 0.0;
    int i;

    // Timing measures for libc getpid() function
    DEBUG(printf("Timing: Measure libc getpid()"));
    tsc_start = getrdtsc ();
    for (i = 0; i < NUM_TIMES; i++)
    	ID1 = getpid();
    tsc_stop = getrdtsc ();
    tsc_libc = (tsc_stop - tsc_start) / (double)NUM_TIMES;
    DEBUG(printf (":%.2f\n", tsc_libc));

    // Timing measures for direct syscall using SYS_getpid
    DEBUG(printf("Timing: Measure direct syscall SYS_getpid"));
    tsc_start = getrdtsc ();
    for (i = 0; i < NUM_TIMES; i++)
	ID2 = syscall(SYS_getpid);
    tsc_stop = getrdtsc ();
    tsc_syscall = (tsc_stop - tsc_start) / (double)NUM_TIMES;
    DEBUG(printf (":%.2f\n", tsc_syscall));

#if defined(__x86_64__)
    // This code is performing timing measurements for a sequence of instructions using the getrdtsc() function to 
    // measure the number of CPU cycles taken to execute the assembly sequence on Intel x86 architecture.
    // in this case involves repeated calls to the my_getpid() function.
    DEBUG(printf("Timing: Measure Assembler sequence"));
    tsc_start = getrdtsc ();            // call to our function gtrdtsc for time stamp counter 
    for (i = 0; i < NUM_TIMES; i++)
    	ID3 = my_getpid();              // makes the call to my_getpid function
    tsc_stop = getrdtsc ();             // gets the time stamp counter again from system
    tsc_int80 = (double)(tsc_stop - tsc_start) / (double)NUM_TIMES;
    DEBUG(printf (":%.2f\n", tsc_int80)); // prompts the time taken to read the PID
    // PLEASE NOTE:
    // Although the function is defined under #if defined(__x86_64__), it uses the 32-bit system 
    // call interface (int $0x80). This mechanism is specific to 32-bit x86 systems and is considered legacy. 
    // The int $0x80 interface will still work in compatibility mode on 64-bit systems, but it’s generally slower 
    // and less preferred compared to the syscall instruction.
#else
    printf("my_getpid with direct system call using ASM not yet implemented on Aarch64\n");
    tsc_int80=-1.0;
#endif
    // retrieves the current process ID (PID) by making a system call
    // using the int 0x80 software interrupt, which was traditionally used in Linux
    // to invoke system calls.
    printf("Timing: libc:%.2f direct syscall:%.2f ASM int 0x80:%8.0f\n",
           tsc_libc, tsc_syscall, tsc_int80);

    return 0;
}

